#include "vulkan_buffer.h"
#include <cstring>
#include <stdexcept>
#include <cassert>

VulkanBuffer::VulkanBuffer(VkPhysicalDevice physicalDevice, VkDevice device, size_t size, unsigned typeFlags)
    : m_typeFlags(typeFlags)
    , m_physicalDevice(physicalDevice)
    , m_device(device)
    , m_size(size)
    , m_mappedData(nullptr)
    , m_primaryBuffer(VK_NULL_HANDLE)
    , m_primaryMemory(VK_NULL_HANDLE)
    , m_primaryMemoryFlags(0)
    , m_stagingBuffer(VK_NULL_HANDLE)
    , m_stagingMemory(VK_NULL_HANDLE)
    , m_stagingMemoryFlags(0)
{
    try {
        build();

    } catch (...) {
        destroy();
        throw;
    }
}

VulkanBuffer::~VulkanBuffer()
{
    destroy();
}

void VulkanBuffer::build()
{
    const VkBufferUsageFlags primaryUsage = (m_typeFlags & Uniform) ? uniformBufferUsage() : primaryBufferUsage();

    if (m_typeFlags & DeviceOnly) {
        createMemBuffer(m_primaryBuffer, primaryUsage);
        allocMemBuffer(m_primaryMemory, m_primaryBuffer, primaryMemoryProperties(), m_primaryMemoryFlags);

        if (m_primaryMemory == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to allocate memory for a buffer");
        }

        bindMemBuffer(m_primaryMemory, m_primaryBuffer);
        return;
    }

    createMemBuffer(m_primaryBuffer, primaryUsage);
    allocMemBuffer(m_primaryMemory, m_primaryBuffer, sharedMemoryProperties(), m_primaryMemoryFlags);

    if (m_primaryMemory != VK_NULL_HANDLE) {

        bindMemBuffer(m_primaryMemory, m_primaryBuffer);
        mapMemBuffer(m_primaryMemory);

    } else {
        allocMemBuffer(m_primaryMemory, m_primaryBuffer, primaryMemoryProperties(), m_primaryMemoryFlags);

        if (m_primaryMemory == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to allocate memory for a buffer");
        }

        bindMemBuffer(m_primaryMemory, m_primaryBuffer);

        createMemBuffer(m_stagingBuffer, stagingBufferUsage());
        allocMemBuffer(m_stagingMemory, m_stagingBuffer, stagingMemoryProperties(), m_stagingMemoryFlags);
        bindMemBuffer(m_stagingMemory, m_stagingBuffer);
        mapMemBuffer(m_stagingMemory);
    }
}

void VulkanBuffer::destroy()
{
    if(m_stagingMemory != VK_NULL_HANDLE) {
        vkUnmapMemory(m_device, m_stagingMemory);
        vkFreeMemory(m_device, m_stagingMemory, nullptr);

    } else if(m_primaryMemory != VK_NULL_HANDLE && !(m_typeFlags & DeviceOnly)) {
        vkUnmapMemory(m_device, m_primaryMemory);
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

VkBufferUsageFlags VulkanBuffer::uniformBufferUsage() const
{
    return VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
           VK_BUFFER_USAGE_TRANSFER_DST_BIT |
           VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
}

VkMemoryPropertyFlagBits VulkanBuffer::sharedMemoryProperties() const
{
    return VkMemoryPropertyFlagBits(
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT |
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
}

VkMemoryPropertyFlagBits VulkanBuffer::primaryMemoryProperties() const
{
    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
}

VkMemoryPropertyFlagBits VulkanBuffer::stagingMemoryProperties() const
{
    return VkMemoryPropertyFlagBits(
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
}

void VulkanBuffer::createMemBuffer(VkBuffer &buffer, VkBufferUsageFlags usage)
{
    VkBufferCreateInfo createInfo =
    {
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        nullptr,
        0,
        m_size,
        usage,
        VK_SHARING_MODE_EXCLUSIVE,
        0, nullptr
    };

    vkCreateBuffer(m_device, &createInfo, nullptr, &buffer);
}

void VulkanBuffer::allocMemBuffer(
    VkDeviceMemory           &memory,
    VkBuffer                  buffer,
    VkMemoryPropertyFlagBits  reqProperties,
    VkMemoryPropertyFlags    &memoryFlags)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    VkMemoryRequirements bufferReqs;

    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);
    vkGetBufferMemoryRequirements(m_device, buffer, &bufferReqs);

    for (uint32_t typeIndex = 0; typeIndex < memProperties.memoryTypeCount; ++typeIndex ) {

        const uint32_t              propertyTypeBit = (1 << typeIndex);
        const VkMemoryPropertyFlags propertyFlags = memProperties.memoryTypes[typeIndex].propertyFlags;

        const bool isFitType        = (bufferReqs.memoryTypeBits & propertyTypeBit);
        const bool isFitProperities = ((propertyFlags & reqProperties) == reqProperties);

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
            memoryFlags = propertyFlags;
            break;
        }
    }
}


void VulkanBuffer::bindMemBuffer(VkDeviceMemory memory, VkBuffer buffer)
{
    VkResult result = vkBindBufferMemory(m_device, buffer, memory, 0);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("failed to bind memory object to a buffer");
    }
}

