#include "vulkan_buffer.h"
#include <cstring>
#include <stdexcept>

VulkanBuffer::VulkanBuffer(VkPhysicalDevice physicalDevice, VkDevice device, void *data, size_t dataSize) :
    m_physicalDevice(physicalDevice),
    m_device(device),
    m_data(data),
    m_dataSize(dataSize),
    m_primaryBuffer(VK_NULL_HANDLE),
    m_primaryMemory(VK_NULL_HANDLE),
    m_stagingBuffer(VK_NULL_HANDLE),
    m_stagingMemory(VK_NULL_HANDLE)
{
    try {
        createMemBuffer(m_primaryBuffer, primaryBufferUsage());
        allocMemBuffer(m_primaryMemory, m_primaryBuffer, primaryMemoryProperties());

        createMemBuffer(m_stagingBuffer, stagingBufferUsage());
        allocMemBuffer(m_stagingMemory, m_stagingBuffer, stagingMemoryProperties());
        mapMemBuffer(m_stagingMemory);

    } catch (...) {
        destroy();
        throw;
    }
}

VulkanBuffer::~VulkanBuffer()
{
    destroy();
}

void VulkanBuffer::destroy()
{
    if(m_stagingMemory != VK_NULL_HANDLE) {
        vkUnmapMemory(m_device, m_stagingMemory);
        vkFreeMemory(m_device, m_stagingMemory, nullptr);
    }

    if (m_stagingBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(m_device, m_stagingBuffer, nullptr);
    }

    if(m_primaryMemory != VK_NULL_HANDLE) {
        vkFreeMemory(m_device, m_primaryMemory, nullptr);
    }

    if (m_primaryBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(m_device, m_primaryBuffer, nullptr);
    }
}

VkBufferUsageFlags VulkanBuffer::primaryBufferUsage() const
{
    return VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
           VK_BUFFER_USAGE_TRANSFER_DST_BIT |
           VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
}

VkBufferUsageFlags VulkanBuffer::stagingBufferUsage() const
{
    return VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
           VK_BUFFER_USAGE_TRANSFER_DST_BIT;
}

VkMemoryPropertyFlagBits VulkanBuffer::primaryMemoryProperties() const
{
    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
}

VkMemoryPropertyFlagBits VulkanBuffer::stagingMemoryProperties() const
{
    return VkMemoryPropertyFlagBits(
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}

void VulkanBuffer::createMemBuffer(VkBuffer &buffer, VkBufferUsageFlags usage)
{
    VkBufferCreateInfo createInfo =
    {
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        nullptr,
        0,
        m_dataSize,
        usage,
        VK_SHARING_MODE_EXCLUSIVE,
        0, nullptr
    };

    vkCreateBuffer(m_device, &createInfo, nullptr, &buffer);
}

void VulkanBuffer::allocMemBuffer(VkDeviceMemory &memory, VkBuffer buffer,
                                  VkMemoryPropertyFlagBits reqProperties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    VkMemoryRequirements bufferReqs;

    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);
    vkGetBufferMemoryRequirements(m_device, buffer, &bufferReqs);

    for (uint32_t typeIndex = 0; typeIndex < memProperties.memoryTypeCount; ++typeIndex ) {

        const uint32_t propertyTypeBit = (1 << typeIndex);
        const bool isFitType        = (bufferReqs.memoryTypeBits & propertyTypeBit);
        const bool isFitProperities = ((memProperties.memoryTypes[typeIndex].propertyFlags & reqProperties) == reqProperties);

        if (!isFitType || !isFitProperities) {
            continue;
        }

        VkMemoryAllocateInfo allocInfo = {
            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            nullptr,
            bufferReqs.size,
            typeIndex
        };

        VkResult result = vkAllocateMemory(m_device, &allocInfo, nullptr, &memory);

        if(result == VK_SUCCESS) {
            break;
        }
    }

    if (memory == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to allocate memory for a buffer");
    }

    VkResult result = vkBindBufferMemory(m_device, buffer, memory, 0);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("failed to bind memory object to a buffer");
    }
}

void VulkanBuffer::mapMemBuffer(VkDeviceMemory memory)
{
    VkResult result = vkMapMemory(m_device, memory, 0, m_dataSize, 0, &m_mappedData);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("failed to map memory object");
    }
}

void VulkanBuffer::flushMemBuffer(VkDeviceMemory memory)
{
    VkMappedMemoryRange memoryRange = {
        VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        nullptr,
        memory,
        0,
        m_dataSize
    };

    VkResult result = vkFlushMappedMemoryRanges(m_device, 1, &memoryRange);

    if( result != VK_SUCCESS) {
        throw std::runtime_error("failed to flush mapped memory");
    }
}

void VulkanBuffer::copyFromLocalBuffer()
{
    std::memcpy(m_mappedData, m_data, m_dataSize);

    flushMemBuffer(m_stagingMemory);
}

void VulkanBuffer::copyToLocalBuffer()
{
    std::memcpy(m_data, m_mappedData, m_dataSize);
}

void VulkanBuffer::recordCopyToDevice(VkCommandBuffer commandBuffer)
{
    VkBufferCopy copyInfo = {
        0, 0, m_dataSize
    };

    vkCmdCopyBuffer(commandBuffer, m_stagingBuffer, m_primaryBuffer, 1, &copyInfo);
}

void VulkanBuffer::recordCopyFromDevice(VkCommandBuffer commandBuffer)
{
    VkBufferCopy copyInfo = {
        0, 0, m_dataSize
    };

    vkCmdCopyBuffer(commandBuffer, m_primaryBuffer, m_stagingBuffer, 1, &copyInfo);
}

void VulkanBuffer::recordMemoryBarrier(
    VkCommandBuffer commandBuffer,
    VkAccessFlagBits srcAccessMask,
    VkAccessFlagBits dstAccessMask,
    VkPipelineStageFlagBits srcStageMask,
    VkPipelineStageFlagBits dstStageMask)
{
    VkBufferMemoryBarrier barrier = {
        VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
        nullptr,
        srcAccessMask,
        dstAccessMask,
        VK_QUEUE_FAMILY_IGNORED,
        VK_QUEUE_FAMILY_IGNORED,
        m_primaryBuffer,
        0,
        VK_WHOLE_SIZE
    };

    vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, 0,
                         0, nullptr, 1, &barrier, 0, nullptr);
}

VkDescriptorBufferInfo VulkanBuffer::descriptorInfo() const
{
    VkDescriptorBufferInfo bufferInfo = {
        m_primaryBuffer,
        0,
        VK_WHOLE_SIZE
    };

    return bufferInfo;
}

VkWriteDescriptorSet VulkanBuffer::updateDescriptorSet(VkDescriptorSet descriptorSet, uint32_t binding)
{
    m_bufferInfo = descriptorInfo();

    VkWriteDescriptorSet writeDescriptors =  {
        VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        nullptr,
        descriptorSet,
        binding,
        0,
        1,
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        nullptr,
        &m_bufferInfo,
        nullptr
    };

    return writeDescriptors;
}
