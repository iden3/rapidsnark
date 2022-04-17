#include "fq.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <cstring>


static mpz_t q;
static mpz_t zero;
static mpz_t one;
static mpz_t mask;
static size_t nBits;
static bool initialized = false;

#ifndef USE_ASM

static FqElement    Fq_q     = {0, 0x80000000, {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029}};
static uint64_t     Fq_rawq[]  =               {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029, 0};
static FqElement    Fq_R3    = {0, 0x80000000, {0xb1cd6dafda1530df,0x62f210e6a7283db6,0xef7f0b0c0ada0afb,0x20fd6e902d592544}};
static FqRawElement Fq_rawR3 =                 {0xb1cd6dafda1530df,0x62f210e6a7283db6,0xef7f0b0c0ada0afb,0x20fd6e902d592544};
static FqRawElement Fq_rawR2 =                 {0xf32cfc5b538afa89,0xb5e71911d44501fb,0x47ab1eff0a417ff6,0x06d89f71cab8351f};
static uint64_t     Fq_np    = {0x87d20782e4866389};

#endif

void Fq_toMpz(mpz_t r, PFqElement pE) {
    FqElement tmp;
    Fq_toNormal(&tmp, pE);
    if (!(tmp.type & Fq_LONG)) {
        mpz_set_si(r, tmp.shortVal);
        if (tmp.shortVal<0) {
            mpz_add(r, r, q);
        }
    } else {
        mpz_import(r, Fq_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
}

void Fq_fromMpz(PFqElement pE, mpz_t v) {
    if (mpz_fits_sint_p(v)) {
        pE->type = Fq_SHORT;
        pE->shortVal = mpz_get_si(v);
    } else {
        pE->type = Fq_LONG;
        for (int i=0; i<Fq_N64; i++) pE->longVal[i] = 0;
        mpz_export((void *)(pE->longVal), NULL, -1, 8, -1, 0, v);
    }
}


bool Fq_init() {
    if (initialized) return false;
    initialized = true;
    mpz_init(q);
    mpz_import(q, Fq_N64, -1, 8, -1, 0, (const void *)Fq_q.longVal);
    mpz_init_set_ui(zero, 0);
    mpz_init_set_ui(one, 1);
    nBits = mpz_sizeinbase (q, 2);
    mpz_init(mask);
    mpz_mul_2exp(mask, one, nBits);
    mpz_sub(mask, mask, one);
    return true;
}

void Fq_str2element(PFqElement pE, char const *s) {
    mpz_t mr;
    mpz_init_set_str(mr, s, 10);
    mpz_fdiv_r(mr, mr, q);
    Fq_fromMpz(pE, mr);
    mpz_clear(mr);
}

char *Fq_element2str(PFqElement pE) {
    FqElement tmp;
    mpz_t r;
    if (!(pE->type & Fq_LONG)) {
        if (pE->shortVal>=0) {
            char *r = new char[32];
            sprintf(r, "%d", pE->shortVal);
            return r;
        } else {
            mpz_init_set_si(r, pE->shortVal);
            mpz_add(r, r, q);
        }
    } else {
        Fq_toNormal(&tmp, pE);
        mpz_init(r);
        mpz_import(r, Fq_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
    char *res = mpz_get_str (0, 10, r);
    mpz_clear(r);
    return res;
}

void Fq_idiv(PFqElement r, PFqElement a, PFqElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fq_toMpz(ma, a);
    // char *s1 = mpz_get_str (0, 10, ma);
    // printf("s1 %s\n", s1);
    Fq_toMpz(mb, b);
    // char *s2 = mpz_get_str (0, 10, mb);
    // printf("s2 %s\n", s2);
    mpz_fdiv_q(mr, ma, mb);
    // char *sr = mpz_get_str (0, 10, mr);
    // printf("r %s\n", sr);
    Fq_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fq_mod(PFqElement r, PFqElement a, PFqElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fq_toMpz(ma, a);
    Fq_toMpz(mb, b);
    mpz_fdiv_r(mr, ma, mb);
    Fq_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fq_pow(PFqElement r, PFqElement a, PFqElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fq_toMpz(ma, a);
    Fq_toMpz(mb, b);
    mpz_powm(mr, ma, mb, q);
    Fq_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fq_inv(PFqElement r, PFqElement a) {
    mpz_t ma;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mr);

    Fq_toMpz(ma, a);
    mpz_invert(mr, ma, q);
    Fq_fromMpz(r, mr);
    mpz_clear(ma);
    mpz_clear(mr);
}

void Fq_div(PFqElement r, PFqElement a, PFqElement b) {
    FqElement tmp;
    Fq_inv(&tmp, b);
    Fq_mul(r, a, &tmp);
}

void Fq_fail() {
    assert(false);
}


RawFq::RawFq() {
    Fq_init();
    fromString(fZero, "0");
    fromString(fOne, "1");
    neg(fNegOne, fOne);
}

RawFq::~RawFq() {
}
extern "C"
void RawFq::fromString(Element &r, std::string s) {
    mpz_t mr;
    mpz_init_set_str(mr, s.c_str(), 10);
    mpz_fdiv_r(mr, mr, q);
    for (int i=0; i<Fq_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);
    Fq_rawToMontgomery(r.v,r.v);
    mpz_clear(mr);
}

void RawFq::fromUI(Element &r, unsigned long int v) {
    mpz_t mr;
    mpz_init(mr);
    mpz_set_ui(mr, v);
    for (int i=0; i<Fq_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);
    Fq_rawToMontgomery(r.v,r.v);
    mpz_clear(mr);
}



std::string RawFq::toString(Element &a, uint32_t radix) {
    Element tmp;
    mpz_t r;
    Fq_rawFromMontgomery(tmp.v, a.v);
    mpz_init(r);
    mpz_import(r, Fq_N64, -1, 8, -1, 0, (const void *)(tmp.v));
    char *res = mpz_get_str (0, radix, r);
    mpz_clear(r);
    std::string resS(res);
    free(res);
    return resS;
}

void RawFq::inv(Element &r, Element &a) {
    mpz_t mr;
    mpz_init(mr);
    mpz_import(mr, Fq_N64, -1, 8, -1, 0, (const void *)(a.v));
    mpz_invert(mr, mr, q);


    for (int i=0; i<Fq_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);

    Fq_rawMMul(r.v, r.v,Fq_rawR3);
    mpz_clear(mr);
}

void RawFq::div(Element &r, Element &a, Element &b) {
    Element tmp;
    inv(tmp, b);
    mul(r, a, tmp);
}

#define BIT_IS_SET(s, p) (s[p>>3] & (1 << (p & 0x7)))
void RawFq::exp(Element &r, Element &base, uint8_t* scalar, unsigned int scalarSize) {
    bool oneFound = false;
    Element copyBase;
    copy(copyBase, base);
    for (int i=scalarSize*8-1; i>=0; i--) {
        if (!oneFound) {
            if ( !BIT_IS_SET(scalar, i) ) continue;
            copy(r, copyBase);
            oneFound = true;
            continue;
        }
        square(r, r);
        if ( BIT_IS_SET(scalar, i) ) {
            mul(r, r, copyBase);
        }
    }
    if (!oneFound) {
        copy(r, fOne);
    }
}

void RawFq::toMpz(mpz_t r, Element &a) {
    Element tmp;
    Fq_rawFromMontgomery(tmp.v, a.v);
    mpz_import(r, Fq_N64, -1, 8, -1, 0, (const void *)tmp.v);
}

void RawFq::fromMpz(Element &r, mpz_t a) {
    for (int i=0; i<Fq_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, a);
    Fq_rawToMontgomery(r.v, r.v);
}


static bool init = Fq_init();

RawFq RawFq::field;

#ifndef USE_ASM

/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib Begin
******************************************************************************************/
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
    mpn_copyi(pRawResult, pRawA, Fq_N64);
}

void Fq_copy(PFqElement r, PFqElement a)
{
    r->shortVal = a->shortVal;
    r->type = a->type;
    std::memcpy(r->longVal, a->longVal, sizeof(FqRawElement));
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

    // FirstLoop 0
    product0[4] = mpn_mul_1(product0, pRawB, Fq_N64, pRawA[0]);

    // Second Loop 0
    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);

    // FirstLoop 1
    product1[4] = mpn_addmul_1(product1, pRawB, Fq_N64, pRawA[1]);
    mpn_add(product1, product1, N, product0+1, N-1);

    // Second Loop 1
    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);

    // FirstLoop 2
    product2[4] = mpn_addmul_1(product2, pRawB, Fq_N64, pRawA[2]);
    mpn_add(product2, product2, N, product1+1, N-1);

    // Second Loop 2
    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);

    // FirstLoop 3
    product3[4] = mpn_addmul_1(product3, pRawB, Fq_N64, pRawA[3]);
    mpn_add(product3, product3, N, product2+1, N-1);

    // Second Loop 3
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

    // FirstLoop 0
    product0[4] = mpn_mul_1(product0, pRawA, Fq_N64, pRawB);

    // Second Loop 0
    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);

    // Second Loop 1
    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);

    // Second Loop 2
    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);

    // Second Loop 3
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

    // FirstLoop 0
    mpn_copyi(product0, pRawA, Fq_N64); product0[4] = 0;

    // Second Loop 0
    np0 = Fq_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);

    // Second Loop 1
    np0 = Fq_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);

    // Second Loop 2
    np0 = Fq_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);

    // Second Loop 3
    np0 = Fq_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fq_N64);

    if (mpn_cmp(pRawResult, mq, Fq_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fq_N64);
    }
}

