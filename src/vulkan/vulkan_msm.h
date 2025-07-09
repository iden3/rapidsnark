#ifndef VULKAN_MSM_H
#define VULKAN_MSM_H

#include "vulkan_manager.h"
#include "msm.hpp"
#include <cstdint>
#include <cstring>

class VulkanMSM
{
    static const uint32_t bitsPerChunk = 8;
    static const uint32_t workgroupSize = 128;

public:
    VulkanMSM(bool enableMgrExceptions = true)
        : m_vkMgr(enableMgrExceptions)
        , m_shaderSize(0)
    {}

    bool isValid() const { m_vkMgr.isValid(); }

    void run(const std::string &shaderPath,
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

        m_params = createParams(nPoints, scalarSize);
        m_chunks.clear();
        m_chunks.resize(m_params.nChunks * pointSize);

        const uint32_t     slicedScalarsSize = nPoints * m_params.nChunks * sizeof(uint32_t);
        VulkanBufferView   vR = {m_chunks.data(), m_chunks.size()};
        VulkanBufferView   vA = {scalars, scalarSize * nPoints};
        VulkanBufferView   vB = {bases, affinePointSize * nPoints};
        VulkanMemoryLayout memoryLayout = {vR.size, vA.size, vB.size, slicedScalarsSize};

        auto vkPipeline = m_vkMgr.createPipeline(shaderPath, memoryLayout, m_params);

        if (!vkPipeline) {
            throw std::runtime_error("failed to create vulkan pipeline");
        }

        m_shaderSize = vkPipeline->shaderSize();

        vkPipeline->run(vR, vA, vB);
    }

    template<typename Curve>
    void computeResult(Curve &g, void *result)
    {
        reduceChunks(g, result, m_chunks.data(), m_params.nChunks, m_params.bitsPerChunk);
    }

    size_t getLastShaderSize() const { return m_shaderSize; }

private:
    template<typename Curve>
    void reduceChunks(Curve &g, void *result, void *chunksData, uint32_t nChunks, uint32_t bitsPerChunk)
    {
        typename Curve::Point r;
        auto chunks = (typename Curve::Point*)chunksData;

        g.copy(r, chunks[nChunks - 1]);

        for (int j = nChunks - 2; j >= 0; j--) {
            for (int i = 0; i < bitsPerChunk; i++) {
                g.dbl(r, r);
            }
            g.add(r, r, chunks[j]);
        }

        std::memcpy(result, &r, sizeof(r));
    }

    ShaderParams createParams(uint32_t nPoints, uint32_t scalarSize)
    {
        MSMParams msmParams(nPoints, scalarSize, bitsPerChunk);

        return { nPoints,
                 scalarSize,
                 (uint32_t)msmParams.getBitsPerChunk(),
                 (uint32_t)msmParams.getChunkCount(),
                 (uint32_t)msmParams.getBucketCount(),
                 workgroupSize
               };
    }

private:
    VulkanManager     m_vkMgr;
    ShaderParams      m_params;
    size_t            m_shaderSize;
    std::vector<char> m_chunks;
};

#endif // VULKAN_MSM_H
