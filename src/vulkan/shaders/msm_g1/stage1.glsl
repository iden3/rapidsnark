#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/g1.glsl"

#define Point       CurvePoint
#define PointAffine CurvePointAffine
#define PointZero   CurvePointZero
#define AssignPoint AssignCurvePoint

layout (local_size_x = 256) in;

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
};

layout(binding = 2) buffer readonly bufB { PointAffine bases[]; };
layout(binding = 3) buffer bufR          { Point       chunks[]; };
layout(binding = 4) buffer bufTemp       { uint        slicedScalars[]; };
layout(binding = 5) buffer bufTemp2      { Point       buckets[]; };

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main()
{
    Point bucket = PointZero;

    for (uint i = 0; i < nPoints; i++) {

        uint bucketIdx = slicedScalars[chunkIdx * nPoints + i];

        if (bucketIdx == 0 || bucketIdx != threadIdx) {
            continue;
        }

        add(bucket, bucket, bases[i]);
    }

    AssignPoint(buckets[chunkIdx * nBuckets + threadIdx], bucket);
}