void Fq_toNormal(PFqElement r, PFqElement a)
{
    if (a->type == Fq_LONGMONTGOMERY)
    {
        r->type = Fq_LONG;
        Fq_rawFromMontgomery(r->longVal, a->longVal);
    }
    else
    {
        Fq_copy(r, a);
    }
}

int Fq_rawIsZero(FqRawElement pRawB)
{
    return mpn_zero_p(pRawB, Fq_N64);
}

void Fq_rawSwap(FqRawElement pRawResult, FqRawElement pRawA)
{
    FqRawElement tmp = {0};
    for (int i=0; i<Fq_N64; i++)
    {
        tmp[i] = pRawResult[i];
        pRawResult[i] = pRawA[i];
        pRawA[i] = tmp[i];
    }
}

void rawCopyS2L(PFqElement r, int64_t temp);
void mul_s1s2(PFqElement r, PFqElement a, PFqElement b);
void mul_l1nl2n(PFqElement r, PFqElement a, PFqElement b);
void mul_l1ml2n(PFqElement r,PFqElement a,PFqElement b);
void mul_l1nl2m(PFqElement r, PFqElement a, PFqElement b);
void mul_l1ml2m(PFqElement r,PFqElement a,PFqElement b);

void mul_l1ns2n(PFqElement r,PFqElement a,PFqElement b);
void mul_s1nl2n(PFqElement r,PFqElement a,PFqElement b);
void mul_l1ms2n(PFqElement r,PFqElement a,PFqElement b);
void mul_s1nl2m(PFqElement r,PFqElement a,PFqElement b);

