#version 430

layout (local_size_x = 128) in;

const int N = 8;

#define Element     uint[N]
#define LongElement uint[N+3]

const Element ElementZero = {0,0,0,0, 0,0,0,0};
const Element ElementOne  = {0xc58f0d9d,0xd35d438d,0xf5c70b3d,0x0a78eb28,0x7879462c,0x666ea36f,0x9a07df2f,0x0e0a77c1};
const Element fq_q        = {0xd87cfd47,0x3c208c16,0x6871ca8d,0x97816a91,0x8181585d,0xb85045b6,0xe131a029,0x30644e72};
const uint[2] fq_np       = {0xe4866389,0x87d20782};

const LongElement LongElementZero = {0,0,0,0, 0,0,0,0, 0,0,0};

#define BaseFieldElement     Element
#define BaseFieldElementZero ElementZero
#define BaseFieldElementOne  ElementOne
#define fa                   BaseFieldElementZero

struct CurvePoint
{
    BaseFieldElement x, y, zz, zzz;
};

struct CurvePointAffine
{
    BaseFieldElement x, y;
};

#define CurvePointZero CurvePoint( \
    BaseFieldElementOne, BaseFieldElementOne, \
    BaseFieldElementZero, BaseFieldElementZero);

layout(binding = 0) uniform bufParams {
    uint nPoints;
    uint scalarSize;
    uint bitsPerChunk;
    uint nChunks;
    int  nBuckets;
    uint workgroupSize;
};

layout(binding = 2) buffer readonly bufB { CurvePointAffine bases[]; };
layout(binding = 3) buffer bufR          { CurvePoint       chunks[]; };
layout(binding = 4) buffer bufTemp       { int              slicedScalars[]; };

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

uint mp_sub(out Element r, Element a, Element b)
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

uint mp_add(out Element r, Element a, Element b)
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

void mp_shl_64(inout LongElement r)
{
    for (int i = 0; i < N; i++) {
        r[i] = r[i+2];
    }
    r[N] = 0;
    r[N+1] = 0;
}

void mp_addmul_2(inout LongElement r, Element a, uint b0, uint b1)
{
    uint carry1 = 0;
    uint carry2 = 0;

    for (uint i = 0; i < N; i++) {
        uint hi, lo, carry;

        umulExtended(a[i], b0, hi, lo);

        lo   = uaddCarry(lo, carry1, carry);
        r[i] = uaddCarry(r[i], lo, carry1);

        carry1 += carry + hi;

        umulExtended(a[i], b1, hi, lo);

        lo     = uaddCarry(lo, carry2, carry);
        r[i+1] = uaddCarry(r[i+1], lo, carry2);

        carry2 += carry + hi;
    }

    r[N]   = uaddCarry(r[N],   carry1, carry1);
    r[N+1] = uaddCarry(r[N+1], carry1, carry1);
    r[N+1] = uaddCarry(r[N+1], carry2, carry2);
    r[N+2] = carry1 + carry2;
}

void add(out Element r, Element a, Element b)
{
    uint carry = mp_add(r, a, b);

    if (carry != 0 || mp_cmp(r, fq_q) >= 0) {
        mp_sub(r, r, fq_q);
    }
}

void sub(out Element r, Element a, Element b)
{
    uint carry = mp_sub(r, a, b);

    if (carry != 0) {
        mp_add(r, r, fq_q);
    }
}

void add_mmul_64(inout LongElement r, Element a, uint b0, uint b1)
{
    uint carry = r[N+2];

    for (uint i = 0; i < N; i++) {
        r[i+2] = uaddCarry(r[i+2], carry, carry);
    }
    r[N+2] = 0;

    mp_addmul_2(r, a, b0, b1);

    uint np0, np1;

    umulExtended(fq_np[0], r[0], np1, np0);

    np1 += (fq_np[0] * r[1]) + (fq_np[1] * r[0]);

    mp_addmul_2(r, fq_q, np0, np1);
}

void mul(out Element r, Element a, Element b)
{
    LongElement accum = LongElementZero;

    add_mmul_64(accum, b, a[0], a[1]);
    mp_shl_64(accum);

    add_mmul_64(accum, b, a[2], a[3]);
    mp_shl_64(accum);

    add_mmul_64(accum, b, a[4], a[5]);
    mp_shl_64(accum);

    add_mmul_64(accum, b, a[6], a[7]);

    for (int i = 0; i < N; i++) {
        r[i] = accum[i+2];
    }

    if (mp_cmp(r, fq_q) >= 0) {
        mp_sub(r, r, fq_q);
    }
}

