#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/g2.glsl"

#define Point       CurvePoint
#define PointZero   CurvePointZero
#define AssignPoint AssignCurvePoint

layout (local_size_x = 1) in;

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

    Point t = buckets[s + nBuckets - 1];
    Point tmp = t;

    for (int i = nBuckets - 2; i >= 1 ; i--) {
        add(tmp, tmp, buckets[s + i]);
        add(t, t, tmp);
    }

    chunks[chunkIdx] = t;
}
