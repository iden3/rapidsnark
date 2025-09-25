#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/g1.glsl"

#define Point       CurvePoint
#define PointZero   CurvePointZero
#define AssignPoint AssignCurvePoint

layout (local_size_x = 64) in;

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
};

layout(binding = 3) buffer bufR     { Point  chunks[]; };
layout(binding = 4) buffer bufTemp  { uint   slicedScalars[]; };
layout(binding = 5) buffer bufTemp2 { Point  buckets[]; };

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main()
{
    const uint s = chunkIdx * nBuckets;

    for (int l = nBuckets / 2; l > 1; l >>= 1) {
        const uint idx = s + threadIdx * 2;

        if (threadIdx * 2 < l) {
            add(buckets[idx], buckets[idx], buckets[idx + l]);
        }

        barrier();
    }

    if (threadIdx == 0) {
        AssignPoint(chunks[chunkIdx], buckets[s]);
    }
}
