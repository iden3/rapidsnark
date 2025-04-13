#ifndef VULKAN_MANAGER_H
#define VULKAN_MANAGER_H

#include <vulkan/vulkan.h>
#include <memory>
#include "vulkan_pipeline.h"

class VulkanManager
{
public:
    using PipelinePtr = std::shared_ptr<VulkanPipeline>;

public:
    VulkanManager(bool enableExceptions = true);
    ~VulkanManager();

    bool isValid() const { return m_isValid; }

    PipelinePtr createPipeline(const char *shaderPath,
                               const VulkanMemoryLayout &memoryLayout,
                               uint32_t groupCount, const VulkanBufferView &params);

    void debugInfo(std::ostream& os, unsigned int logLevel);

private:
    void initInstance();
    void initPhysicalDevice();
    void initQueueFamilyIndex();
    void initDevice();

    void destroy();

private:
    VkInstance        m_instance;
    VkPhysicalDevice  m_physicalDevice;
    uint32_t          m_queueFamilyIndex;
    VkDevice          m_device;
    bool              m_enableExceptions;
    bool              m_isValid;
};

#endif // VULKAN_MANAGER_H
