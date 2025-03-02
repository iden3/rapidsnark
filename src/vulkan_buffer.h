#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>
#include <vector>

class VulkanBuffer
{
public:
    VulkanBuffer(VkPhysicalDevice physicalDevice, VkDevice device, void *data, size_t dataSize);
    ~VulkanBuffer();

    VkWriteDescriptorSet updateDescriptorSet(VkDescriptorSet descriptorSet, uint32_t binding);

    void recordCopyToDevice(VkCommandBuffer commandBuffer);
    void recordCopyFromDevice(VkCommandBuffer commandBuffer);

    void recordMemoryBarrier(
      VkCommandBuffer commandBuffer,
      VkAccessFlagBits srcAccessMask,
      VkAccessFlagBits dstAccessMask,
      VkPipelineStageFlagBits srcStageMask,
      VkPipelineStageFlagBits dstStageMask);

    void copyFromLocalBuffer();
    void copyToLocalBuffer();

private:
    void createMemBuffer(VkBuffer &buffer, VkBufferUsageFlags usage);
    void allocMemBuffer(VkDeviceMemory &memory, VkBuffer buffer, VkMemoryPropertyFlagBits reqProperties);
    void mapMemBuffer(VkDeviceMemory memory);
    void flushMemBuffer(VkDeviceMemory memory);

    void destroy();

private:
    VkBufferUsageFlags primaryBufferUsage() const;
    VkBufferUsageFlags stagingBufferUsage() const;
    VkMemoryPropertyFlagBits primaryMemoryProperties() const;
    VkMemoryPropertyFlagBits stagingMemoryProperties() const;
    VkDescriptorBufferInfo descriptorInfo() const;

private:
    VkPhysicalDevice m_physicalDevice;
    VkDevice         m_device;
    void*            m_data;
    size_t           m_dataSize;
    void*            m_mappedData;

    VkBuffer         m_primaryBuffer;
    VkBuffer         m_stagingBuffer;
    VkDeviceMemory   m_primaryMemory;
    VkDeviceMemory   m_stagingMemory;

    VkDescriptorBufferInfo m_bufferInfo;
};

#endif // VULKAN_BUFFER_H