void neg(out Element r, Element a)
{
    if (mp_cmp(a, ElementZero) != 0) {
        mp_sub(r, fq_q, a);

    } else {
        r = ElementZero;
    }
}

void copy(out CurvePoint r, CurvePointAffine a)
{
    if ((a.x == ElementZero) && (a.y == ElementZero)) {
        r.x = BaseFieldElementOne;
        r.y = BaseFieldElementOne;
        r.zz = BaseFieldElementZero;
        r.zzz = BaseFieldElementZero;
        return;
    }
    r.x = a.x;
    r.y = a.y;
    r.zz = BaseFieldElementOne;
    r.zzz = BaseFieldElementOne;
}

void add(out CurvePoint p3, CurvePoint p1, CurvePoint p2)
{
    if (p1.zz == ElementZero) {
        p3 = p2;
        return;
    }

    if (p2.zz == ElementZero) {
        p3 = p1;
        return;
    }

    BaseFieldElement tmp;
    BaseFieldElement T1;
    BaseFieldElement T2;
    BaseFieldElement T3;
    BaseFieldElement T4;
    BaseFieldElement P;
    BaseFieldElement R;

    mul(T1, p1.x, p2.zz);
    mul(T2, p2.x, p1.zz);
    mul(T3, p1.y, p2.zzz);
    mul(T4, p2.y, p1.zzz);
    sub(P, T2, T1);
    sub(R, T4, T3);

    if ((P == ElementZero) && (R == ElementZero)) {
        add(T1, p1.y, p1.y);
        mul(T2, T1, T1);
        mul(T3, T1, T2);
        mul(T4, p1.x, T2);
        mul(T1, p1.x, p1.x);
        add(tmp, T1, T1);
        add(T1, T1, tmp);
        mul(p3.x, T1, T1);
        sub(p3.x, p3.x, T4);
        sub(p3.x, p3.x, T4);
        mul(tmp, T3, p1.y);
        sub(p3.y, T4, p3.x);
        mul(p3.y, T1, p3.y);
        sub(p3.y, p3.y, tmp);
        mul(p3.zz, T2, p1.zz);
        mul(p3.zzz, T3, p1.zzz);
    } else {
        mul(T2, P, P);
        mul(T4, P, T2);
        mul(T1, T1, T2);
        mul(p3.x, R, R);
        sub(p3.x, p3.x, T4);
        sub(p3.x, p3.x, T1);
        sub(p3.x, p3.x, T1);
        mul(tmp, T3, T4);
        sub(p3.y, T1, p3.x);
        mul(p3.y, p3.y, R );
        sub(p3.y, p3.y, tmp);
        mul(p3.zz, p1.zz, p2.zz);
        mul(p3.zz, p3.zz, T2);
        mul(p3.zzz, p1.zzz, p2.zzz);
        mul(p3.zzz, p3.zzz, T4);
    }
}

void sub(out CurvePoint p3, CurvePoint p1, CurvePoint p2)
{
    CurvePoint tmp;

    neg(tmp.y, p2.y);
    tmp.x = p2.x;
    tmp.zz = p2.zz;
    tmp.zzz = p2.zzz;

    add(p3, p1, tmp);
}

shared CurvePoint Buckets[128];

#define chunkIdx  gl_WorkGroupID.x
#define threadIdx gl_LocalInvocationID.x

void main() {
    CurvePoint bucket = CurvePointZero;

    for (uint i = 0; i < nPoints; i++) {
        int bucketIdx = slicedScalars[chunkIdx * nPoints + i];
        bool negative = false;
        CurvePoint B;

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

        copy(B, bases[i]);

        if (negative) {
            sub(bucket, bucket, B);

        } else {
            add(bucket, bucket, B);
        }
     }

    Buckets[threadIdx] = bucket;

    barrier();

    if (threadIdx == 0) {
        CurvePoint t = Buckets[nBuckets - 1];
        CurvePoint tmp = t;

        for (int i = nBuckets - 2; i >= 0 ; i--) {
            add(tmp, tmp, Buckets[i]);
            add(t, t, tmp);
        }

        chunks[chunkIdx] = t;
    }
}
