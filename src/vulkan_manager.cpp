#include "vulkan_manager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

static std::vector<char>
loadSource(const char *shader_path)
{
    std::ifstream fileStream(shader_path, std::ios::binary);

    if (!fileStream) {
        throw std::runtime_error(std::string("failed to open shader file: ")
                                 + shader_path);
    }

    std::vector<char> buffer;

    buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(fileStream), {});

    return buffer;
}

VulkanManager::VulkanManager(const char *shaderPath) :
    m_instance(VK_NULL_HANDLE),
    m_device(VK_NULL_HANDLE),
    m_commandPool(VK_NULL_HANDLE),
    m_commandBuffer(VK_NULL_HANDLE),
    m_fence(VK_NULL_HANDLE),
    m_shaderModule(VK_NULL_HANDLE),
    m_descriptorSetLayout(VK_NULL_HANDLE),
    m_descriptorPool(VK_NULL_HANDLE),
    m_descriptorSet(VK_NULL_HANDLE),
    m_pipelineLayout(VK_NULL_HANDLE),
    m_pipeline(VK_NULL_HANDLE)
{
    try {
        initInstance();
        initPhysicalDevice();
        initQueueFamilyIndex();
        initDevice();
        initQueue();
        initCommandPool();
        initCommandBuffer();
        initFence();
        initShaderModule(shaderPath);
        initDescriptorPool();
        initDescriptorSetLayout();
        initDescriptorSet();
        initPipelineLayout();
        initPipeline();

    } catch (...) {
        destroy();
        throw;
    }
}

VulkanManager::~VulkanManager()
{
    destroy();
}

void VulkanManager::run(void *r, void *a, void *b, size_t dataSize, uint32_t groupCount)
{
    m_groupCount = groupCount;

    m_bufferA = createBuffer(a, dataSize);
    m_bufferB = createBuffer(b, dataSize);
    m_bufferR = createBuffer(r, dataSize);

    m_bufferA->copyFromLocalBuffer();
    m_bufferB->copyFromLocalBuffer();

    updateDescriptorSet();

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
    bindPipeline();
    bindDescriptorSet();

    dispatchCommandBuffer();

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

    resetFence();
    submitCommandBuffer();
    waitFence();

    m_bufferR->copyToLocalBuffer();

    m_bufferA.reset();
    m_bufferB.reset();
    m_bufferR.reset();
}

void VulkanManager::destroy()
{
    if (m_pipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
    }

    if (m_pipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(m_device, m_pipeline, nullptr );
    }

    if (m_descriptorSet != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
    }

    if (m_descriptorSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
    }

    if (m_shaderModule != VK_NULL_HANDLE) {
        vkDestroyShaderModule(m_device, m_shaderModule, nullptr);
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

    if (m_instance != VK_NULL_HANDLE) {
        vkDestroyDevice(m_device, nullptr);
    }

    if (m_device != VK_NULL_HANDLE) {
        vkDestroyInstance(m_instance, nullptr);
    }
}

void VulkanManager::initInstance()
{
    VkApplicationInfo appInfo = { };

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "rapidsnark";
    appInfo.pEngineName = "rapidsnark";
    appInfo.apiVersion =  VK_API_VERSION_1_0;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

    std::vector<char const *> layers;
    layers.emplace_back("VK_LAYER_LUNARG_standard_validation");

    VkInstanceCreateInfo createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
//    createInfo.ppEnabledLayerNames = layers.data();
//    createInfo.enabledLayerCount = layers.size();

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create an instance");
    }
}

void VulkanManager::initPhysicalDevice()
{
    VkResult result;
    uint32_t deviceCount = 0;
    std::vector<VkPhysicalDevice> devices;

    result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to enumerate physical devices");
    }

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support");
    }

    devices.resize(deviceCount);

    result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to enumerate physical devices");
    }

    m_physicalDevice = devices[0];
}

void VulkanManager::initQueueFamilyIndex()
{
    uint32_t queueFamilyIndex = 0;
    uint32_t queueFamilyCount = 0;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;

    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

    queueFamilyProperties.resize(queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount,
                                             queueFamilyProperties.data());

    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            queueFamilyIndex = i;
            break;
        }
    }

    m_queueFamilyIndex = queueFamilyIndex;
}