void mul_l1ns2m(PFqElement r,PFqElement a,PFqElement b);
void mul_l1ms2m(PFqElement r,PFqElement a,PFqElement b);
void mul_s1ml2n(PFqElement r,PFqElement a,PFqElement b);
void mul_s1ml2m(PFqElement r,PFqElement a,PFqElement b);


void Fq_mul(PFqElement r, PFqElement a, PFqElement b)
{
    //mpz_import(mr3, Fr_N64, -1, 8, -1, 0, (const void *)Fr_rawR3);

    if (a->type & Fq_LONG) // if (mpz_tstbit (ma, 63)) // 2267 ; Check if is short first operand
    {
        // jc     mul_l1
        if (b->type & Fq_LONG) //if (mpz_tstbit (mb, 63)) // 2293 ; Check if is short second operand
        {
            // mul_l1l2
            if (a->type == Fq_LONGMONTGOMERY) // if (mpz_tstbit (ma, 62)) // 2511 ; check if montgomery first
            {
                // mul_l1ml2
                if (b->type == Fq_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2554 ; check if montgomery second
                {
                    mul_l1ml2m(r, a, b);
                }
                else
                {
                    mul_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fq_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2514 ; check if montgomery second
            {
                mul_l1nl2m(r, a, b);
            }
            else
            {
                mul_l1nl2n(r, a, b);
            }
        }
        //mul_l1s2:
        else if (a->type == Fq_LONGMONTGOMERY) //if (mpz_tstbit (ma, 62)) // 2298 ; check if montgomery first
        {
            // mul_l1ms2
            if (b->type == Fq_SHORT) //if (mpz_tstbit (mb, 62)) // 2358 ; check if montgomery second
            {

                mul_l1ms2n(r, a, b);
            }
            else
            {
                mul_l1ms2m(r, a, b);
            }

        }
        // mul_l1ns2
        else
        {
            if (b->type == Fq_SHORTMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2301 ; check if montgomery second
            {
                mul_l1ns2m(r, a, b);
            }
            else
            {
                mul_l1ns2n(r, a, b);
            }
        }
    }
    else if (b->type & Fq_LONG)//if (mpz_tstbit (mb, 63)) // 2269  ; Check if is short second operand
    {
        // mul_s1l2
        if (a->type == Fq_SHORTMONTGOMERY)//if (mpz_tstbit (ma, 62)) // 2406  ; check if montgomery first
        {
            // mul_s1ml2
            if (b->type == Fq_LONGMONTGOMERY)//if (mpz_tstbit (mb, 62)) // 2479  ; check if montgomery second
            {
                mul_s1ml2m(r, a, b);
            }
            else
            {
                mul_s1ml2n(r,a, b);
            }
        }
        // mul_s1nl2
        else if (b->type == Fq_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2409; check if montgomery second
        {
            mul_s1nl2m(r, a, b);
        }
        // mul_s1nl2n
        else
        {
            mul_s1nl2n(r, a, b);
        }
    }
    else
    {
         mul_s1s2(r, a, b);
    }
}

void mul_s1s2(PFqElement r, PFqElement a, PFqElement b)
{
    mpz_t rax;
    mpz_init(rax);

    int64_t temp = (int64_t)a->shortVal * (int64_t)b->shortVal;
    r->longVal[0] = temp;
    mpz_import(rax, 1, -1, 8, -1, 0, (const void *)r);
    // mul_manageOverflow
    if (!mpz_fits_sint_p(rax))
    {
        rawCopyS2L(r, temp);
    }
    else
    {
        r->type = Fq_LONG;
    }
    mpz_clear(rax);
}

void rawCopyS2L(PFqElement pResult, int64_t val)
{
    pResult->type = Fq_LONG;
    pResult->shortVal = 0;

    uint64_t *result = pResult->longVal;

    mpn_zero(result, Fq_N64);
    result[0] = val;

    if (val < 0)
    {
        mpn_com(result+1, result+1, Fq_N64-1);
        mpn_add_n(result, result, Fq_rawq, Fq_N64);
    }
}

void mul_l1nl2n(PFqElement r,PFqElement a,PFqElement b)
{
    FqElement tmp1;
    FqElement tmp2;

    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);

    tmp1.type = Fq_LONG;
    tmp2.type = Fq_LONG;
    tmp1.shortVal = 0;
    tmp2.shortVal = 0;
    for (int i=0; i<Fq_N64; i++)
    {
        tmp1.longVal[i] = r->longVal[i];
        tmp2.longVal[i] = Fq_R3.longVal[i];
    }    
    Fq_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
}

void mul_l1nl2m(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ml2m(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ml2n(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ns2n(PFqElement r,PFqElement a,PFqElement b)
{
    FqElement tmp1;
    FqElement tmp2;
    int32_t   tmp3;

    r->type = Fq_LONGMONTGOMERY;
    if (b->shortVal >= 0)
    {
        // tmp_5:
        Fq_rawMMul1(&r->longVal[0], &a->longVal[0], b->shortVal);
        // tmp_6:
        tmp1.type = Fq_LONG;
        tmp2.type = Fq_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fq_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fq_R3.longVal[i];
        }
        Fq_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
    else
    {
        tmp3 = b->shortVal * (-1);
        Fq_rawMMul1(&r->longVal[0], &a->longVal[0], tmp3);
        Fq_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_6:
        tmp1.type = Fq_LONG;
        tmp2.type = Fq_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fq_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fq_R3.longVal[i];
        }
        Fq_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
}

void mul_s1nl2n(PFqElement r,PFqElement a,PFqElement b)
{
    FqElement tmp1;
    FqElement tmp2;
    int32_t   tmp3;

    r->type = Fq_LONGMONTGOMERY;
    if (a->shortVal >= 0)
    {
        // tmp_9:
        Fq_rawMMul1(&r->longVal[0], &b->longVal[0], a->shortVal);
        // tmp_10:
        tmp1.type = Fq_LONG;
        tmp2.type = Fq_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fq_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fq_R3.longVal[i];
        }
        Fq_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
    else
    {
        tmp3 = a->shortVal * (-1);
        Fq_rawMMul1(&r->longVal[0], &b->longVal[0], tmp3);
        Fq_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_6:
        tmp1.type = Fq_LONG;
        tmp2.type = Fq_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fq_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fq_R3.longVal[i];
        }
        Fq_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
}

void mul_l1ms2n(PFqElement r,PFqElement a,PFqElement b)
{
    FqElement tmp1;
    FqElement tmp2;
    int32_t   tmp3;

    r->type = Fq_LONG;
    if (b->shortVal >= 0)
    {
        // tmp_7:
        Fq_rawMMul1(&r->longVal[0], &a->longVal[0], b->shortVal);
        // tmp_8:
    }
    else
    {
        tmp3 = b->shortVal * (-1);
        Fq_rawMMul1(&r->longVal[0], &a->longVal[0], tmp3);
        Fq_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_8:
    }
}

void mul_s1nl2m(PFqElement r,PFqElement a,PFqElement b)
{
    FqElement tmp1;
    FqElement tmp2;
    int32_t   tmp3;

    r->type = Fq_LONG;
    if (a->shortVal >= 0)
    {
        // tmp_11:
        Fq_rawMMul1(&r->longVal[0], &b->longVal[0], a->shortVal);
        // tmp_12:
    }
    else
    {
        tmp3 = a->shortVal * (-1);
        Fq_rawMMul1(&r->longVal[0], &b->longVal[0], tmp3);
        Fq_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_12:
    }
}

void mul_l1ns2m(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ms2m(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_s1ml2m(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_s1ml2n(PFqElement r,PFqElement a,PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib End
******************************************************************************************/

#endif
