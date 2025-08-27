#version 460

layout (local_size_x = 256) in;

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
    uint workgroupSize;
};

layout(binding = 1) buffer readonly bufA { uint scalars[]; };
layout(binding = 4) buffer bufTemp       { uint slicedScalars[]; };

#define pointIdx gl_GlobalInvocationID.x

void main() {

    if (gl_GlobalInvocationID.x >= nPoints) {
        return;
    }

    int carry = 0;

    for (int j = 0; j < nChunks; j++) {
        int wordNum = j / 4;
        int byteNum = j % 4;
        int shift = byteNum * 8;

        uint word = scalars[pointIdx * 8 + wordNum];

        uint bucketIdx = bitfieldExtract(word, shift, 8);

        slicedScalars[j * nPoints + pointIdx] = bucketIdx;
    }
}
