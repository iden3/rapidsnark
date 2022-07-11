#include "fq_element.hpp"
#include <gmp.h>
#include <cstring>

static uint64_t     Fq_rawq[] = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029, 0};
static FqRawElement Fq_rawR2  = {0xf32cfc5b538afa89,0xb5e71911d44501fb,0x47ab1eff0a417ff6,0x06d89f71cab8351f};
static uint64_t     Fq_np     = {0x87d20782e4866389};


void Fq_rawAdd(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
{
    uint64_t carry = mpn_add_n(pRawResult, pRawA, pRawB, Fq_N64);

    if(carry || mpn_cmp(pRawResult, Fq_rawq, Fq_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fq_rawq, Fq_N64);
    }
}

void Fq_rawSub(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
{
    uint64_t carry = mpn_sub_n(pRawResult, pRawA, pRawB, Fq_N64);

    if(carry)
    {
        mpn_add_n(pRawResult, pRawResult, Fq_rawq, Fq_N64);
    }
}

void Fq_rawNeg(FqRawElement pRawResult, FqRawElement pRawA)
{
    const uint64_t zero[Fq_N64] = {0, 0, 0, 0};

    if (mpn_cmp(pRawA, zero, Fq_N64) != 0)
    {
        mpn_sub_n(pRawResult, Fq_rawq, pRawA, Fq_N64);
    }
    else
    {
        mpn_copyi(pRawResult, zero, Fq_N64);
    }
}

void Fq_rawCopy(FqRawElement pRawResult, FqRawElement pRawA)
{
    pRawResult[0] = pRawA[0];
    pRawResult[1] = pRawA[1];
    pRawResult[2] = pRawA[2];
    pRawResult[3] = pRawA[3];
}

int Fq_rawIsEq(FqRawElement pRawA, FqRawElement pRawB)
{
    return mpn_cmp(pRawA, pRawB, Fq_N64) == 0;
}

void Fq_rawMMul(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
{
    const mp_size_t  N = Fq_N64+1;
    const uint64_t  *mq = Fq_rawq;

    uint64_t  np0;

    uint64_t  product0[N] = {0};
    uint64_t  product1[N] = {0};
    uint64_t  product2[N] = {0};
    uint64_t  product3[N] = {0};

    product0[4] = mpn_mul_1(product0, pRawB, Fq_N64, pRawA[0]);

    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);

    product1[4] = mpn_addmul_1(product1, pRawB, Fq_N64, pRawA[1]);
    mpn_add(product1, product1, N, product0+1, N-1);

    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);

    product2[4] = mpn_addmul_1(product2, pRawB, Fq_N64, pRawA[2]);
    mpn_add(product2, product2, N, product1+1, N-1);

    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);

    product3[4] = mpn_addmul_1(product3, pRawB, Fq_N64, pRawA[3]);
    mpn_add(product3, product3, N, product2+1, N-1);

    np0 = Fq_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fq_N64);

    if (mpn_cmp(pRawResult, mq, Fq_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fq_N64);
    }
}

void Fq_rawMSquare(FqRawElement pRawResult, FqRawElement pRawA)
{
    Fq_rawMMul(pRawResult, pRawA, pRawA);
}

void Fq_rawMMul1(FqRawElement pRawResult, FqRawElement pRawA, uint64_t pRawB)
{
    const mp_size_t  N = Fq_N64+1;
    const uint64_t  *mq = Fq_rawq;

    uint64_t  np0;

    uint64_t  product0[N] = {0};
    uint64_t  product1[N] = {0};
    uint64_t  product2[N] = {0};
    uint64_t  product3[N] = {0};

    product0[4] = mpn_mul_1(product0, pRawA, Fq_N64, pRawB);

    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);

    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);

    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);

    np0 = Fq_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fq_N64);

    if (mpn_cmp(pRawResult, mq, Fq_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fq_N64);
    }
}

void Fq_rawToMontgomery(FqRawElement pRawResult, FqRawElement pRawA)
{
    Fq_rawMMul(pRawResult, pRawA, Fq_rawR2);
}

void Fq_rawFromMontgomery(FqRawElement pRawResult, FqRawElement pRawA)
{
    const mp_size_t  N = Fq_N64+1;
    const uint64_t  *mq = Fq_rawq;

    uint64_t  np0;

    uint64_t  product0[N];
    uint64_t  product1[N] = {0};
    uint64_t  product2[N] = {0};
    uint64_t  product3[N] = {0};

    mpn_copyi(product0, pRawA, Fq_N64); product0[4] = 0;

    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);

    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);

    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);

    np0 = Fq_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fq_N64);

    if (mpn_cmp(pRawResult, mq, Fq_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fq_N64);
    }
}

int Fq_rawIsZero(FqRawElement rawA)
{
    return mpn_zero_p(rawA, Fq_N64) ? 1 : 0;
}

void Fq_rawSwap(FqRawElement pRawResult, FqRawElement pRawA)
{
    FqRawElement temp;

    temp[0] = pRawResult[0];
    temp[1] = pRawResult[1];
    temp[2] = pRawResult[2];
    temp[3] = pRawResult[3];

    pRawResult[0] = pRawA[0];
    pRawResult[1] = pRawA[1];
    pRawResult[2] = pRawA[2];
    pRawResult[3] = pRawA[3];

    pRawA[0] = temp[0];
    pRawA[1] = temp[1];
    pRawA[2] = temp[2];
    pRawA[3] = temp[3];
}

void Fq_rawCopyS2L(FqRawElement pRawResult, int64_t val)
{
    pRawResult[0] = val;
    pRawResult[1] = 0;
    pRawResult[2] = 0;
    pRawResult[3] = 0;

    if (val < 0)
    {
        pRawResult[1] = -1;
        pRawResult[2] = -1;
        pRawResult[3] = -1;

        mpn_add_n(pRawResult, pRawResult, Fq_rawq, Fq_N64);
    }
}
