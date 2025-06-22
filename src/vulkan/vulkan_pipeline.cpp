#include "vulkan_pipeline.h"
#include <fstream>
#include <vector>

static std::vector<char>
loadSource(const std::string& shader_path)
{
    std::ifstream fileStream(shader_path, std::ios::binary);

    if (!fileStream) {
        throw InvalidPathException("failed to open shader file", shader_path);
    }

    std::vector<char> buffer;

    buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(fileStream), {});

    return buffer;
}

VulkanPipeline::VulkanPipeline(VkPhysicalDevice physicalDevice,
        VkDevice                  device,
        uint32_t                  queueFamilyIndex,
        const std::string        &shaderDir,
        const VulkanMemoryLayout &memoryLayout,
        const ShaderParams       &params)

    : m_physicalDevice(physicalDevice)
    , m_queueFamilyIndex(queueFamilyIndex)
    , m_device(device)
    , m_commandPool(VK_NULL_HANDLE)
    , m_commandBuffer(VK_NULL_HANDLE)
    , m_fence(VK_NULL_HANDLE)
    , m_shaderModules{VK_NULL_HANDLE, VK_NULL_HANDLE}
    , m_descriptorSetLayout(VK_NULL_HANDLE)
    , m_descriptorPool(VK_NULL_HANDLE)
    , m_descriptorSet(VK_NULL_HANDLE)
    , m_pipelineLayout(VK_NULL_HANDLE)
    , m_pipelines{VK_NULL_HANDLE, VK_NULL_HANDLE}
    , m_shaderSize(0)
{
    try {
        initQueue();
        initCommandPool();
        initCommandBuffer();
        initFence();
        initShaderModules(shaderDir);
        initDescriptorPool();
        initDescriptorSetLayout();
        initDescriptorSet();
        initPipelineLayout();
        initPipelines();

        m_bufferA = createBuffer(memoryLayout.sizeA);
        m_bufferB = createBuffer(memoryLayout.sizeB);
        m_bufferR = createBuffer(memoryLayout.sizeR);
        m_bufferParams = createBuffer(sizeof(ShaderParams), VulkanBuffer::Uniform | VulkanBuffer::DeviceOnly);
        m_bufferTemp = createBuffer(memoryLayout.sizeTemp, VulkanBuffer::DeviceOnly);

        updateDescriptorSet();

        buildCommandBuffer(params);

    } catch (...) {
        destroy();
        throw;
    }
}

VulkanPipeline::~VulkanPipeline()
{
    destroy();
}

void VulkanPipeline::buildCommandBuffer(const ShaderParams &params)
{
    GroupCounts groupCounts = {
        (params.nPoints + params.workgroupSize - 1) / params.workgroupSize,
        params.nChunks
    };

    beginCommandBuffer();

    m_bufferA->recordCopyToDevice(m_commandBuffer);
    m_bufferB->recordCopyToDevice(m_commandBuffer);

    m_bufferA->recordMemoryBarrier(m_commandBuffer,
                                   VK_ACCESS_TRANSFER_WRITE_BIT,
                                   VK_ACCESS_SHADER_READ_BIT,
                                   VK_PIPELINE_STAGE_TRANSFER_BIT,
                                   VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);

    m_bufferB->recordMemoryBarrier(m_commandBuffer,
                                   VK_ACCESS_TRANSFER_WRITE_BIT,
                                   VK_ACCESS_SHADER_READ_BIT,
                                   VK_PIPELINE_STAGE_TRANSFER_BIT,
                                   VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);

    m_bufferParams->update(m_commandBuffer, &params, sizeof(params));
    m_bufferTemp->fill(m_commandBuffer, 0);

    bindDescriptorSet();

    for (int i = 0; i < groupCounts.size(); i++) {
        bindPipeline(i);
        dispatchCommandBuffer(groupCounts[i]);
    }

    m_bufferR->recordMemoryBarrier(m_commandBuffer,
                                   VK_ACCESS_SHADER_WRITE_BIT,
                                   VK_ACCESS_TRANSFER_READ_BIT,
                                   VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                                   VK_PIPELINE_STAGE_TRANSFER_BIT);

    m_bufferR->recordCopyFromDevice(m_commandBuffer);

    m_bufferR->recordMemoryBarrier(m_commandBuffer,
                                   VK_ACCESS_TRANSFER_WRITE_BIT,
                                   VK_ACCESS_HOST_READ_BIT,
                                   VK_PIPELINE_STAGE_TRANSFER_BIT,
                                   VK_PIPELINE_STAGE_HOST_BIT);
    endCommandBuffer();
}

void VulkanPipeline::run(VulkanBufferView &r, const VulkanBufferView &a, const VulkanBufferView &b)
{
    runAsync(a, b);
    wait(r);
}

