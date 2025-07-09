#version 430

layout (local_size_x = 128) in;

const int N = 8;

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
    uint workgroupSize;
};

layout(binding = 1) buffer readonly bufA { uint scalars[]; };
layout(binding = 4) buffer bufTemp       { int  slicedScalars[]; };

#define pointIdx gl_GlobalInvocationID.x

void main() {

    if (gl_GlobalInvocationID.x >= nPoints) {
        return;
    }

    int carry = 0;

    for (uint j = 0; j < nChunks; j++) {
        uint wordNum = j / 4;
        uint byteNum = j % 4;
        uint shift = byteNum * 8;

        uint word = scalars[pointIdx * 8 + wordNum];

        word = (word >> shift) & 0xFF;

        int bucketIndex = int(word) + carry;

        if (bucketIndex >= nBuckets) {
            bucketIndex -= nBuckets * 2;
            carry = 1;
        } else {
            carry = 0;
        }

        slicedScalars[j * nPoints + pointIdx] = bucketIndex;
    }
}
