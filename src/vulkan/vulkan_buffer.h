#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>
#include <vector>

class VulkanBuffer
{
public:
    enum {Uniform = 0x1, DeviceOnly = 0x2};

public:
    VulkanBuffer(VkPhysicalDevice physicalDevice, VkDevice device, size_t size, unsigned typeFlags = 0);
    ~VulkanBuffer();

    VkWriteDescriptorSet updateDescriptorSet(VkDescriptorSet descriptorSet, uint32_t binding);

    void recordCopyToDevice(VkCommandBuffer commandBuffer);
    void recordCopyFromDevice(VkCommandBuffer commandBuffer);

    void fill(VkCommandBuffer commandBuffer, uint32_t data);
    void update(VkCommandBuffer commandBuffer, const void *data, size_t size);

    void recordMemoryBarrier(
      VkCommandBuffer commandBuffer,
      VkAccessFlagBits srcAccessMask,
      VkAccessFlagBits dstAccessMask,
      VkPipelineStageFlagBits srcStageMask,
      VkPipelineStageFlagBits dstStageMask);

    void copyFromLocalBuffer(const void *data, size_t dataSize);
    void copyToLocalBuffer(void *data, size_t dataSize);

    size_t size() const { return m_size; }

private:
   void build();
   void destroy();

    void createMemBuffer(VkBuffer &buffer, VkBufferUsageFlags usage);
    void allocMemBuffer(VkDeviceMemory &memory, VkBuffer buffer,
                        VkMemoryPropertyFlagBits reqProperties,
                        VkMemoryPropertyFlags &memoryFlags);
    void bindMemBuffer(VkDeviceMemory memory, VkBuffer buffer);
    void mapMemBuffer(VkDeviceMemory memory);
    void flushMemBuffer(VkDeviceMemory memory, VkMemoryPropertyFlags memoryFlags);

private:
    VkBufferUsageFlags primaryBufferUsage() const;
    VkBufferUsageFlags stagingBufferUsage() const;
    VkBufferUsageFlags uniformBufferUsage() const;
    VkMemoryPropertyFlagBits sharedMemoryProperties() const;
    VkMemoryPropertyFlagBits primaryMemoryProperties() const;
    VkMemoryPropertyFlagBits stagingMemoryProperties() const;
    VkDescriptorBufferInfo descriptorInfo() const;

private:
    int              m_typeFlags;
    VkPhysicalDevice m_physicalDevice;
    VkDevice         m_device;
    size_t           m_size;
    void*            m_mappedData;

    VkBuffer         m_primaryBuffer;
    VkBuffer         m_stagingBuffer;
    VkDeviceMemory   m_primaryMemory;
    VkDeviceMemory   m_stagingMemory;

    VkMemoryPropertyFlags  m_primaryMemoryFlags;
    VkMemoryPropertyFlags  m_stagingMemoryFlags;

    VkDescriptorBufferInfo m_bufferInfo;
};

#endif // VULKAN_BUFFER_H
