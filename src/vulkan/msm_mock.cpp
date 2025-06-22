#include "msm_mock.h"
#include "misc.hpp"
#include <memory>

template <typename Curve>
void MSM_Mock<Curve>::computeSlices(int32_t *slicedScalars)
{
    threadPool.parallelFor(0, nPoints, [&] (int64_t begin, int64_t end, uint64_t idThread) {

        for (int i = begin; i < end; i++) {
            int32_t carry = 0;

            for (int j = 0; j < nChunks; j++) {
                int32_t bucketIndex = getBucketIndex(i, j) + carry;

                if (bucketIndex >= nBuckets) {
                    bucketIndex -= nBuckets*2;
                    carry = 1;
                } else {
                    carry = 0;
                }

                slicedScalars[i*nChunks + j] = bucketIndex;
            }
        }
    });
}

template<typename Curve>
void MSM_Mock<Curve>::computeChunks(int32_t *slicedScalars,
    typename Curve::Point* bucketMatrix,
    typename Curve::Point* chunks)
{
    threadPool.parallelFor(0, nChunks, [&] (int64_t begin, int64_t end, uint64_t idThread) {

        for (int j = begin; j < end; j++) { //chunks

            typename Curve::Point *buckets = &bucketMatrix[idThread*nBuckets];

            for (int i = 0; i < nBuckets; i++) {
                g.copy(buckets[i], g.zero());
            }

            for (int i = 0; i < nPoints; i++) {
                const int bucketIndex = slicedScalars[i*nChunks + j];

                if (bucketIndex > 0) {
                    g.add(buckets[bucketIndex-1], buckets[bucketIndex-1], bases[i]);

                } else if (bucketIndex < 0) {
                    g.sub(buckets[-bucketIndex-1], buckets[-bucketIndex-1], bases[i]);
                }
            }

            typename Curve::Point t, tmp;

            g.copy(t, buckets[nBuckets - 1]);
            g.copy(tmp, t);

            for (int i = nBuckets - 2; i >= 0 ; i--) {
                g.add(tmp, tmp, buckets[i]);
                g.add(t, t, tmp);
            }

            chunks[j] = t;
        }
    });
}

template<typename Curve>
void MSM_Mock<Curve>::computeResult(typename Curve::Point &r, typename Curve::Point* chunks)
{
    g.copy(r, chunks[nChunks - 1]);

    for (int j = nChunks - 2; j >= 0; j--) {
        for (int i = 0; i < bitsPerChunk; i++) {
            g.dbl(r, r);
        }
        g.add(r, r, chunks[j]);
    }
}
