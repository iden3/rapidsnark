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
    const uint ofs = chunkIdx * nBuckets;
    const uint s = ofs + threadIdx * q;

    Point a = buckets[ofs + (threadIdx * q + q) % nBuckets];
    Point b = a;

    for (int i = q - 1; i >= 1; i--) {
        add(a, a, buckets[s + i]);
        add(b, b, a);
    }

    buckets[s+0] = a;
    buckets[s+2] = b;
}