void VulkanPipeline::runAsync(const VulkanBufferView &a, const VulkanBufferView &b)
{
    m_bufferA->copyFromLocalBuffer(a.data, a.size);
    m_bufferB->copyFromLocalBuffer(b.data, b.size);

    resetFence();
    submitCommandBuffer();
}

void VulkanPipeline::wait(VulkanBufferView &r)
{
    waitFence();

    m_bufferR->copyToLocalBuffer(r.data, r.size);
}

void VulkanPipeline::destroy()
{
    m_bufferA.reset();
    m_bufferB.reset();
    m_bufferR.reset();
    m_bufferParams.reset();
    m_bufferTemp.reset();

    if (m_pipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
    }

    for (int i = 0; i < m_pipelines.size(); i++) {
        if (m_pipelines[i] != VK_NULL_HANDLE) {
            vkDestroyPipeline(m_device, m_pipelines[i], nullptr );
        }
    }

    if (m_descriptorPool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
    }

    if (m_descriptorSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
    }

    for (int i = 0; i < m_shaderModules.size(); i++) {
        if (m_shaderModules[i] != VK_NULL_HANDLE) {
            vkDestroyShaderModule(m_device, m_shaderModules[i], nullptr);
        }
    }

    if (m_fence != VK_NULL_HANDLE) {
        vkDestroyFence(m_device, m_fence, nullptr);
    }

    if (m_commandBuffer != VK_NULL_HANDLE) {
        vkFreeCommandBuffers(m_device, m_commandPool, 1, &m_commandBuffer);
    }

    if (m_commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(m_device, m_commandPool, nullptr);
    }
}

void VulkanPipeline::initQueue()
{
    const uint32_t queueIndex = 0;

    vkGetDeviceQueue(m_device, m_queueFamilyIndex, queueIndex, &m_queue);
}

void VulkanPipeline::initCommandPool()
{
    VkCommandPoolCreateInfo poolInfo = {
        VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        nullptr,
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        m_queueFamilyIndex
    };

    VkResult result = vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a command pool");
    }
}

void VulkanPipeline::initCommandBuffer()
{
    VkCommandBufferAllocateInfo bufferInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        nullptr,
        m_commandPool,
        VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        1
    };

    VkResult result = vkAllocateCommandBuffers(m_device, &bufferInfo, &m_commandBuffer);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a command buffer");
    }
}

void VulkanPipeline::initFence()
{
    VkFenceCreateInfo fenceInfo = {
        VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        nullptr,
        0,
    };

    VkResult result = vkCreateFence(m_device, &fenceInfo, nullptr, &m_fence);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a fence");
    }
}

size_t VulkanPipeline::initShaderModule(const std::string& shaderPath, VkShaderModule &shaderModule)
{
    std::vector<char> shader = loadSource(shaderPath);

    if (shader.empty()) {
        return 0;
    }

    VkShaderModuleCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        nullptr,
        0,
        shader.size(), // in bytes
        reinterpret_cast<uint32_t const *>(shader.data())
    };

    VkResult result = vkCreateShaderModule(m_device, &createInfo, nullptr, &shaderModule);

    if (result != VK_SUCCESS) {
        throw InvalidShaderException("failed to create a shader module from " + shaderPath);
    }

    return shader.size();
}

static inline std::string buildShaderPath(const std::string& shaderDir, unsigned stageNumber)
{
    std::string shaderName = "stage" + std::to_string(stageNumber) + ".spv";

    if (shaderDir.empty()) {
        return shaderName;
    }

    return shaderDir + "/" + shaderName;
}

void VulkanPipeline::initShaderModules(const std::string& shaderDir)
{
    for (int i = 0; i < m_shaderModules.size(); i++) {
        const auto shaderPath = buildShaderPath(shaderDir, i);

        m_shaderSize += initShaderModule(shaderPath, m_shaderModules[i]);
    }

    if (m_shaderSize == 0) {
        throw InvalidShaderException("all shaders are empty in " + shaderDir);
    }
}

void VulkanPipeline::initDescriptorSetLayout()
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;

    uint32_t num = 0;

    for (int i = 0; i < 1; i++) {
        bindings.push_back({num++,
                            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                            1,
                            VK_SHADER_STAGE_COMPUTE_BIT,
                            nullptr});
    }

    for (int i = 0; i < 4; i++) {
        bindings.push_back({num++,
                            VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                            1,
                            VK_SHADER_STAGE_COMPUTE_BIT,
                            nullptr});
    }

    VkDescriptorSetLayoutCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        nullptr,
        0,
        static_cast<uint32_t>(bindings.size()),
        bindings.data()
    };

    VkResult result = vkCreateDescriptorSetLayout(m_device, &createInfo, nullptr, &m_descriptorSetLayout);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a descriptor set layout");
    }
}

