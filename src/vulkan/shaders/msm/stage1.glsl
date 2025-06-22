#version 430

layout (local_size_x = 128) in;

const int N = 8;

#define Element     uint[N]
#define ZeroElement Element(0,0,0,0, 0,0,0,0);

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint pointSize;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
    uint workgroupSize;
};

layout(binding = 2) buffer readonly bufB { Element bases[]; };
layout(binding = 3) buffer bufR          { Element chunks[]; };
layout(binding = 4) buffer bufTemp       { int slicedScalars[]; };

const Element Fq_rawq = {0xd87cfd47,0x3c208c16,0x6871ca8d,0x97816a91,0x8181585d,0xb85045b6,0xe131a029,0x30644e72};

#define AssignElement(res, arg, size)     \
    for (int i = 0; i < size; i++) {res[i] = arg[i];}

int mp_cmp(Element a, Element b)
{
    for (int i = N - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

uint mp_sub_n(out Element r, Element a, Element b)
{
    uint borrow = 0;

    for (int i = 0; i < N; i++) {
        uint borrow2 = 0;

        r[i] = usubBorrow(a[i], borrow, borrow);
        r[i] = usubBorrow(r[i], b[i], borrow2);
        borrow += borrow2;
    }
    return borrow;
}

uint mp_add_n(out Element r, Element a, Element b)
{
    uint carry = 0;

    for (int i = 0; i < N; i++) {
        uint carry2 = 0;

        r[i] = uaddCarry(a[i], carry, carry);
        r[i] = uaddCarry(r[i], b[i], carry2);
        carry += carry2;
    }
    return carry;
}

void Fq_rawAdd(out Element r, Element a, Element b)
{
    uint carry = mp_add_n(r, a, b);

    if (carry != 0 || mp_cmp(r, Fq_rawq) >= 0) {
        mp_sub_n(r, r, Fq_rawq);
    }
}

#define Fq_rawDbl(r, a) Fq_rawAdd(r, a, a)

void Fq_rawSub(out Element r, Element a, Element b)
{
    uint carry = mp_sub_n(r, a, b);

    if (carry != 0) {
        mp_add_n(r, r, Fq_rawq);
    }
}

shared Element Buckets[128];

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main() {
    Element bucket = ZeroElement;

    for (uint i = 0; i < nPoints; i++) {

        int bucketIdx = slicedScalars[chunkIdx * nPoints + i];
        bool negative = false;

        if (bucketIdx > 0) {
            bucketIdx = bucketIdx-1;

        } else if (bucketIdx < 0) {
            bucketIdx = -bucketIdx-1;
            negative = true;

        } else {
            continue;
        }

        if (bucketIdx != threadIdx) {
            continue;
        }

        if (negative) {
            Fq_rawSub(bucket, bucket, bases[i]);

        } else {
            Fq_rawAdd(bucket, bucket, bases[i]);
        }
     }

    Buckets[threadIdx] = bucket;

    barrier();

    if (threadIdx == 0) {
        Element t = Buckets[nBuckets - 1];
        Element tmp = t;

        for (int i = nBuckets - 2; i >= 0 ; i--) {
            Fq_rawAdd(tmp, tmp, Buckets[i]);
            Fq_rawAdd(t, t, tmp);
        }

        AssignElement(chunks[chunkIdx], t, N);
    }
}
