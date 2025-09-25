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
};

layout(binding = 3) buffer bufR     { Point  chunks[]; };
layout(binding = 4) buffer bufTemp  { uint   slicedScalars[]; };
layout(binding = 5) buffer bufTemp2 { Point  buckets[]; };

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main()
{
    const int  q = 4;
    const uint s = chunkIdx * nBuckets + threadIdx * q;
    const uint e = q * threadIdx;

    Point a = PointZero;

    for (int i = findMSB(e); i >= 0; i--) {
        add(a, a, a);

        if (bitfieldExtract(e, i, 1) == 1) {
            add(a, a, buckets[s+0]);
        }
    }

    buckets[s+0] = a;
}