void VulkanManager::initDevice()
{
    VkResult result;
    VkPhysicalDeviceFeatures supportedFeatures;
    VkPhysicalDeviceFeatures requiredFeatures = {};
    const float priority = 1.0;
    const uint32_t queueCount = 1;

    vkGetPhysicalDeviceFeatures(m_physicalDevice, &supportedFeatures);

//    requiredFeatures.shaderInt64 = supportedFeatures.shaderInt64;

    const VkDeviceQueueCreateInfo queueCreateInfo = {
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        0,
        m_queueFamilyIndex,
        queueCount,
        &priority
    };

    const VkDeviceCreateInfo deviceCreateInfo = {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        nullptr,
        0,
        1,
        &queueCreateInfo,
        0,
        nullptr,
        0,
        nullptr,
        &requiredFeatures
    };

    result = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a logical device");
    }
}

void VulkanManager::initQueue()
{
    const uint32_t queueIndex = 0;

    vkGetDeviceQueue(m_device, m_queueFamilyIndex, queueIndex, &m_queue);
}

void VulkanManager::initCommandPool()
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

void VulkanManager::initCommandBuffer()
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

void VulkanManager::initFence()
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

void VulkanManager::initShaderModule(const char *shaderPath)
{
    std::vector<char> shader = loadSource(shaderPath);

    VkShaderModuleCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        nullptr,
        0,
        shader.size(), // in bytes
        reinterpret_cast<uint32_t const *>(shader.data())
    };

    VkResult result = vkCreateShaderModule(m_device,  &createInfo, nullptr, &m_shaderModule);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a shader module");
    }
}

void VulkanManager::initDescriptorSetLayout()
{

    std::vector<VkDescriptorSetLayoutBinding> bindings;

    for (uint32_t i = 0; i < 3; i++) {
        bindings.push_back({i,
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
        throw std::runtime_error("failed to  create a descriptor set layout");
    }
}

void VulkanManager::initDescriptorPool()
{
    VkDescriptorPoolSize descriptorPoolSize = {
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        3
    };

    VkDescriptorPoolCreateInfo createInfo = {
        VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        nullptr,
        0,
        1,
        1,
        &descriptorPoolSize
    };

    VkResult result = vkCreateDescriptorPool(m_device, &createInfo, nullptr, &m_descriptorPool);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to  create a descriptor pool");
    }
}

void VulkanManager::initDescriptorSet()
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

void VulkanManager::initPipelineLayout()
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

void VulkanManager::initPipeline()
{
    VkPipelineShaderStageCreateInfo shaderStage = {
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        nullptr,
        0,
        VK_SHADER_STAGE_COMPUTE_BIT,
        m_shaderModule,
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

    VkResult result = vkCreateComputePipelines(m_device, nullptr, 1, &createInfo, nullptr, &m_pipeline);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create a compute pipeline");
    }
}

void VulkanManager::beginCommandBuffer()
{
    VkCommandBufferBeginInfo beginInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        nullptr,
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        nullptr
    };

    VkResult result = vkBeginCommandBuffer(m_commandBuffer, &beginInfo);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to begin the command buffer");
    }
}

void VulkanManager::endCommandBuffer()
{
    VkResult result = vkEndCommandBuffer(m_commandBuffer);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("error during recording commands");
    }
}

void VulkanManager::submitCommandBuffer()
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

void VulkanManager::waitFence()
{
    uint64_t timeout = 1000*1000*1000LL; // 1 second

    VkResult result = vkWaitForFences(m_device, 1, &m_fence, VK_TRUE, timeout);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("the fence timed out");
    }
}

void VulkanManager::resetFence()
{
    VkResult result = vkResetFences(m_device, 1, &m_fence);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to reset the fence");
    }
}

void VulkanManager::bindPipeline()
{
    vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_pipeline);
}

void VulkanManager::bindDescriptorSet()
{
    vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_pipelineLayout,
                            0, 1, &m_descriptorSet, 0, nullptr);
}

void VulkanManager::dispatchCommandBuffer()
{
    vkCmdDispatch(m_commandBuffer, m_groupCount, 1, 1);
}

VulkanManager::BufferPtr VulkanManager::createBuffer(void *data, size_t dataSize)
{
    return std::make_shared<VulkanBuffer>(m_physicalDevice, m_device, data, dataSize);
}

