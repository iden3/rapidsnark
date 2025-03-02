#ifndef VULKAN_MANAGER_H
#define VULKAN_MANAGER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "vulkan_buffer.h"

class VulkanManager
{
    using BufferPtr = std::shared_ptr<VulkanBuffer>;

public:
    VulkanManager(const char *shaderPath);
    ~VulkanManager();

    void run(void *r, void *a, void *b, size_t dataSize, uint32_t groupCount);

    void debugInfo(std::ostream& os);

private:
    void initInstance();
    void initPhysicalDevice();
    void initQueueFamilyIndex();
    void initDevice();
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

    void destroy();

    void beginCommandBuffer();
    void endCommandBuffer();
    void submitCommandBuffer();
    void waitFence();
    void resetFence();
    void bindPipeline();
    void bindDescriptorSet();
    void dispatchCommandBuffer();

    BufferPtr createBuffer(void *data, size_t dataSize);

    void updateDescriptorSet();

private:
    VkInstance             m_instance;
    VkPhysicalDevice       m_physicalDevice;
    uint32_t               m_queueFamilyIndex;
    VkDevice               m_device;
    VkQueue                m_queue;
    VkCommandPool          m_commandPool;
    VkCommandBuffer        m_commandBuffer;
    VkFence                m_fence;
    VkShaderModule         m_shaderModule;
    BufferPtr              m_bufferA;
    BufferPtr              m_bufferB;
    BufferPtr              m_bufferR;
    VkDescriptorSetLayout  m_descriptorSetLayout;
    VkDescriptorPool       m_descriptorPool;
    VkDescriptorSet        m_descriptorSet;
    VkPipelineLayout       m_pipelineLayout;
    VkPipeline             m_pipeline;
    uint32_t               m_groupCount;

};

#endif // VULKAN_MANAGER_H