void VulkanPipeline::initDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> descriptorPoolSizes = {
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4}
    };

    VkDescriptorPoolCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        nullptr,
        0,
        1,
        static_cast<uint32_t>(descriptorPoolSizes.size()),
        descriptorPoolSizes.data()
    };

    VkResult result = vkCreateDescriptorPool(m_device, &createInfo, nullptr, &m_descriptorPool);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to  create a descriptor pool");
    }
}

void VulkanPipeline::initDescriptorSet()
{
    VkDescriptorSetAllocateInfo allocInfo = {
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        nullptr,
        m_descriptorPool,
        1,
        &m_descriptorSetLayout
    };

    VkResult result = vkAllocateDescriptorSets(m_device, &allocInfo, &m_descriptorSet);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to  allocate descriptor sets");
    }
}

void VulkanPipeline::updateDescriptorSet()
{
    std::vector<VkWriteDescriptorSet> writeDescriptors =  {
        m_bufferParams->updateDescriptorSet(m_descriptorSet, 0),
        m_bufferA->updateDescriptorSet(m_descriptorSet, 1),
        m_bufferB->updateDescriptorSet(m_descriptorSet, 2),
        m_bufferR->updateDescriptorSet(m_descriptorSet, 3),
        m_bufferTemp->updateDescriptorSet(m_descriptorSet, 4)
      };

    vkUpdateDescriptorSets(m_device, writeDescriptors.size(), writeDescriptors.data(), 0, nullptr);
}

void VulkanPipeline::initPipelineLayout()
{
    VkPipelineLayoutCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        nullptr,
        0,
        1,
        &m_descriptorSetLayout,
        0,
        nullptr
    };

    VkResult result = vkCreatePipelineLayout(m_device, &createInfo, nullptr, &m_pipelineLayout);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a pipeline layout");
    }
}

void VulkanPipeline::initPipelines()
{
    for (int i = 0; i < m_pipelines.size(); i++) {

        if (m_shaderModules[i] == VK_NULL_HANDLE) {
            continue;
        }

        VkPipelineShaderStageCreateInfo shaderStage = {
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr,
            0,
            VK_SHADER_STAGE_COMPUTE_BIT,
            m_shaderModules[i],
            "main",
            nullptr
        };

        VkComputePipelineCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
            nullptr,
            0,
            shaderStage,
            m_pipelineLayout,
            VK_NULL_HANDLE,
            -1
        };

        VkResult result = vkCreateComputePipelines(m_device, nullptr, 1, &createInfo, nullptr, &m_pipelines[i]);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create a compute pipeline for NAF shader");
        }
    }
}

void VulkanPipeline::beginCommandBuffer()
{
    VkCommandBufferBeginInfo beginInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        nullptr,
        0,
        nullptr
    };

    VkResult result = vkBeginCommandBuffer(m_commandBuffer, &beginInfo);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to begin the command buffer");
    }
}

void VulkanPipeline::endCommandBuffer()
{
    VkResult result = vkEndCommandBuffer(m_commandBuffer);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("error during recording commands");
    }
}

void VulkanPipeline::submitCommandBuffer()
{
    VkSubmitInfo submitInfo = {
        VK_STRUCTURE_TYPE_SUBMIT_INFO,
        nullptr,
        0,
        nullptr,
        nullptr,
        1,
        &m_commandBuffer,
        0,
        nullptr
    };

    VkResult result = vkQueueSubmit(m_queue, 1, &submitInfo, m_fence);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to submit command buffer");
    }
}

void VulkanPipeline::waitFence()
{
    VkResult result = vkWaitForFences(m_device, 1, &m_fence, VK_TRUE, computeTimeout);

    if (result != VK_SUCCESS) {
        throw TimeoutException("compute pipeline timed out");
    }
}

void VulkanPipeline::resetFence()
{
    VkResult result = vkResetFences(m_device, 1, &m_fence);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to reset the fence");
    }
}

bool VulkanPipeline::bindPipeline(unsigned stageNumber)
{
    if (m_pipelines[stageNumber] != VK_NULL_HANDLE) {

        vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_pipelines[stageNumber]);
        return true;
    }

    return false;
}

void VulkanPipeline::bindDescriptorSet()
{
    vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_pipelineLayout,
                            0, 1, &m_descriptorSet, 0, nullptr);
}

void VulkanPipeline::dispatchCommandBuffer(uint32_t groupCountX, uint32_t groupCountY)
{
    vkCmdDispatch(m_commandBuffer, groupCountX, groupCountY, 1);
}

VulkanPipeline::BufferPtr VulkanPipeline::createBuffer(size_t dataSize, unsigned typeFlags)
{
    return std::make_shared<VulkanBuffer>(m_physicalDevice, m_device, dataSize, typeFlags);
}
