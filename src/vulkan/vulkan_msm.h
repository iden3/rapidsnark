#ifndef VULKAN_MSM_H
#define VULKAN_MSM_H

#include "vulkan_manager.h"
#include <string>
#include <cstdint>
#include <cstring>

struct MsmShaderParams
{
    uint32_t nPoints;
    uint32_t scalarSize;
    uint32_t bitsPerChunk;
    uint32_t nChunks;
    uint32_t nBuckets;
};

class VulkanMSM
{
    static const uint32_t bitsPerChunk = 8;

public:
    VulkanMSM(bool enableMgrExceptions = true)
        : m_vkMgr(enableMgrExceptions)
    {}

    bool isValid() const { return m_vkMgr.isValid(); }

    void init(const std::string &shaderPath,
              void              *bases,
              void              *scalars,
              uint32_t           pointSize,
              uint32_t           affinePointSize,
              uint32_t           scalarSize,
              uint32_t           nPoints);

    void run();

    template<typename Curve>
    void computeResult(Curve &g, void *result)
    {
        typename Curve::Point r;

        reduceChunks(g, r, m_chunks.data(), m_params.nChunks, m_params.bitsPerChunk);

        std::memcpy(result, &r, sizeof(r));
    }

    template<typename Curve>
    void computeResultAffine(Curve &g, void *result)
    {
        typename Curve::Point r;
        typename Curve::PointAffine rAffine;

        reduceChunks(g, r, m_chunks.data(), m_params.nChunks, m_params.bitsPerChunk);

        g.copy(rAffine, r);

        std::memcpy(result, &rAffine, sizeof(rAffine));
    }

    VulkanPipeline::Perf getPerf() const { return m_pipeline->getPerf(); }

private:
    template<typename Curve>
    void reduceChunks(Curve &g, typename Curve::Point &r, void *chunksData, uint32_t nChunks, uint32_t bitsPerChunk)
    {
        auto chunks = (typename Curve::Point*)chunksData;

        g.copy(r, chunks[nChunks - 1]);

        for (int j = nChunks - 2; j >= 0; j--) {
            for (int i = 0; i < bitsPerChunk; i++) {
                g.dbl(r, r);
            }
            g.add(r, r, chunks[j]);
        }
    }

    MsmShaderParams createShaderParams(uint32_t nPoints, uint32_t scalarSize);

private:
    VulkanManager              m_vkMgr;
    VulkanManager::PipelinePtr m_pipeline;
    MsmShaderParams            m_params;
    std::vector<char>          m_chunks;
    VulkanBufferView           m_vA;
    VulkanBufferView           m_vB;
    VulkanBufferView           m_vR;
    long                       m_timeCompile;
    long                       m_timeCompute;
};

#endif // VULKAN_MSM_H
