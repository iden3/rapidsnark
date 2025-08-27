#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/fq.glsl"

#define Point       Element
#define PointZero   ElementZero
#define AssignPoint AssignElement

layout (local_size_x = 64) in;

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
    uint workgroupSize;
};

layout(binding = 3) buffer bufR     { Point  chunks[]; };
layout(binding = 4) buffer bufTemp  { uint   slicedScalars[]; };
layout(binding = 5) buffer bufTemp2 { Point  buckets[]; };

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main() {

    const int q = 4;
    const int r = nBuckets / q;

    const uint k = threadIdx;
    const uint s = chunkIdx*workgroupSize + k*q;

    for (int i = 1; i < r; i <<= 1) {

        if (k % (2*i) == 0) {
            add(buckets[s+0], buckets[s+0], buckets[s + i*q+0]);
            add(buckets[s+1], buckets[s+1], buckets[s + i*q+1]);
        }
        barrier();
    }

    if (threadIdx == 0) {
        Point t;
        add(t, buckets[s + 0], buckets[s + 1]);

        AssignPoint(chunks[chunkIdx], t, N);
    }
}
