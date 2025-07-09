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

struct F2FieldElement {
    Element a;
    Element b;
};

const F2FieldElement F2FieldElementZero = {ElementZero, ElementZero};
const F2FieldElement F2FieldElementOne  = {ElementOne,  ElementZero};

#define BaseFieldElement     F2FieldElement
#define BaseFieldElementZero F2FieldElementZero
#define BaseFieldElementOne  F2FieldElementOne
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

void square(out Element r, Element a)
{
    mul(r, a, a);
}

void neg(out Element r, Element a)
{
    if (mp_cmp(a, ElementZero) != 0) {
        mp_sub(r, fq_q, a);

    } else {
        r = ElementZero;
    }
}

void mul(out F2FieldElement r, F2FieldElement e1, F2FieldElement e2)
{
    Element aa;
    mul(aa, e1.a, e2.a);
    Element bb;
    mul(bb, e1.b, e2.b);

    Element bbr;
    neg(bbr, bb);

    Element sum1, sum2;
    add(sum1, e1.a, e1.b);
    add(sum2, e2.a, e2.b);

    add(r.a, aa, bbr);

    mul(r.b, sum1, sum2 );
    sub(r.b, r.b, aa);
    sub(r.b, r.b, bb);
}

void square(out F2FieldElement r, F2FieldElement e1)
{
    Element ab;
    Element tmp1, tmp2;

    mul(ab, e1.a, e1.b);

    add(tmp1, e1.a, e1.b);
    sub(tmp2, e1.a, e1.b);

    mul(r.a, tmp1, tmp2);
    add(r.b, ab, ab);
}

void neg(out F2FieldElement r, F2FieldElement a)
{
    neg(r.a, a.a);
    neg(r.b, a.b);
}

void sub(out F2FieldElement r, F2FieldElement a, F2FieldElement b)
{
    sub(r.a, a.a, b.a);
    sub(r.b, a.b, b.b);
}

void add(out F2FieldElement r, F2FieldElement a, F2FieldElement b)
{
    add(r.a, a.a, b.a);
    add(r.b, a.b, b.b);
}

bool isZero(F2FieldElement a)
{
    return (a.a == ElementZero) && (a.b == ElementZero);
}

bool isZero(CurvePoint p1)
{
    return isZero(p1.zz);
}

bool isZero(CurvePointAffine p1)
{
    return isZero(p1.x) && isZero(p1.y);
}

void copy(out CurvePoint r, CurvePointAffine a)
{
    if (isZero(a)) {
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

void dbl(out CurvePoint p3, CurvePoint p1)
{
    if (isZero(p1)) {
        p3 = p1;
        return;
    }

    BaseFieldElement tmp;

    BaseFieldElement U;
    add(U, p1.y, p1.y);

    BaseFieldElement V;
    square(V, U);

    BaseFieldElement W;
    mul(W, U, V);

    BaseFieldElement S;
    mul(S, p1.x, V);

    BaseFieldElement M;
    square(M, p1.x);
    add(tmp, M, M);
    add(M, M, tmp);

    square(p3.x, M);
    sub(p3.x, p3.x, S);
    sub(p3.x, p3.x, S);

    mul(tmp, W, p1.y);
    sub(p3.y, S, p3.x);
    mul(p3.y, M, p3.y);
    sub(p3.y, p3.y, tmp);
    mul(p3.zz, V, p1.zz);
    mul(p3.zzz, W, p1.zzz);
}

void dbl(out CurvePoint p3, CurvePointAffine p1)
{
    if (isZero(p1)) {
        copy(p3, p1);
        return;
    }

    BaseFieldElement tmp;

    BaseFieldElement U;
    add(U, p1.y, p1.y);
    square(p3.zz, U);
    mul(p3.zzz, U, p3.zz);

    BaseFieldElement S;
    mul(S, p1.x, p3.zz);

    BaseFieldElement M;
    square(M, p1.x);
    add(tmp, M, M);
    add(M, tmp, M);
    add(M, M, fa);

    square(p3.x, M);
    sub(p3.x, p3.x, S);
    sub(p3.x, p3.x, S);

    mul(tmp, p3.zzz, p1.y);
    sub(p3.y, S, p3.x);
    mul(p3.y, M, p3.y);
    sub(p3.y, p3.y, tmp);
}

void add(out CurvePoint p3, CurvePoint p1, CurvePoint p2)
{
    if (isZero(p1)) {
        p3 = p2;
        return;
    }

    if (isZero(p2)) {
        p3 = p1;
        return;
    }

    BaseFieldElement tmp;

    BaseFieldElement U1;
    mul(U1, p1.x, p2.zz);

    BaseFieldElement U2;
    mul(U2, p2.x, p1.zz);

    BaseFieldElement S1;
    mul(S1, p1.y, p2.zzz);

    BaseFieldElement S2;
    mul(S2, p2.y, p1.zzz);

    BaseFieldElement P;
    sub(P, U2, U1);

    BaseFieldElement R;
    sub(R, S2, S1);

    if (isZero(P) && isZero(R)) {
        dbl(p3, p1);
        return;
    }

    BaseFieldElement PP;
    square(PP, P);

    BaseFieldElement PPP;
    mul(PPP, P, PP);

    BaseFieldElement Q;
    mul(Q, U1, PP);

    square(p3.x, R);
    sub(p3.x, p3.x, PPP);
    sub(p3.x, p3.x, Q);
    sub(p3.x, p3.x, Q);

    mul(tmp, S1, PPP);
    sub(p3.y, Q, p3.x);
    mul(p3.y, p3.y, R );
    sub(p3.y, p3.y, tmp);

    mul(p3.zz, p1.zz, p2.zz);
    mul(p3.zz, p3.zz, PP);

    mul(p3.zzz, p1.zzz, p2.zzz);
    mul(p3.zzz, p3.zzz, PPP);
}

void add(out CurvePoint p3, CurvePoint p1, CurvePointAffine p2)
{
    if (isZero(p1)) {
        copy(p3, p2);
        return;
    }

    if (isZero(p2)) {
        p3 = p1;
        return;
    }

    BaseFieldElement tmp;
    BaseFieldElement U2;
    mul(U2, p2.x, p1.zz);

    BaseFieldElement S2;
    mul(S2, p2.y, p1.zzz);

    BaseFieldElement P;
    sub(P, U2, p1.x);

    BaseFieldElement R;
    sub(R, S2, p1.y);

    if (isZero(P) && isZero(R)) {
        dbl(p3, p2);
        return;
    }

    BaseFieldElement PP;
    square(PP, P);

    BaseFieldElement PPP;
    mul(PPP, P, PP);

    BaseFieldElement Q;
    mul(Q, p1.x, PP);

    square(p3.x, R);
    sub(p3.x, p3.x, PPP);
    sub(p3.x, p3.x, Q);
    sub(p3.x, p3.x, Q);

    mul(tmp, p1.y, PPP);
    sub(p3.y, Q, p3.x);
    mul(p3.y, p3.y, R );
    sub(p3.y, p3.y, tmp);
    mul(p3.zz, p1.zz, PP);
    mul(p3.zzz, p1.zzz, PPP);
}

void neg(out CurvePointAffine r, CurvePointAffine a)
{
    r.x = a.x;
    neg(r.y, a.y);
}

void sub(out CurvePoint p3, CurvePoint p1, CurvePointAffine p2)
{
    CurvePointAffine tmp;

    neg(tmp, p2);
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
            sub(bucket, bucket, bases[i]);

        } else {
            add(bucket, bucket, bases[i]);
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
