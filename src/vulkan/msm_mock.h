#ifndef MSM_MOCK_H
#define MSM_MOCK_H

#include <cstdint>
#include "fq.hpp"
#include "exp.hpp"
#include "msm.hpp"
#include <iostream>

class ThreadPool;

template <typename Curve>
class MSM_Mock {

    Curve &g;
    uint64_t nPoints;
    typename Curve::PointAffine *bases;
    uint8_t *scalars;
    uint64_t scalarSize;
    ThreadPool &threadPool;

    uint64_t bitsPerChunk;
    uint64_t nThreads;
    uint64_t nChunks;
    uint64_t nBuckets;

public:
    using Buckets = std::vector<typename Curve::Point>;
    using Chunks  = std::vector<typename Curve::Point>;
    using Slices  = std::vector<int32_t>;

private:
    uint32_t getBucketIndex(uint32_t scalarIdx, uint32_t chunkIdx) const {
        uint32_t bitStart = chunkIdx*bitsPerChunk;
        uint32_t byteStart = bitStart/8;
        uint32_t efectiveBitsPerChunk = bitsPerChunk;

        if (byteStart > scalarSize-4) byteStart = scalarSize - 4;
        if (bitStart + bitsPerChunk > scalarSize*8) efectiveBitsPerChunk = scalarSize*8 - bitStart;

        uint32_t shift = bitStart - byteStart*8;
        uint32_t v = *(uint32_t *)(scalars + scalarIdx*scalarSize + byteStart);

        v = v >> shift;
        v = v & ( ((uint32_t)1 << efectiveBitsPerChunk) - 1);

        return uint32_t(v);
    }

    uint32_t getBucketIndex8(uint32_t scalarIdx, uint32_t chunkIdx) const {
        uint32_t wordNum = chunkIdx / 4;
        uint32_t byteNum = chunkIdx % 4;
        uint32_t shift = byteNum * 8;

        uint32_t word = ((uint32_t *)scalars)[scalarIdx*8 + wordNum];

        word = (word >> shift) & 0xFF;

        return word;
    }

public:
    MSM_Mock(Curve &_g,
              typename Curve::PointAffine *bases,
              uint8_t* scalars,
              uint64_t scalarSize,
              uint64_t n,
              ThreadPool &threadPool,
              uint64_t nBitsPerChunk = 0)
        : g(_g)
        , nPoints(n)
        , bases(bases)
        , scalars(scalars)
        , scalarSize(scalarSize)
        , threadPool(threadPool)
    {
        MSMParams msmParams(n, scalarSize, nBitsPerChunk);

        nThreads     = threadPool.getThreadCount();
        bitsPerChunk = msmParams.getBitsPerChunk();
        nChunks      = msmParams.getChunkCount();
        nBuckets     = msmParams.getBucketCount();
    }

    uint64_t getPointCount()   const { return nPoints; }
    uint64_t getScalarSize()   const { return scalarSize; }
    uint64_t getBitsPerChunk() const { return bitsPerChunk; }
    uint64_t getChunkCount()   const { return nChunks; }
    uint64_t getBucketCount()  const { return nBuckets; }
    uint64_t getThreadCount()  const { return nThreads; }

    void run(typename Curve::Point &r)
    {
        if (nPoints == 0) {
            g.copy(r, g.zero());
            return;
        }

        if (nPoints == 1) {
            g.mulByScalar(r, bases[0], scalars, scalarSize);
            return;
        }

        Buckets bucketMatrix(nThreads * nBuckets);
        Chunks  chunks(nChunks);
        Slices  slicedScalars(nChunks * nPoints);

        computeSlices(slicedScalars.data());
        computeChunks(slicedScalars.data(), bucketMatrix.data(), chunks.data());
        computeResult(r, chunks.data());
    }

    void computeSlices(int32_t* slicedScalars);
    void computeChunks(int32_t* slicedScalars, typename Curve::Point* bucketMatrix, typename Curve::Point* chunks);
    void computeResult(typename Curve::Point &r, typename Curve::Point* chunks);
};

struct CurveMock
{
    struct Element {
        FqRawElement v;
    };

    typedef Element Point;
    typedef Element PointAffine;

    Element zero() const { return {0}; }
    Element one()  const { return {1}; }

    Element zeroAffine() const { return {0}; }
    Element oneAffine()  const { return {1}; }

    void copy(Element &r, const Element &a) { Fq_rawCopy(r.v, a.v); }
    void add(Element &r, const Element &a, const Element &b) { Fq_rawAdd(r.v, a.v, b.v); }
    void sub(Element &r, const Element &a, const Element &b) { Fq_rawSub(r.v, a.v, b.v); }
    void dbl(Element &r, const Element &a) { Fq_rawAdd(r.v, a.v, a.v); }

    void mulByScalar(Point &r, Point &base, uint8_t* scalar, unsigned int scalarSize) {
        nafMulByScalar<CurveMock, Point, Point>(*this, r, base, scalar, scalarSize);
    }

    void multiMulByScalarMSM(Point &r, PointAffine *bases, uint8_t* scalars, unsigned int scalarSize,
                             unsigned int n, ThreadPool &threadPool) {

        MSM_Mock<CurveMock> msm(*this, bases, scalars, scalarSize, n, threadPool, 8);
        msm.run(r);
    }
};

#include "msm_mock.cpp"

#endif // MSM_MOCK_H
