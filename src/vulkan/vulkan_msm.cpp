#include "vulkan_msm.h"
#include "msm.hpp"
#include "utils.h"

void VulkanMSM::init(const std::string &shaderPath,
          void              *bases,
          void              *scalars,
          uint32_t           pointSize,
          uint32_t           affinePointSize,
          uint32_t           scalarSize,
          uint32_t           nPoints)
{
    if (!m_vkMgr.isValid()) {
        throw std::runtime_error("invalid Vulkan manager");
    }

    m_params = createShaderParams(nPoints, scalarSize);
    m_chunks.clear();
    m_chunks.resize(m_params.nChunks * pointSize);

    m_vR = { m_chunks.data(), m_chunks.size() };
    m_vA = { scalars, scalarSize * nPoints };
    m_vB = { bases, affinePointSize * nPoints };

    VulkanWorkgroups workgroups = { div_ceil(nPoints, 128),
                                    m_params.nChunks,
                                    m_params.nChunks,
                                    m_params.nChunks,
                                    m_params.nChunks };

    const uint32_t slicedScalarsSize = nPoints * m_params.nChunks * sizeof(uint32_t);
    const uint32_t bucketsSize = m_params.nBuckets * m_params.nChunks * pointSize;

    VulkanMemoryLayout memoryLayout = {sizeof(m_params), m_vR.size, m_vA.size, m_vB.size, slicedScalarsSize, bucketsSize};

    m_pipeline = m_vkMgr.createPipeline(shaderPath, workgroups, memoryLayout, &m_params);

    if (!m_pipeline) {
        throw std::runtime_error("failed to create vulkan pipeline");
    }
}

void VulkanMSM::run()
{
    m_pipeline->run(m_vR, m_vA, m_vB);
}

MsmShaderParams VulkanMSM::createShaderParams(uint32_t nPoints, uint32_t scalarSize)
{
    MSMParams msmParams(nPoints, scalarSize, bitsPerChunk);

    return { nPoints,
             scalarSize,
             (uint32_t)msmParams.getBitsPerChunk(),
             (uint32_t)msmParams.getChunkCount(),
             (uint32_t)msmParams.getBucketCountNoNaf(),
           };
}