void VulkanBuffer::mapMemBuffer(VkDeviceMemory memory)
{
    VkResult result = vkMapMemory(m_device, memory, 0, m_size, 0, &m_mappedData);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("failed to map memory object");
    }
}

void VulkanBuffer::flushMemBuffer(VkDeviceMemory memory, VkMemoryPropertyFlags memoryFlags)
{
    if ((memoryFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0) {
        return;
    }

    VkMappedMemoryRange memoryRange = {
        VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        nullptr,
        memory,
        0,
        m_size
    };

    VkResult result = vkFlushMappedMemoryRanges(m_device, 1, &memoryRange);

    if( result != VK_SUCCESS) {
        throw std::runtime_error("failed to flush mapped memory");
    }
}

void VulkanBuffer::copyFromLocalBuffer(const void *data, size_t dataSize)
{
    assert(dataSize <= m_size);

    std::memcpy(m_mappedData, data, dataSize);

    if (m_stagingMemory != VK_NULL_HANDLE) {
        flushMemBuffer(m_stagingMemory, m_stagingMemoryFlags);
    } else {
        flushMemBuffer(m_primaryMemory, m_primaryMemoryFlags);
    }
}

void VulkanBuffer::copyToLocalBuffer(void *data, size_t dataSize)
{
    assert(dataSize <= m_size);

    std::memcpy(data, m_mappedData, dataSize);
}

void VulkanBuffer::recordCopyToDevice(VkCommandBuffer commandBuffer)
{
    if (m_stagingBuffer == VK_NULL_HANDLE) {
        return;
    }

    VkBufferCopy copyInfo = {
        0, 0, m_size
    };

    vkCmdCopyBuffer(commandBuffer, m_stagingBuffer, m_primaryBuffer, 1, &copyInfo);
}

void VulkanBuffer::recordCopyFromDevice(VkCommandBuffer commandBuffer)
{
    if (m_stagingBuffer == VK_NULL_HANDLE) {
        return;
    }

    VkBufferCopy copyInfo = {
        0, 0, m_size
    };

    vkCmdCopyBuffer(commandBuffer, m_primaryBuffer, m_stagingBuffer, 1, &copyInfo);
}

void VulkanBuffer::fill(VkCommandBuffer commandBuffer, uint32_t data)
{
    vkCmdFillBuffer(commandBuffer, m_primaryBuffer, 0, VK_WHOLE_SIZE, data);
}

void VulkanBuffer::update(VkCommandBuffer commandBuffer, const void *data, size_t size)
{
    assert(size <= 65536);

    vkCmdUpdateBuffer(commandBuffer, m_primaryBuffer, 0, size, data);
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

    const bool isUniform = (m_typeFlags & Uniform);
    const VkDescriptorType descriptorType = isUniform ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
                                                      : VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

    VkWriteDescriptorSet writeDescriptors =  {
        VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        nullptr,
        descriptorSet,
        binding,
        0,
        1,
        descriptorType,
        nullptr,
        &m_bufferInfo,
        nullptr
    };

    return writeDescriptors;
}
