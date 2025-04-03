#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

#include <vulkan/vulkan.h>
#include <memory>
#include "vulkan_buffer.h"

struct VulkanMemoryLayout
{
    size_t sizeR;
    size_t sizeA;
    size_t sizeB;
    size_t sizeParams;
    size_t sizeTemp;
};

struct VulkanBufferView
{
    void   *data;
    size_t  size;
};

class VulkanPipeline
{
    using BufferPtr = std::shared_ptr<VulkanBuffer>;

    const uint64_t computeTimeout = 15*1000*1000*1000LL; // 15 second in ns

public:
    VulkanPipeline(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t queueFamilyIndex,
                   const char *shaderPath, const VulkanMemoryLayout& memoryLayout, uint32_t groupCount);
    ~VulkanPipeline();

    void run(VulkanBufferView &r, const VulkanBufferView &a, const VulkanBufferView &b, const VulkanBufferView &params);
    void runAsync(const VulkanBufferView &a, const VulkanBufferView &b, const VulkanBufferView &params);
    void wait(VulkanBufferView &r);

    size_t shaderSize() const { return m_shaderSize; }

private:
    void initQueue();
    void initCommandPool();
    void initCommandBuffer();
    void initFence();
    void initShaderModule(const char *shaderPath);
    void initDescriptorSetLayout();
    void initDescriptorPool();
    void initDescriptorSet();
    void initPipelineLayout();
    void initPipeline();
    void updateDescriptorSet();

    void destroy();

    void buildCommandBuffer(uint32_t groupCount);
    void beginCommandBuffer();
    void endCommandBuffer();
    void submitCommandBuffer();
    void waitFence();
    void resetFence();
    void bindPipeline();
    void bindDescriptorSet();
    void dispatchCommandBuffer(uint32_t groupCount);

    BufferPtr createBuffer(size_t dataSize, VulkanBuffer::Type type);

private:
    VkPhysicalDevice       m_physicalDevice;
    uint32_t               m_queueFamilyIndex;
    VkDevice               m_device;
    VkQueue                m_queue;
    VkCommandPool          m_commandPool;
    VkCommandBuffer        m_commandBuffer;
    VkFence                m_fence;
    VkShaderModule         m_shaderModule;
    VkDescriptorSetLayout  m_descriptorSetLayout;
    VkDescriptorPool       m_descriptorPool;
    VkDescriptorSet        m_descriptorSet;
    VkPipelineLayout       m_pipelineLayout;
    VkPipeline             m_pipeline;
    size_t                 m_shaderSize;
    BufferPtr              m_bufferA;
    BufferPtr              m_bufferB;
    BufferPtr              m_bufferR;
    BufferPtr              m_bufferParams;
    BufferPtr              m_bufferTemp;
};

#endif // VULKAN_PIPELINE_H
