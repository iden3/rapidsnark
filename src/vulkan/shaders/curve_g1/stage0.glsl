#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/g1.glsl"

layout (local_size_x = 64) in;

layout(binding = 0) uniform bufParams {
    uint IterCount;
    uint PointCount;
};

layout(binding = 1) buffer  readonly bufA { CurvePoint A[]; };
layout(binding = 2) buffer  readonly bufB { CurvePoint B[]; };
layout(binding = 3) buffer  bufR          { CurvePoint R[]; };

void main() {
    uint x = gl_GlobalInvocationID.x;

    if (x >= PointCount) {
        return;
    }

    const CurvePoint a = A[x];
    const CurvePoint b = B[x];
    CurvePoint r;

    for (int i = 0; i < IterCount; i++) {
        add(r, a, b);
    }

    R[x] = r;
}