void VulkanManager::updateDescriptorSet()
{
    std::vector<VkWriteDescriptorSet> writeDescriptors =  {
        m_bufferA->updateDescriptorSet(m_descriptorSet, 0),
        m_bufferB->updateDescriptorSet(m_descriptorSet, 1),
        m_bufferR->updateDescriptorSet(m_descriptorSet, 2)
      };

    vkUpdateDescriptorSets(m_device, writeDescriptors.size(), writeDescriptors.data(), 0, nullptr);
}

#define printStr(value) os << #value " = " << value << std::endl
#define printHex(value) os << std::hex << #value " = 0x" << value << std::dec << std::endl

void VulkanManager::debugInfo(std::ostream &os)
{
    VkResult result = VK_SUCCESS;

    uint32_t extensionsCount = 0;
    std::vector<VkExtensionProperties> availableExtensions;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to get the number of instance extensions");
    }

    printStr(extensionsCount);

    if(extensionsCount != 0) {
        availableExtensions.resize(extensionsCount);

        result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, availableExtensions.data());

        if((result != VK_SUCCESS) || (extensionsCount == 0)) {
            throw std::runtime_error("Failed to enumerate instance extensions");
        }

        for (auto& instanceExt: availableExtensions) {
            printStr(instanceExt.extensionName);
        }
    }

    uint32_t instanceLayerCount = 0;
    std::vector<VkLayerProperties> instanceLayerProperties;

    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to get the number of instance layers");
    }


    printStr(instanceLayerCount);

    if (instanceLayerCount != 0) {
        instanceLayerProperties.resize(instanceLayerCount);

        result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());

        if(result != VK_SUCCESS) {
            throw std::runtime_error("Failed to enumerate instance layers");
        }

        for (auto& instanceLayer: instanceLayerProperties) {
            printStr(instanceLayer.layerName);
        }
    }

    uint32_t physicalDeviceCount = 0;

    vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to get the number of physical devices");
    }

    printStr(physicalDeviceCount);

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);

    printHex(deviceProperties.apiVersion);
    printHex(deviceProperties.driverVersion);
    printHex(deviceProperties.vendorID);
    printHex(deviceProperties.deviceID);
    printHex(deviceProperties.deviceType);
    printStr(deviceProperties.deviceName);

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(m_physicalDevice, &supportedFeatures);

    printStr(supportedFeatures.robustBufferAccess);
    printStr(supportedFeatures.pipelineStatisticsQuery);
    printStr(supportedFeatures.shaderStorageBufferArrayDynamicIndexing);
    printStr(supportedFeatures.shaderInt64);
    printStr(supportedFeatures.shaderResourceResidency);
    printStr(supportedFeatures.shaderResourceMinLod);

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memoryProperties);

    printStr(memoryProperties.memoryTypeCount);

    for (int i = 0; i < memoryProperties.memoryTypeCount; i++) {
        printHex(memoryProperties.memoryTypes[i].heapIndex);
        printHex(memoryProperties.memoryTypes[i].propertyFlags);
    }

    printStr(memoryProperties.memoryHeapCount);

    for (int i = 0; i < memoryProperties.memoryHeapCount; i++) {
        printHex(memoryProperties.memoryHeaps[i].flags);
        printStr(memoryProperties.memoryHeaps[i].size);
    }

    uint32_t queueFamilyPropertyCount = 0;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;

    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount, nullptr);

    printStr(queueFamilyPropertyCount);

    queueFamilyProperties.resize(queueFamilyPropertyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount,
                                             queueFamilyProperties.data());

    for (int i = 0; i < queueFamilyPropertyCount; i++) {
        printStr(queueFamilyProperties[i].queueCount);
        printHex(queueFamilyProperties[i].queueFlags);
    }

    uint32_t deviceExtPropertyCount = 0;
    std::vector<VkExtensionProperties> deviceExtProperties;

    result = vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &deviceExtPropertyCount, nullptr);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to get the number of device extension properties");
    }

    printStr(deviceExtPropertyCount);

    deviceExtProperties.resize(deviceExtPropertyCount);

    result = vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &deviceExtPropertyCount, deviceExtProperties.data());

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to enumerate device extension properties");
    }

    for (auto& deviceExt: deviceExtProperties) {
        printStr(deviceExt.extensionName);
    }
}
