#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

#include "vulkan_buffer.h"
#include <vulkan/vulkan.h>
#include <string>
#include <memory>
#include <vector>

using VulkanWorkgroups = std::vector<uint32_t>;

struct VulkanMemoryLayout
{
    size_t sizeParams;
    size_t sizeR;
    size_t sizeA;
    size_t sizeB;
    size_t sizeTemp;
    size_t sizeTemp2;
};

struct VulkanBufferView
{
    void   *data;
    size_t  size;
};

class InvalidPathException : public std::runtime_error
{
public:
    explicit InvalidPathException(const std::string &msg, const std::string &path)
        : std::runtime_error(msg + ": " + path) {}
};

class InvalidShaderException : public std::runtime_error
{
public:
    explicit InvalidShaderException(const std::string &msg)
        : std::runtime_error(msg) {}
};

class TimeoutException : public std::runtime_error
{
public:
    explicit TimeoutException(const std::string &msg)
        : std::runtime_error(msg) {}
};

class VulkanPipeline
{
    static const unsigned uniformBufferCount = 1;
    static const unsigned storageBufferCount = 5;
    static const uint64_t computeTimeout = 15*1000*1000*1000LL; // 15 second in ns

    using BufferPtr     = std::shared_ptr<VulkanBuffer>;
    using ShaderModules = std::vector<VkShaderModule>;
    using Pipelines     = std::vector<VkPipeline>;

public:
    struct Perf
    {
        size_t shaderSize;
        long   compileTime;
        long   computeTime;
    };

public:
    VulkanPipeline(VkPhysicalDevice          physicalDevice,
                   VkDevice                  device,
                   uint32_t                  queueFamilyIndex,
                   const std::string        &shaderDir,
                   const VulkanWorkgroups   &workgroups,
                   const VulkanMemoryLayout &memoryLayout,
                   const void               *params);
    ~VulkanPipeline();

    void run(VulkanBufferView &r, const VulkanBufferView &a, const VulkanBufferView &b);
    void runAsync(const VulkanBufferView &a, const VulkanBufferView &b);
    void wait(VulkanBufferView &r);

    Perf getPerf() const { return { m_shaderSize, m_compileTime, m_computeTime}; }

private:
    void initQueue();
    void initCommandPool();
    void initCommandBuffer();
    void initFence();
    size_t initShaderModule(const std::string &shaderPath, VkShaderModule& shaderModule);
    void initShaderModules(const std::string &shaderDir);
    void initDescriptorSetLayout();
    void initDescriptorPool();
    void initDescriptorSet();
    void initPipelineLayout();
    void initPipelines();
    void updateDescriptorSet();

    void build(const std::string        &shaderDir,
               const VulkanMemoryLayout &memoryLayout,
               const void               *params);
    void destroy();

    void buildCommandBuffer(const void *params);
    void beginCommandBuffer();
    void endCommandBuffer();
    void submitCommandBuffer();
    void waitFence();
    void resetFence();
    bool bindPipeline(unsigned stageNumber);
    void bindDescriptorSet();
    void dispatchCommandBuffer(uint32_t groupCountX, uint32_t groupCountY = 1);

    BufferPtr createBuffer(size_t dataSize, unsigned typeFlags = 0);

private:
    VkPhysicalDevice       m_physicalDevice;
    uint32_t               m_queueFamilyIndex;
    VkDevice               m_device;
    VkQueue                m_queue;
    VkCommandPool          m_commandPool;
    VkCommandBuffer        m_commandBuffer;
    VkFence                m_fence;
    ShaderModules          m_shaderModules;
    VkDescriptorSetLayout  m_descriptorSetLayout;
    VkDescriptorPool       m_descriptorPool;
    VkDescriptorSet        m_descriptorSet;
    VkPipelineLayout       m_pipelineLayout;
    Pipelines              m_pipelines;
    VulkanWorkgroups       m_workgroups;
    size_t                 m_shaderSize;
    long                   m_compileTime;
    long                   m_computeTime;
    BufferPtr              m_bufferA;
    BufferPtr              m_bufferB;
    BufferPtr              m_bufferR;
    BufferPtr              m_bufferParams;
    BufferPtr              m_bufferTemp;
    BufferPtr              m_bufferTemp2;
};

#endif // VULKAN_PIPELINE_H
