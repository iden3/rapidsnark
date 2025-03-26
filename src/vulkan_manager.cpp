#include "vulkan_manager.h"
#include <iostream>
#include <vector>

VulkanManager::VulkanManager(bool enableExceptions)
    : m_instance(VK_NULL_HANDLE)
    , m_physicalDevice(VK_NULL_HANDLE)
    , m_device(VK_NULL_HANDLE)
    , m_enableExceptions(enableExceptions)
    , m_isValid(false)
{
    try {
        initInstance();
        initPhysicalDevice();
        initQueueFamilyIndex();
        initDevice();

    } catch (...) {
        destroy();

        if (enableExceptions) {
            throw;
        }
    }

    m_isValid = true;
}

VulkanManager::~VulkanManager()
{
    destroy();
}

void VulkanManager::destroy()
{
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

VulkanManager::PipelinePtr VulkanManager::createPipeline(
    const char               *shaderPath,
    const VulkanMemoryLayout &memoryLayout,
    uint32_t                  groupCount)
{
    if (!m_isValid) {
        return std::shared_ptr<VulkanPipeline>(nullptr);
    }

    try {
        return std::make_shared<VulkanPipeline>(m_physicalDevice, m_device, m_queueFamilyIndex,
                                                shaderPath, memoryLayout, groupCount);

    } catch (...) {
        if (m_enableExceptions) {
            throw;
        }
    }

    return std::shared_ptr<VulkanPipeline>(nullptr);
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
    printStr(deviceProperties.limits.maxStorageBufferRange);
    printStr(deviceProperties.limits.maxUniformBufferRange);
    printStr(deviceProperties.limits.maxPushConstantsSize);
    printStr(deviceProperties.limits.maxBoundDescriptorSets);
    printStr(deviceProperties.limits.maxPerStageResources);
    printStr(deviceProperties.limits.maxPerStageDescriptorStorageBuffers);
    printStr(deviceProperties.limits.maxPerStageDescriptorUniformBuffers);
    printStr(deviceProperties.limits.maxDescriptorSetStorageBuffers);
    printStr(deviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
    printStr(deviceProperties.limits.maxDescriptorSetUniformBuffers);
    printStr(deviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
    printStr(deviceProperties.limits.maxMemoryAllocationCount);
    printStr(deviceProperties.limits.maxComputeSharedMemorySize);
    printStr(deviceProperties.limits.maxComputeWorkGroupInvocations);
    printStr(deviceProperties.limits.maxComputeWorkGroupCount[0]);
    printStr(deviceProperties.limits.maxComputeWorkGroupCount[1]);
    printStr(deviceProperties.limits.maxComputeWorkGroupCount[2]);
    printStr(deviceProperties.limits.maxComputeWorkGroupSize[0]);
    printStr(deviceProperties.limits.maxComputeWorkGroupSize[1]);
    printStr(deviceProperties.limits.maxComputeWorkGroupSize[2]);
    printStr(deviceProperties.limits.minMemoryMapAlignment);
    printStr(deviceProperties.limits.minStorageBufferOffsetAlignment);
    printStr(deviceProperties.limits.minUniformBufferOffsetAlignment);
    printStr(deviceProperties.limits.optimalBufferCopyOffsetAlignment);
    printStr(deviceProperties.limits.nonCoherentAtomSize);

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
