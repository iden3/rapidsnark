#version 460
#extension GL_GOOGLE_include_directive : require

#include "math/fq.glsl"

layout (local_size_x = 64) in;

layout(binding = 0) uniform bufParams {
    uint IterCount;
    uint PointCount;
};

layout(binding = 1) buffer  readonly bufA { Element A[]; };
layout(binding = 2) buffer  readonly bufB { Element B[]; };
layout(binding = 3) buffer  bufR          { Element R[]; };

void main() {
    uint x = gl_GlobalInvocationID.x;

    if (x >= PointCount) {
        return;
    }

    const Element a = A[x];
    const Element b = B[x];
    Element r;

    for (int i = 0; i < IterCount; i++) {
        add(r, a, b);
    }

    AssignElement(R[x], r, N);
}
