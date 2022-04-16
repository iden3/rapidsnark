#include "fr.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include <string>
#include <cstring>
#include <iostream>


static mpz_t q;
static mpz_t zero;
static mpz_t one;
static mpz_t mask;
static size_t nBits;
static bool initialized = false;

#ifndef USE_ASM

static FrElement    Fr_q     = {0, 0x80000000, {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
static FrRawElement Fr_rawq  =                 {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
static FrElement    Fr_R3    = {0, 0x80000000, {0x5e94d8e1b4bf0040,0x2a489cbe1cfbb6b8,0x893cc664a19fcfed,0x0cf8594b7fcc657c}};
static FrRawElement Fr_rawR3 =                 {0x5e94d8e1b4bf0040,0x2a489cbe1cfbb6b8,0x893cc664a19fcfed,0x0cf8594b7fcc657c};
static FrRawElement Fr_rawR2 =                 {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5};
static uint64_t     Fr_np    = {0xc2e1f593efffffff};
static FrRawElement half     = {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
static uint64_t     lboMask  =  0x3fffffffffffffff;


#endif

void Fr_toMpz(mpz_t r, PFrElement pE) {
    FrElement tmp;
    Fr_toNormal(&tmp, pE);
    if (!(tmp.type & Fr_LONG)) {
        mpz_set_si(r, tmp.shortVal);
        if (tmp.shortVal<0) {
            mpz_add(r, r, q);
        }
    } else {
        mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
}

void Fr_fromMpz(PFrElement pE, mpz_t v) {
    if (mpz_fits_sint_p(v)) {
        pE->type = Fr_SHORT;
        pE->shortVal = mpz_get_si(v);
    } else {
        pE->type = Fr_LONG;
        for (int i=0; i<Fr_N64; i++) pE->longVal[i] = 0;
        mpz_export((void *)(pE->longVal), NULL, -1, 8, -1, 0, v);
    }
}


bool Fr_init() {
    if (initialized) return false;
    initialized = true;
    mpz_init(q);
    mpz_import(q, Fr_N64, -1, 8, -1, 0, (const void *)Fr_q.longVal);
    mpz_init_set_ui(zero, 0);
    mpz_init_set_ui(one, 1);
    nBits = mpz_sizeinbase (q, 2);
    mpz_init(mask);
    mpz_mul_2exp(mask, one, nBits);
    mpz_sub(mask, mask, one);
    return true;
}

void Fr_str2element(PFrElement pE, char const *s) {
    mpz_t mr;
    mpz_init_set_str(mr, s, 10);
    mpz_fdiv_r(mr, mr, q);
    Fr_fromMpz(pE, mr);
    mpz_clear(mr);
}

char *Fr_element2str(PFrElement pE) {
    FrElement tmp;
    mpz_t r;
    if (!(pE->type & Fr_LONG)) {
        if (pE->shortVal>=0) {
            char *r = new char[32];
            sprintf(r, "%d", pE->shortVal);
            return r;
        } else {
            mpz_init_set_si(r, pE->shortVal);
            mpz_add(r, r, q);
        }
    } else {
        Fr_toNormal(&tmp, pE);
        mpz_init(r);
        mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
    char *res = mpz_get_str (0, 10, r);
    mpz_clear(r);
    return res;
}

void Fr_idiv(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    // char *s1 = mpz_get_str (0, 10, ma);
    // printf("s1 %s\n", s1);
    Fr_toMpz(mb, b);
    // char *s2 = mpz_get_str (0, 10, mb);
    // printf("s2 %s\n", s2);
    mpz_fdiv_q(mr, ma, mb);
    // char *sr = mpz_get_str (0, 10, mr);
    // printf("r %s\n", sr);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_mod(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    Fr_toMpz(mb, b);
    mpz_fdiv_r(mr, ma, mb);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_pow(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    Fr_toMpz(mb, b);
    mpz_powm(mr, ma, mb, q);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_inv(PFrElement r, PFrElement a) {
    mpz_t ma;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    mpz_invert(mr, ma, q);
    Fr_fromMpz(r, mr);
    mpz_clear(ma);
    mpz_clear(mr);
}

void Fr_div(PFrElement r, PFrElement a, PFrElement b) {
    FrElement tmp;
    Fr_inv(&tmp, b);
    Fr_mul(r, a, &tmp);
}

void Fr_fail() {
    assert(false);
}


RawFr::RawFr() {
    Fr_init();
    fromString(fZero, "0");
    fromString(fOne, "1");
    neg(fNegOne, fOne);
}

RawFr::~RawFr() {
}

void RawFr::fromString(Element &r, std::string s) {
    mpz_t mr;
    mpz_init_set_str(mr, s.c_str(), 10);
    mpz_fdiv_r(mr, mr, q);
    for (int i=0; i<Fr_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);
    Fr_rawToMontgomery(r.v,r.v);
    mpz_clear(mr);
}

void RawFr::fromUI(Element &r, unsigned long int v) {
    mpz_t mr;
    mpz_init(mr);
    mpz_set_ui(mr, v);
    for (int i=0; i<Fr_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);
    Fr_rawToMontgomery(r.v,r.v);
    mpz_clear(mr);
}



std::string RawFr::toString(Element &a, uint32_t radix) {
    Element tmp;
    mpz_t r;
    Fr_rawFromMontgomery(tmp.v, a.v);
    mpz_init(r);
    mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)(tmp.v));
    char *res = mpz_get_str (0, radix, r);
    mpz_clear(r);
    std::string resS(res);
    free(res);
    return resS;
}

void RawFr::inv(Element &r, Element &a) {
    mpz_t mr;
    mpz_init(mr);
    mpz_import(mr, Fr_N64, -1, 8, -1, 0, (const void *)(a.v));
    mpz_invert(mr, mr, q);


    for (int i=0; i<Fr_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, mr);

    Fr_rawMMul(r.v, r.v,Fr_rawR3);
    mpz_clear(mr);
}

void RawFr::div(Element &r, Element &a, Element &b) {
    Element tmp;
    inv(tmp, b);
    mul(r, a, tmp);
}

#define BIT_IS_SET(s, p) (s[p>>3] & (1 << (p & 0x7)))
void RawFr::exp(Element &r, Element &base, uint8_t* scalar, unsigned int scalarSize) {
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

void RawFr::toMpz(mpz_t r, Element &a) {
    Element tmp;
    Fr_rawFromMontgomery(tmp.v, a.v);
    mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)tmp.v);
}

void RawFr::fromMpz(Element &r, mpz_t a) {
    for (int i=0; i<Fr_N64; i++) r.v[i] = 0;
    mpz_export((void *)(r.v), NULL, -1, 8, -1, 0, a);
    Fr_rawToMontgomery(r.v, r.v);
}


static bool init = Fr_init();

RawFr RawFr::field;

#ifndef USE_ASM

/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib Begin
******************************************************************************************/

static inline void
Fr_to_mpz(mpz_ptr dst, uint64_t src)
{
     mpz_import(dst, 1, -1, sizeof(src), -1, 0, &src);
}

static inline void
Fr_to_mpz(mpz_ptr dst, FrRawElement src)
{
     mpz_import(dst, Fr_N64, -1, sizeof(*src), -1, 0, src);
}

static inline void
Fr_to_rawElement(FrRawElement dst, mpz_ptr src)
{
    assert(mpz_size(src) <= Fr_N64);

    std::memset(dst, 0, sizeof(FrRawElement));
    mpz_export(dst, NULL, -1, 8, -1, 0, src);
}

void debug_val(uint64_t val)
{
    std::cout << std::hex << "{ " << val << " };" << std::endl;
}

void debug_val(FrRawElement val)
{
    std::cout << std::hex << "{ " << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << " };" << std::endl;
}

void debug_val(mpz_t val)
{
     std::cout << std::hex << "{ ";

    int i = 0;
    for(; i < val->_mp_size-1; i++) {
         std::cout <<  val->_mp_d[i] << ", ";
    }

    std::cout <<  val->_mp_d[i];

    std::cout << " };" << std::endl;
}

template <typename T>
void debug(T val, const char *name = 0, const char *msg = 0)
{
    if (msg) {
        std::cout << msg << std::endl;
    }

    if (name) {
        std::cout << name << " = ";
    }

    debug_val(val);
}

void get_carry(mpz_ptr val, mpz_ptr carry)
{
    if (mpz_size(val) <= 4)
    {
        mpz_set_ui(carry, 0);
    }
    else
    {
        mpz_set_ui(carry, 1);
        mpz_mul_2exp(carry, carry, 64);
    }
}

void Fr_rawAdd(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t carry;

    carry = mpn_add_n(&mr[0], &ma[0], &mb[0], 4);
    if(carry || mpn_cmp(mr, mq, 4) >= 0)
    {
        mpn_sub_n(&mr[0], &mr[0], &mq[0], 4);
    }
    std::memcpy(pRawResult, mr, sizeof(FrRawElement));
}

void Fr_rawSub(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t carry;

    carry = mpn_sub_n(&mr[0], &ma[0], &mb[0], 4);
    if(carry)
    {
        mpn_add_n(&mr[0], &mr[0], &mq[0], 4);
    }

    std::memcpy(pRawResult, mr, sizeof(FrRawElement));
}

void Fr_rawNeg(FrRawElement pRawResult, FrRawElement pRawA)
{
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t mz[Fr_N64] = {0, 0, 0, 0};

    if (mpn_cmp(&ma[0], &mz[0], 4) != 0)
    {
        mpn_sub_n(&mr[0], &mq[0], &ma[0], 4);
    }
    else
    {
        std::memcpy(mr, mz, sizeof(FrRawElement));
    }

    std::memcpy(pRawResult, mr, sizeof(FrRawElement));
}

void Fr_rawCopy(FrRawElement pRawResult, FrRawElement pRawA)
{
    std::memcpy(pRawResult, pRawA, sizeof(FrRawElement));
}

void Fr_copy(PFrElement r, PFrElement a)
{
    r->shortVal = a->shortVal;
    r->type = a->type;
    std::memcpy(r->longVal, a->longVal, sizeof(FrRawElement));
}

int Fr_rawIsEq(FrRawElement pRawA, FrRawElement pRawB)
{
    for (int i=0; i<Fr_N64; i++)
    {
        if (pRawA[i] != pRawB[i])
            return 0;
    }
    return 1;
}

void Fr_rawMMul(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    uint64_t np0;
    mpz_t a, b, mq, product, np0q, result, md, fcarry;

    mpz_inits(a, b, mq, product, np0q, result, md, fcarry, NULL);

    mpz_init_set_ui(md, 1);
    mpz_mul_2exp(md, md, 256);

    Fr_to_mpz(a, pRawA);
    Fr_to_mpz(b, pRawB);
    Fr_to_mpz(mq, Fr_rawq);

    // FirstLoop 0
    mpz_mul_ui(product, b, pRawA[0]);

    // Second Loop 0
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // FirstLoop 1
    mpz_mul_ui(product, b, pRawA[1]);
    mpz_add(product, result, product);
    mpz_add(product, product, fcarry);

    // Second Loop 1
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // FirstLoop 2
    mpz_mul_ui(product, b, pRawA[2]);
    mpz_add(product, result, product);
    mpz_add(product, product, fcarry);

    // Second Loop 2
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // FirstLoop 3
    mpz_mul_ui(product, b, pRawA[3]);
    mpz_add(product, result, product);
    mpz_add(product, product, fcarry);

    // Second Loop 3
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    mpz_mod(result, result, md);

    if (mpz_cmp(result, mq) >= 0)
    {
        mpz_sub(result, result, mq);
    }

    Fr_to_rawElement(pRawResult, result);

    mpz_clears(a, b, mq, product, np0q, result, md, fcarry, NULL);
}

void Fr_rawMSquare(FrRawElement pRawResult, FrRawElement pRawA)
{
    Fr_rawMMul(pRawResult, pRawA, pRawA);
}

void Fr_rawMMul1(FrRawElement pRawResult, FrRawElement pRawA, uint64_t pRawB)
{
    uint64_t np0;
    mpz_t a, mq, product, np0q, result, md, fcarry;

    mpz_inits(a, mq, product, np0q, result, md, fcarry, NULL);

    mpz_init_set_ui(md, 1);
    mpz_mul_2exp(md, md, 256);

    Fr_to_mpz(a, pRawA);
    Fr_to_mpz(mq, Fr_rawq);

    // FirstLoop 0
    mpz_mul_ui(product, a, pRawB);

    // Second Loop 0
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 1
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 2
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 3
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    mpz_mod(result, result, md);

    if (mpz_cmp(result, mq) >= 0)
    {
        mpz_sub(result, result, mq);
    }

    Fr_to_rawElement(pRawResult, result);

    mpz_clears(a, mq, product, np0q, result, md, fcarry, NULL);
}

void Fr_rawToMontgomery(FrRawElement pRawResult, FrRawElement pRawA)
{
    Fr_rawMMul(pRawResult, pRawA, Fr_rawR2);
}

void Fr_rawFromMontgomery(FrRawElement pRawResult, FrRawElement pRawA)
{
    uint64_t np0;
    mpz_t a, mq, product, np0q, result, md, fcarry;

    mpz_inits(a, mq, product, np0q, result, md, fcarry, NULL);

    mpz_init_set_ui(md, 1);
    mpz_mul_2exp(md, md, 256);

    Fr_to_mpz(a, pRawA);
    Fr_to_mpz(mq, Fr_rawq);

    // FirstLoop 0
    mpz_set(product, a);

    // Second Loop 0
    np0 = Fr_np * mpz_getlimbn(product, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, product);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 1
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 2
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    get_carry(result, fcarry);
    mpz_mod(result, result, md);

    // Second Loop 3
    np0 = Fr_np * mpz_getlimbn(result, 0);
    mpz_mul_ui(np0q, mq, np0);
    mpz_add(result, np0q, result);
    mpz_add(result, result, fcarry);
    mpz_tdiv_q_2exp(result, result, 64);
    mpz_mod(result, result, md);

    if (mpz_cmp(result, mq) >= 0)
    {
        mpz_sub(result, result, mq);
    }

    Fr_to_rawElement(pRawResult, result);

    mpz_clears(a, mq, product, np0q, result, md, fcarry, NULL);
}

void Fr_toNormal(PFrElement r, PFrElement a)
{
    if (a->type == Fr_LONGMONTGOMERY)
    {
        r->type = Fr_LONG;
        Fr_rawFromMontgomery(r->longVal, a->longVal);
    }
    else
    {
        Fr_copy(r, a);
    }
}

int Fr_rawIsZero(FrRawElement pRawB)
{
    for (int i=0; i<Fr_N64; i++)
    {
        if (pRawB[i] != 0)
        {
            return 0;
        }

    }
    return 1;
}

void Fr_rawSwap(FrRawElement pRawResult, FrRawElement pRawA)
{
    FrRawElement tmp = {0};
    for (int i=0; i<Fr_N64; i++)
    {
        tmp[i] = pRawResult[i];
        pRawResult[i] = pRawA[i];
        pRawA[i] = tmp[i];
    }
}

void rawCopyS2L(PFrElement r, int64_t temp);
void mul_s1s2(PFrElement r, PFrElement a, PFrElement b);
void mul_l1nl2n(PFrElement r, PFrElement a, PFrElement b);
void mul_l1ml2n(PFrElement r,PFrElement a,PFrElement b);
void mul_l1nl2m(PFrElement r, PFrElement a, PFrElement b);
void mul_l1ml2m(PFrElement r,PFrElement a,PFrElement b);

void mul_l1ns2n(PFrElement r,PFrElement a,PFrElement b);
void mul_s1nl2n(PFrElement r,PFrElement a,PFrElement b);
void mul_l1ms2n(PFrElement r,PFrElement a,PFrElement b);
void mul_s1nl2m(PFrElement r,PFrElement a,PFrElement b);

void mul_l1ns2m(PFrElement r,PFrElement a,PFrElement b);
void mul_l1ms2m(PFrElement r,PFrElement a,PFrElement b);
void mul_s1ml2n(PFrElement r,PFrElement a,PFrElement b);
void mul_s1ml2m(PFrElement r,PFrElement a,PFrElement b);


void Fr_mul(PFrElement r, PFrElement a, PFrElement b)
{
    //mpz_import(mr3, Fr_N64, -1, 8, -1, 0, (const void *)Fr_rawR3);

    if (a->type & Fr_LONG) // if (mpz_tstbit (ma, 63)) // 2267 ; Check if is short first operand
    {
        // jc     mul_l1
        if (b->type & Fr_LONG) //if (mpz_tstbit (mb, 63)) // 2293 ; Check if is short second operand
        {
            // mul_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // if (mpz_tstbit (ma, 62)) // 2511 ; check if montgomery first
            {
                // mul_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2554 ; check if montgomery second
                {
                    mul_l1ml2m(r, a, b);
                }
                else
                {
                    mul_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2514 ; check if montgomery second
            {
                mul_l1nl2m(r, a, b);
            }
            else
            {
                mul_l1nl2n(r, a, b);
            }
        }
        //mul_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) //if (mpz_tstbit (ma, 62)) // 2298 ; check if montgomery first
        {
            // mul_l1ms2
            if (b->type == Fr_SHORT) //if (mpz_tstbit (mb, 62)) // 2358 ; check if montgomery second
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
            if (b->type == Fr_SHORTMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2301 ; check if montgomery second
            {
                mul_l1ns2m(r, a, b);
            }
            else
            {
                mul_l1ns2n(r, a, b);
            }
        }
    }
    else if (b->type & Fr_LONG)//if (mpz_tstbit (mb, 63)) // 2269  ; Check if is short second operand
    {
        // mul_s1l2
        if (a->type == Fr_SHORTMONTGOMERY)//if (mpz_tstbit (ma, 62)) // 2406  ; check if montgomery first
        {
            // mul_s1ml2
            if (b->type == Fr_LONGMONTGOMERY)//if (mpz_tstbit (mb, 62)) // 2479  ; check if montgomery second
            {
                mul_s1ml2m(r, a, b);
            }
            else
            {
                mul_s1ml2n(r,a, b);
            }
        }
        // mul_s1nl2
        else if (b->type == Fr_LONGMONTGOMERY) //if (mpz_tstbit (mb, 62)) // 2409; check if montgomery second
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

void mul_s1s2(PFrElement r, PFrElement a, PFrElement b)
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
        r->type = Fr_LONG;
    }
    mpz_clear(rax);
}

//void rawCopyS2L(PFrElement pResult, int64_t val)
//{
//    mpz_t result, mq;

//    mpz_inits(result, mq);

//    mpz_set_si(result, val);

//    if (val < 0)
//    {
//        Fr_to_mpz(mq, Fr_rawq);

//        mpz_add(result, result, mq);
//    }

//    pResult->type = Fr_LONG;
//    pResult->shortVal = 0;
//    Fr_to_rawElement(pResult->longVal, result);

//    mpz_clears(result, mq);
//}

void rawCopyS2L(PFrElement pResult, int64_t val)
{
    pResult->type = Fr_LONG;
    pResult->shortVal = 0;

    uint64_t *result = pResult->longVal;

    mpn_zero(result, Fr_N64);
    result[0] = val;

    if (val < 0)
    {
        mpn_com(result+1, result+1, Fr_N64-1);
        mpn_add_n(result, result, Fr_rawq, Fr_N64);
    }
}

void mul_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;

    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);

    tmp1.type = Fr_LONG;
    tmp2.type = Fr_LONG;
    tmp1.shortVal = 0;
    tmp2.shortVal = 0;
    for (int i=0; i<Fr_N64; i++)
    {
        tmp1.longVal[i] = r->longVal[i];
        tmp2.longVal[i] = Fr_R3.longVal[i];
    }

    Fr_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
}

void mul_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ns2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;
    int32_t   tmp3;

    r->type = Fr_LONGMONTGOMERY;
    if (b->shortVal >= 0)
    {
        // tmp_5:
        Fr_rawMMul1(&r->longVal[0], &a->longVal[0], b->shortVal);
        // tmp_6:
        tmp1.type = Fr_LONG;
        tmp2.type = Fr_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fr_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fr_R3.longVal[i];
        }
        Fr_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
    else
    {
        tmp3 = b->shortVal * (-1);
        Fr_rawMMul1(&r->longVal[0], &a->longVal[0], tmp3);
        Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_6:
        tmp1.type = Fr_LONG;
        tmp2.type = Fr_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fr_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fr_R3.longVal[i];
        }
        Fr_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
}

void mul_s1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;
    int32_t   tmp3;

    r->type = Fr_LONGMONTGOMERY;
    if (a->shortVal >= 0)
    {
        // tmp_9:
        Fr_rawMMul1(&r->longVal[0], &b->longVal[0], a->shortVal);
        // tmp_10:
        tmp1.type = Fr_LONG;
        tmp2.type = Fr_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fr_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fr_R3.longVal[i];
        }
        Fr_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
    else
    {
        tmp3 = a->shortVal * (-1);
        Fr_rawMMul1(&r->longVal[0], &b->longVal[0], tmp3);
        Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_6:
        tmp1.type = Fr_LONG;
        tmp2.type = Fr_LONG;
        tmp1.shortVal = 0;
        tmp2.shortVal = 0;
        for (int i=0; i<Fr_N64; i++)
        {
            tmp1.longVal[i] = r->longVal[i];
            tmp2.longVal[i] = Fr_R3.longVal[i];
        }
        Fr_rawMMul(&r->longVal[0], &tmp1.longVal[0], &tmp2.longVal[0]);
    }
}

void mul_l1ms2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;
    int32_t   tmp3;

    r->type = Fr_LONG;
    if (b->shortVal >= 0)
    {
        // tmp_7:
        Fr_rawMMul1(&r->longVal[0], &a->longVal[0], b->shortVal);
        // tmp_8:
    }
    else
    {
        tmp3 = b->shortVal * (-1);
        Fr_rawMMul1(&r->longVal[0], &a->longVal[0], tmp3);
        Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_8:
    }
}

void mul_s1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;
    int32_t   tmp3;

    r->type = Fr_LONG;
    if (a->shortVal >= 0)
    {
        // tmp_11:
        Fr_rawMMul1(&r->longVal[0], &b->longVal[0], a->shortVal);
        // tmp_12:
    }
    else
    {
        tmp3 = a->shortVal * (-1);
        Fr_rawMMul1(&r->longVal[0], &b->longVal[0], tmp3);
        Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
        // tmp_12:
    }
}

void mul_l1ns2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_l1ms2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_s1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void mul_s1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

// Implemented, not checked
void Fr_toLongNormal(PFrElement r, PFrElement a)
{
    if (a->type != Fr_LONG)
    {
        // toLongNormal_fromShort
        rawCopyS2L(r, a->shortVal);
        r->type = Fr_LONG;
    }
    else if (a->type == Fr_LONGMONTGOMERY)
    {
        // toLongNormal_fromMontgomery:
        r->type = Fr_LONG;
        Fr_rawFromMontgomery(r->longVal, a->longVal);
    }
    else
    {
        Fr_copy(r, a);
    }
}

// Implemented, not checked
void Fr_copyn(PFrElement r, PFrElement a, int n)
{
    r->shortVal = a->shortVal;
    r->type = a->type;
    std::memset(r, 0, sizeof(FrRawElement));
    std::memcpy(r->longVal, a->longVal, n);
}

// Implemented, Not checked
//  Substracts a long element and a short element form 0
void rawNegLS(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], 0, 0, 0};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t carry = 0;
    mp_limb_t dl = 0, dh = 0;

    dl = mpn_sub_n(&mr[0], &mq[0], &mb[0], 4);
    //dl = carry;
    dh = mpn_sub_n(&mr[0], &mr[0], &ma[0], 4);
    //dh = carry;
    std::cout << "dl " << dl << "\n";
    std::cout << "dh " << dh << "\n";

    //mpn_ior_n(&carry,&dh,&dl,1);
    if(dl || dh)
    {
        std::cout << "carry != 0 " << "\n";
        mpn_add_n(&mr[0], &mr[0], &mq[0], 4);
    }
    std::memcpy(pRawResult, mr, sizeof(FrRawElement));
}

// Implemented, Not checked 1
void sub_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    mpz_t rax;
    mpz_init(rax);

    int64_t temp = (int64_t)a->shortVal - (int64_t)b->shortVal;
    r->shortVal = (int32_t)temp;
    mpz_import(rax, 1, -1, 8, -1, 0, (const void *)r);
    // mul_manageOverflow
    if (!mpz_fits_uint_p(rax))
    {
        rawCopyS2L(r, temp);
        //std::cout << "rawCopyS2L" << "\n";
    }
    else
    {
        //r->type = Fr_LONG;
        //std::cout << "Not rawCopyS2L" << "\n";
    }
    mpz_clear(rax);
}
// Implemented, Not checked 2
void sub_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 3
void sub_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, a);
    Fr_rawSub(&r->longVal[0], &r->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 4
void sub_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 5
void sub_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, b);
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &r->longVal[0]);
}

// Implemented, Not checked 6
void sub_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrRawElement tmp1 = {0,0,0,0};

    r->type = Fr_LONG;
    if (a->shortVal < 0)
    {
        tmp1[0] = a->shortVal * (-1);
        Fr_rawSub(r->longVal, tmp1, b->longVal);
        std::cout << "a->shortVal < 0" << "\n" ;
    }
    else
    {
        std::cout << "a->shortVal >= 0" << "\n" ;
        tmp1[0] = a->shortVal;
        rawNegLS(r->longVal, tmp1, b->longVal);
    }
}
// Implemented, Not checked 7
void sub_l1ms2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, b);
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &r->longVal[0]);
}

// Implemented, Not checked 8
void sub_s1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, a);
    Fr_rawSub(&r->longVal[0], &r->longVal[0], &b->longVal[0]);
}

// Implemented, Not checked 9
void sub_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    FrRawElement tmp1 = {0,0,0,0};

    r->type = Fr_LONG;
    if (b->shortVal < 0)
    {
        tmp1[0] = b->shortVal * (-1);
        Fr_rawAdd(&r->longVal[0], &a->longVal[0], &tmp1[0]);
        std::cout << "b->shortVal >= 0" << "\n" ;
    }
    else
    {
        tmp1[0] = b->shortVal;
        Fr_rawSub(&r->longVal[0], &a->longVal[0], &tmp1[0]);
        std::cout << "b->shortVal < 0" << "\n" ;
    }
}

// Implemented, Not checked 10
void sub_l1ms2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 11
void sub_s1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawSub(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

// Implemented, Not checked
void Fr_sub(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // sub_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // sub_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // sub_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    sub_l1ml2m(r, a, b);
                }
                else
                {
                    sub_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                sub_l1nl2m(r, a, b);
            }
            else
            {
                sub_l1nl2n(r, a, b);
            }
        }
        //sub_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // sub_l1ms2
            if (b->type == Fr_SHORT) // check if montgomery second
            {
                sub_l1ms2n(r, a, b);
            }
            else
            {
                sub_l1ms2m(r, a, b);
            }

        }
        // sub_l1ns2
        else
        {
            sub_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // sub_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // sub_s1l2m
            if (a->type == Fr_SHORTMONTGOMERY)// check if montgomery first
            {
               // sub_s1ml2m
               sub_s1ml2m(r,a,b);
            }
            else
            {
               // sub_s1nl2m
               sub_s1nl2m(r,a,b);
            }
        }
        else
        {
            // sub_s1l2n
            sub_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         sub_s1s2(r, a, b);
    }
}

// Implemented, Not checked
void Fr_toMontgomery(PFrElement r, PFrElement a)
{
    if (a->type == Fr_LONGMONTGOMERY) // ; check if montgomery
    {
        // toMontgomery_doNothing
        Fr_copy(r,a);
        return;
    }

    if (a->type == Fr_LONG)
    {
        // toMontgomeryLong
        r->type = Fr_LONGMONTGOMERY;
        Fr_rawMMul(&r->longVal[0], &a->longVal[0], &Fr_rawR2[0]);
        return;
    }

    // toMontgomeryShort
    if (a->shortVal < 0)
    {
       // negMontgomeryShort
       r->type = Fr_SHORTMONTGOMERY;
       int32_t tmp;
       tmp = a->shortVal * (-1);
       // ; Do the multiplication positive and then negate the result.
       Fr_rawMMul1(&r->longVal[0], &Fr_rawR2[0], tmp);
       Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
       return;
    }

    // posMontgomeryShort
    r->type = Fr_SHORTMONTGOMERY;
    Fr_rawMMul1(&r->longVal[0], &Fr_rawR2[0], a->shortVal);
    return;
}

//// Implemented, Not checked 1
//void add_s1s2(PFrElement r, PFrElement a, PFrElement b)
//{
//    mpz_t rax;
//    mpz_init(rax);

//    int64_t temp = (int64_t)a->shortVal + (int64_t)b->shortVal;
//    r->longVal[0] = temp;
//    mpz_import(rax, 1, -1, 8, -1, 0, (const void *)r);
//    // mul_manageOverflow
//    if (!mpz_fits_sint_p(rax))
//    {
//        rawCopyS2L(r, temp);
//    }
//    else
//    {
//        r->type = Fr_LONG;
//    }
//    mpz_clear(rax);
//}

// Implemented, Not checked 1
void add_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    mpz_t rax;
    mpz_init(rax);

    int64_t temp = (int64_t)a->shortVal + (int64_t)b->shortVal;
    r->shortVal = (int32_t)temp;
    mpz_import(rax, 1, -1, 8, -1, 0, (const void *)r);
    // mul_manageOverflow
    if (!mpz_fits_sint_p(rax))
    {
        rawCopyS2L(r, temp);
        //std::cout << "rawCopyS2L" << "\n";
    }
    else
    {
        //r->type = Fr_LONG;
        //std::cout << "Not rawCopyS2L" << "\n";
    }
    mpz_clear(rax);
}
// Implemented, Not checked 2
void add_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmp1;
    FrElement tmp2;

    r->type = Fr_LONG;
    Fr_rawAdd(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 3
void add_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, a);
    Fr_rawAdd(&r->longVal[0], &r->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 4
void add_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawAdd(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 5
void add_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, b);
    Fr_rawAdd(&r->longVal[0], &r->longVal[0], &a->longVal[0]);
}

// Implemented, Not checked 6
void add_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrRawElement tmp1 = {0,0,0,0};

    r->type = Fr_LONG;
    if (a->shortVal >= 0)
    {
        tmp1[0] = a->shortVal;
        Fr_rawAdd(&r->longVal[0], &b->longVal[0], &tmp1[0]);
    }
    else
    {
        tmp1[0] = a->shortVal * (-1);
        Fr_rawSub(&r->longVal[0], &b->longVal[0], &tmp1[0]);
    }
}
// Implemented, Not checked 7
void add_l1ms2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, b);
    Fr_rawAdd(&r->longVal[0], &r->longVal[0], &a->longVal[0]);
}

// Implemented, Not checked 8
void add_s1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, a);
    Fr_rawAdd(&r->longVal[0], &r->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 9
void add_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    FrRawElement tmp1 = {0,0,0,0};

    r->type = Fr_LONG;
    if (b->shortVal >= 0)
    {
        tmp1[0] = b->shortVal;
        Fr_rawAdd(&r->longVal[0], &a->longVal[0], &tmp1[0]);
    }
    else
    {
        tmp1[0] = b->shortVal * (-1);
        Fr_rawSub(&r->longVal[0], &a->longVal[0], &tmp1[0]);
    }
}

// Implemented, Not checked 10
void add_l1ms2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawAdd(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}
// Implemented, Not checked 11
void add_s1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawAdd(&r->longVal[0], &a->longVal[0], &b->longVal[0]);
}

void Fr_add(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // add_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // add_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // add_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    add_l1ml2m(r, a, b);
                }
                else
                {
                    add_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                add_l1nl2m(r, a, b);
            }
            else
            {
                add_l1nl2n(r, a, b);
            }
        }
        //add_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // add_l1ms2
            if (b->type == Fr_SHORT) // check if montgomery second
            {
                add_l1ms2n(r, a, b);
            }
            else
            {
                add_l1ms2m(r, a, b);
            }

        }
        // add_l1ns2
        else
        {
            add_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // add_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // add_s1l2m
            if (a->type == Fr_SHORTMONTGOMERY)// check if montgomery first
            {
               // add_s1ml2m
               add_s1ml2m(r,a,b);
            }
            else
            {
               // add_s1nl2m
               add_s1nl2m(r,a,b);
            }
        }
        else
        {
            // add_s1l2n
            add_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         add_s1s2(r, a, b);
    }
}

//Implemented, not checked
int Fr_isTrue(PFrElement pE)
{
    PFrElement tmp = pE;

    if (tmp->type & Fr_LONG)
    {
       // tmp_140
       if (tmp->longVal[0] & tmp->longVal[0])
           return 1;
       if (tmp->longVal[1] & tmp->longVal[1])
           return 1;
       if (tmp->longVal[2] & tmp->longVal[2])
           return 1;
       if (tmp->longVal[3] & tmp->longVal[3])
           return 1;
       return 0;
    }
    else
    {
        if (tmp->shortVal & tmp->shortVal)
            return 1;
        else
           return 0;
    }
}

int Fr_longNeg(FrRawElement tmp, uint64_t * rax)
{
    uint64_t   rcx = 0;
    uint64_t   carry = 0;
    // Fr_longNeg
    *rax = tmp[0];
    carry = mpn_sub_n (rax, rax, &Fr_rawq[0], 1);
    if(!carry)
    {
       // Fr_longErr
       Fr_fail();
       return 0;
    }

    rcx = tmp[1];
    carry = mpn_sub_n (&rcx, &rcx, &Fr_rawq[1], 1);
    if(!carry)
    {
       // Fr_longErr
       Fr_fail();
       return 0;
    }

    rcx = tmp[2];
    carry = mpn_sub_n (&rcx, &rcx, &Fr_rawq[2], 1);
    if(!carry)
    {
       // Fr_longErr
       Fr_fail();
       return 0;
    }

    rcx = tmp[3];
    carry = mpn_sub_n (&rcx, &rcx, &Fr_rawq[3], 1);
    if(!carry)
    {
       // Fr_longErr
       Fr_fail();
       return 0;
    }
}

// Implemented, not checked
// Convert a 64 bit integer to a long format field element
int Fr_toInt(PFrElement pE)
{
    PFrElement ptmp = pE;
    FrRawElement tmp = {0,0,0,0};
    uint64_t   rcx = 0;
    uint64_t   rax = 0;
    int retVal = 0;

    rax = pE->shortVal;

    if (pE->type & Fr_LONG)
    {
       //Fr_long
       if (pE->type != Fr_LONGMONTGOMERY)
       {
           // Fr_longNormal
           rax = ptmp->longVal[0];
           rcx = rax;
           mpn_rshift(&rcx, &rcx, 1, 31);
           std::memcpy(tmp, &ptmp->longVal[0], sizeof(FrRawElement));

           if (rcx != 0)
           {
               Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[1];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[2];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[3];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }
       }
       else
       {
           // Fr_longMontgomery
           Fr_toNormal(ptmp,pE);
           // Fr_longNormal
           rax = ptmp->longVal[0];
           rcx = rax;
           mpn_rshift(&rcx, &rcx, 1, 31);
           std::memcpy(tmp, &ptmp->longVal[0], sizeof(FrRawElement));

           if (rcx != 0)
           {
               Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[1];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[2];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }

           rcx = ptmp->longVal[3];
           if (rcx & rcx)
           {
                Fr_longNeg(tmp, &rax);
           }
       }
    }

   retVal = rax;
   return retVal;
}

// Implemented, Not checked 1
int rlt_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal < b->shortVal)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rltRawL1L2(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawB, pRawA, 4);
    std::cout << "rltRawL1L2" << "\n";
    if (carry)
    {
        return 1;
    }
    if (carry <= 0)
    {
        return 0;
    }
}

int rltl1l2_n1(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(half, pRawB, 4);
    std::cout << "rltl1l2_n1" << "\n";
    if (carry)
    {
        return rltRawL1L2(pRawResult, pRawA, pRawB);
    }
    if (carry != 0)
    {
        return 1;
    }
}

int rltl1l2_p1(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawB, half, 4);
    std::cout << "rltl1l2_p1" << "\n";
    if (carry)
    {
        return 0;
    }
    if (carry <= 0)
    {
        return rltRawL1L2(pRawResult, pRawA, pRawB);
    }
}

int rltL1L2(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    //int retVal = 0;
    int carry = 0;
    carry = mpn_cmp(half, pRawA, 4);
    if (carry)
    {
        return rltl1l2_n1(pRawResult, pRawA, pRawB);
    }
    if (carry <= 0)
    {
        return rltl1l2_p1(pRawResult, pRawA, pRawB);
    }
    //return retVal;
}

// Implemented, Not checked 2
int rlt_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    std::cout << "rlt_l1nl2n " << "\n";
    // rltL1L2
    return rltL1L2(&r->longVal[0], &a->longVal[0], &b->longVal[0]);

}
// Implemented, Not checked 3
int rlt_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toNormal(tmpb,b);
    rltL1L2(r->longVal, a->longVal, tmpb->longVal);
}
// Implemented, Not checked 4
int rlt_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmpa = {0,0,{0,0,0,0}};
    FrElement tmpb = {0,0,{0,0,0,0}};
    std::memcpy(&tmpa, &a, sizeof (FrElement));
    std::memcpy(&tmpb, &b, sizeof (FrElement));
    Fr_toNormal(&tmpa,&tmpa);
    Fr_toNormal(&tmpb,&tmpb);
    return rltL1L2(r->longVal, tmpa.longVal, tmpb.longVal);
}
// Implemented, Not checked 5
int rlt_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement tmpa = {0,0,{0,0,0,0}};

    std::memcpy(&tmpa, &a, sizeof (FrElement));
    Fr_toNormal(&tmpa,&tmpa);
    return rltL1L2(r->longVal, tmpa.longVal, b->longVal);
}

// Implemented, Not checked 6
int rlt_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toLongNormal(tmpa,a);
    return rltL1L2(r->longVal, tmpa->longVal, b->longVal);
}
// Implemented, Not checked 7
int rlt_l1ms2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    PFrElement tmpb = b;
    Fr_toNormal(tmpa,a);
    Fr_toLongNormal(tmpb,b);
    return rltL1L2(r->longVal, tmpa->longVal, tmpb->longVal);
}

// Implemented, Not checked 8
int rlt_s1l2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    PFrElement tmpb = b;
    Fr_toLongNormal(tmpa,a);
    Fr_toNormal(tmpb,b);
    return rltL1L2(r->longVal, tmpa->longVal, tmpb->longVal);
}
// Implemented, Not checked 9
int rlt_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toLongNormal(tmpb,b);
    return rltL1L2(r->longVal, a->longVal, tmpb->longVal);
}

// Implemented, not checked
void Fr_rlt(PFrElement r, PFrElement a, PFrElement b)
{
    int rax = 0;
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // rlt_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // rlt_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // rlt_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    rax = rlt_l1ml2m(r, a, b);
                }
                else
                {
                    rax = rlt_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                rax = rlt_l1nl2m(r, a, b);
            }
            else
            {
                rax = rlt_l1nl2n(r, a, b);
            }
        }
        //rlt_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // rlt_l1ms2
            rax = rlt_l1ms2(r, a, b);
        }
        else
        {
            // rlt_l1ns2
            rax = rlt_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // rlt_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // rlt_s1l2m
            rax = rlt_s1l2m(r,a,b);
        }
        else
        {
            // add_s1l2n
            rax = rlt_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         rax = rlt_s1s2(r, a, b);
    }
    r->shortVal = rax;
}

// Implemented, not checked
void Fr_lt(PFrElement r, PFrElement a, PFrElement b)
{
    Fr_rlt(r, a, b);
}

//Implemented, not checked
void Fr_geq(PFrElement r, PFrElement a, PFrElement b)
{
   mp_limb_t rax = 0;
   Fr_rlt(r, a, b);
   rax = r->shortVal;
   mpn_xor_n(&rax, &rax, &rax, 1);
   r->shortVal = rax;
}

//Implemented, not checked
void Fr_neg(PFrElement r, PFrElement a)
{
    mp_limb_t tmp = 0;

    r->type = a->type;
    if (a->type & Fr_LONG)
    {
        // neg_l
        Fr_rawNeg(&r->longVal[0], &a->longVal[0]);
    }
    else
    {
        // neg_s
        tmp = a->shortVal * (-1);
        //mpn_neg(&tmp,&tmp,1);
        if (tmp >= 0x80000000) // Check if overflow. (0x80000000 is the only case)
        {
            // neg_manageOverflow
            rawCopyS2L(r, tmp);
        }
        else
        {
           r->shortVal = tmp;
        }
    }
}

int reqL1L2(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawA, pRawB, 4);
    if (carry == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Implemented, Not checked 1
int req_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal == b->shortVal)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Implemented, Not checked 2
int req_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    // rltL1L2
    return reqL1L2(&r->longVal[0], &a->longVal[0], &b->longVal[0]);

}
// Implemented, Not checked 3
int req_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toMontgomery(tmpa,a);
    return reqL1L2(r->longVal, tmpa->longVal, b->longVal);
}
// Implemented, Not checked 4
int req_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    // rltL1L2
    return reqL1L2(r->longVal, a->longVal, b->longVal);
}
// Implemented, Not checked 5
int req_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toMontgomery(tmpb,b);
    return reqL1L2(r->longVal, a->longVal, tmpb->longVal);
}

// Implemented, Not checked 6
int req_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toLongNormal(tmpa,a);
    return reqL1L2(r->longVal, tmpa->longVal, b->longVal);
}
// Implemented, Not checked 7
int req_l1ms2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toMontgomery(tmpb,b);
    return reqL1L2(r->longVal, a->longVal, tmpb->longVal);
}

// Implemented, Not checked 8
int req_s1l2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toMontgomery(tmpa,a);
    return reqL1L2(r->longVal, tmpa->longVal, b->longVal);
}
// Implemented, Not checked 9
int req_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toLongNormal(tmpb,b);
    return reqL1L2(r->longVal, a->longVal, tmpb->longVal);
}

//Not Implemented, not checked
// Compares two elements of any kind
// returns in ax 1 id *rsi == *rdx
void Fr_req(PFrElement r, PFrElement a, PFrElement b)
{
    int rax = 0;
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // req_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // req_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // req_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    rax = req_l1ml2m(r, a, b);
                }
                else
                {
                    rax = req_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                rax = req_l1nl2m(r, a, b);
            }
            else
            {
                rax = req_l1nl2n(r, a, b);
            }
        }
        //rlt_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // rlt_l1ms2
            rax = req_l1ms2(r, a, b);
        }
        else
        {
            // rlt_l1ns2
            rax = req_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // rlt_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // rlt_s1l2m
            rax = req_s1l2m(r,a,b);
        }
        else
        {
            // add_s1l2n
            rax = req_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         rax = req_s1s2(r, a, b);
    }
    r->shortVal = rax;
}
//Implemented, not checked
void Fr_eq(PFrElement r, PFrElement a, PFrElement b)
{
    Fr_req(r, a, b);
}

//Implemented, not checked
void Fr_neq(PFrElement r, PFrElement a, PFrElement b)
{
    mp_limb_t rax = 0;
    Fr_req(r, a, b);
    rax = r->shortVal;
    mpn_xor_n(&rax, &rax, &rax, 1);
    r->shortVal = rax;
}

// Implemented, not checked
// Logical or between two elements
void Fr_lor(PFrElement r, PFrElement a, PFrElement b)
{
   FrElement rax = {0,0,{0,0,0,0}};
   std::memcpy(&rax, &a, sizeof (FrElement));
   uint64_t r8 = 0;
   uint64_t rcx = 0;
   mp_limb_t cmpVal[Fr_N64] = {0,0,0,0};

   // l1
   if(rax.type & Fr_LONG)
   {
       // tmp_128
       mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
       if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
       {
           // retOne_129
           r8 = 1;
           // done_131
           std::memcpy(&rax, &b, sizeof (FrElement));
           // l1l2
           if(rax.type & Fr_LONG)
           {
               // tmp_132
               mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
               if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
               {
                    // retOne_133
                    rcx = 1;
                    // done_135
                    mpn_ior_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
               }
               else
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
           // l1s2
           else
           {
               // test    eax, eax
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }

       }
       else
       {
           // retZero_130:
           r8 = 0;
           // done_131
           std::memcpy(&rax, &b, sizeof (FrElement));
           // l1l2
           if(rax.type & Fr_LONG)
           {
               // tmp_132
               mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
               if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
               {
                    // retOne_133
                    rcx = 1;
                    // done_135
                    mpn_ior_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
               }
               else
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
           else // l1s2
           {
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
       }
   }
   //s1
   else
   {
       mp_limb_t raxTmp = rax.shortVal;
       mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
       if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
       {
           // retZero_130:
           r8 = 0;
           // done_131
           std::memcpy(&rax, &b, sizeof (FrElement));
           // l1l2
           if(rax.type & Fr_LONG)
           {
               // tmp_132
               mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
               if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
               {
                    // retOne_133
                    rcx = 1;
                    // done_135
                    mpn_ior_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
               }
               else
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
           else // l1s2
           {
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
       }
       else
       {
           // retOne_129
           r8 = 1;
           // done_131
           std::memcpy(&rax, &b, sizeof (FrElement));
           // l1l2
           if(rax.type & Fr_LONG)
           {
               // tmp_132
               mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
               if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
               {
                    // retOne_133
                    rcx = 1;
                    // done_135
                    mpn_ior_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
               }
               else
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
           // l1s2
           else
           {
               // test    eax, eax
               mp_limb_t raxTmp = rax.shortVal;
               mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
               if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
               {
                   // retZero_134
                   rcx = 0;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
               else
               {
                   // retOne_133
                   rcx = 1;
                   // done_135
                   mpn_ior_n(&rcx,&rcx,&r8, 1);
                   r->shortVal = rcx;
                   return;
               }
           }
       }
   }
}

// Implemented, Not checked 1
int rgt_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal > b->shortVal)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rgtRawL1L2(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawA, pRawB, 4);
    if (carry)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rgtl1l2_n1(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawB, half, 4);
    if (carry)
    {
        return rgtRawL1L2(pRawResult, pRawA, pRawB);
    }
    else
    {
        return 0;
    }
}

int rgtl1l2_p1(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawB, half, 4);
    if (carry)
    {
        return 1;
    }
    else
    {
        return rgtRawL1L2(pRawResult, pRawA, pRawB);
    }
}

int rgtL1L2(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    int carry = 0;
    carry = mpn_cmp(pRawA, half, 4);
    if (carry)
    {
        rgtl1l2_n1(pRawResult, pRawA, pRawB);
    }
    else
    {
        rgtl1l2_p1(pRawResult, pRawA, pRawB);
    }
}

// Implemented, Not checked 2
int rgt_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    // rltL1L2
    return rgtRawL1L2(&r->longVal[0], &a->longVal[0], &b->longVal[0]);

}
// Implemented, Not checked 3
int rgt_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toNormal(tmpb,b);
    return rgtL1L2(r->longVal, a->longVal, tmpb->longVal);
}
// Implemented, Not checked 4
int rgt_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    PFrElement tmpb = b;
    Fr_toNormal(tmpa,tmpa);
    Fr_toNormal(tmpb,tmpb);
    return rgtL1L2(r->longVal, tmpa->longVal, tmpb->longVal);
}
// Implemented, Not checked 5
int rgt_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toNormal(tmpa,a);
    return rgtL1L2(r->longVal, tmpa->longVal, b->longVal);
}

// Implemented, Not checked 6
int rgt_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    Fr_toLongNormal(tmpa,a);
    return rgtL1L2(r->longVal, tmpa->longVal, b->longVal);
}
// Implemented, Not checked 7
int rgt_l1ms2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    PFrElement tmpb = b;
    Fr_toNormal(tmpa,a);
    Fr_toLongNormal(tmpb,b);
    return rgtL1L2(r->longVal, tmpa->longVal, tmpb->longVal);
}

// Implemented, Not checked 8
int rgt_s1l2m(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpa = a;
    PFrElement tmpb = b;
    Fr_toLongNormal(tmpa,a);
    Fr_toNormal(tmpb,b);
    return rgtL1L2(r->longVal, tmpa->longVal, tmpb->longVal);
}
// Implemented, Not checked 9
int rgt_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    PFrElement tmpb = b;
    Fr_toLongNormal(tmpb,b);
    return rgtL1L2(r->longVal, a->longVal, tmpb->longVal);
}

// Implemented, not checked
void Fr_rgt(PFrElement r, PFrElement a, PFrElement b)
{
    int rax = 0;
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // rgt_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // rgt_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // rgt_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    rax = rgt_l1ml2m(r, a, b);
                }
                else
                {
                    rax = rgt_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                rax = rgt_l1nl2m(r, a, b);
            }
            else
            {
                rax = rgt_l1nl2n(r, a, b);
            }
        }
        //rgt_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // rgt_l1ms2
            rax = rgt_l1ms2(r, a, b);
        }
        else
        {
            // rgt_l1ns2
            rax = rgt_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // rgt_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // rgt_s1l2m
            rax = rgt_s1l2m(r,a,b);
        }
        else
        {
            // rgt_s1l2n
            rax = rgt_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         rax = rgt_s1s2(r, a, b);
    }
    r->shortVal = rax;
}


//Implemented, not checked
void Fr_gt(PFrElement r, PFrElement a, PFrElement b)
{
    Fr_rgt(r,a,b);
}

// Logical and between two elements
//Implemented, not checked
void Fr_land(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    std::memcpy(&rax, a, sizeof (FrElement));
    uint64_t r8 = 0;
    uint64_t rcx = 0;
    mp_limb_t cmpVal[Fr_N64] = {0,0,0,0};

    std::cout << "rax.type  "  << std::hex <<  rax.type << "\n";
    // l1
    if(rax.type & Fr_LONG)
    {
        // tmp_120
        mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
        if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
        {
            // retOne_121
            r8 = 1;
            // done_123
            std::memcpy(&rax, &b, sizeof (FrElement));
            // l1l2
            if(rax.type & Fr_LONG)
            {
                // tmp_124
                mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
                if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
                {
                     std::cout << "1 " << "\n";
                     // retOne_125
                     rcx = 1;
                     // done_127
                     mpn_and_n(&rcx,&rcx,&r8, 1);
                     r->shortVal = rcx;
                     return;
                }
                std::cout << "2 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            // l1s2
            // test    eax, eax
            mp_limb_t raxTmp = rax.shortVal;
            mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
            if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
            {
                std::cout << "3 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            else
            {
                std::cout << "4 " << "\n";
                // retOne_125
                rcx = 1;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }

        }
        else
        {
            // retZero_122:
            r8 = 0;
            // done_123
            std::memcpy(&rax, &b, sizeof (FrElement));
            // l1l2
            if(rax.type & Fr_LONG)
            {
                // tmp_124
                mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
                if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
                {
                    std::cout << "5 " << "\n";
                     // retOne_125
                     rcx = 1;
                     // done_127
                     mpn_and_n(&rcx,&rcx,&r8, 1);
                     r->shortVal = rcx;
                     return;
                }
                std::cout << "6 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            // l1s2
            mp_limb_t raxTmp = rax.shortVal;
            mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
            if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
            {
                std::cout << "7 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            std::cout << "8 " << "\n";
            // retOne_125
            rcx = 1;
            // done_127
            mpn_and_n(&rcx,&rcx,&r8, 1);
            r->shortVal = rcx;
            return;
        }
    }
    //s1
    else
    {
        mp_limb_t raxTmp = rax.shortVal;
        mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
        if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
        {
            // retZero_122:
            r8 = 0;
            // done_123
            std::memcpy(&rax, &b, sizeof (FrElement));
            // l1l2
            if(rax.type & Fr_LONG)
            {
                // tmp_124
                mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
                if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
                {
                    std::cout << "9 " << "\n";
                     // retOne_125
                     rcx = 1;
                     // done_127
                     mpn_and_n(&rcx,&rcx,&r8, 1);
                     r->shortVal = rcx;
                     return;
                }
                std::cout << "10 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            // l1s2
            mp_limb_t raxTmp = rax.shortVal;
            mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
            if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
            {
                std::cout << "11 " << "\n";
                // retZero_126
                rcx = 0;
                // done_127
                mpn_and_n(&rcx,&rcx,&r8, 1);
                r->shortVal = rcx;
                return;
            }
            std::cout << "12 " << "\n";
            // retOne_125
            rcx = 1;
            // done_127
            mpn_and_n(&rcx,&rcx,&r8, 1);
            r->shortVal = rcx;
            return;
        }
        else
        {
            // retOne_121
            r8 = 1;
            // done_123
            std::memcpy(&rax, &b, sizeof (FrElement));
            // l1l2
            if(rax.type & Fr_LONG)
            {
                // tmp_124
                mpn_and_n(rax.longVal,rax.longVal,rax.longVal, 4);
                if ( mpn_cmp(rax.longVal, cmpVal, Fr_N64) !=0)
                {
                    std::cout << "13 " << "\n";
                     // retOne_125
                     rcx = 1;
                     // done_127
                     mpn_and_n(&rcx,&rcx,&r8, 1);
                     r->shortVal = rcx;
                     return;
                }
                else
                {
                    std::cout << "14 " << "\n";
                    // retZero_126
                    rcx = 0;
                    // done_127
                    mpn_and_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
                }
                mp_limb_t raxTmp = rax.shortVal;
                mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
                if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
                {
                    std::cout << "15 " << "\n";
                    // retZero_126
                    rcx = 0;
                    // done_127
                    mpn_and_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
                }
                else
                {
                    std::cout << "16 " << "\n";
                    // retOne_125
                    rcx = 1;
                    // done_127
                    mpn_and_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
                }
            }
            // l1s2
            else
            {
                // test    eax, eax
                mp_limb_t raxTmp = rax.shortVal;
                mpn_and_n(&raxTmp,&raxTmp,&raxTmp, 1);
                if ( mpn_cmp(&raxTmp, &cmpVal[0], 1) == 0)
                {
                    std::cout << "17 " << "\n";
                    // retZero_126
                    rcx = 0;
                    // done_127
                    mpn_and_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
                }
                else
                {
                    std::cout << "18 " << "\n";
                    // retOne_125
                    rcx = 1;
                    // done_127
                    mpn_and_n(&rcx,&rcx,&r8, 1);
                    r->shortVal = rcx;
                    return;
                }
            }
        }
    }
}

// Implemented, Not checked 1
void and_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    mp_limb_t cmpVal = 0;
    mp_limb_t eax = a->shortVal;
    mp_limb_t ecx = b->shortVal;
    mp_limb_t edx = b->shortVal;
    FrElement tmpa = {0,0,{0,0,0,0}};
    FrElement tmpb = {0,0,{0,0,0,0}};
    std::memcpy(&tmpa, &a, sizeof (FrElement));
    std::memcpy(&tmpb, &b, sizeof (FrElement));
    PFrElement rax;
    std::memcpy(&rax, &a, sizeof (FrElement));

    if(mpn_cmp(&eax, &cmpVal, 1) < 0)
    {
        // tmp_13
        r->type = Fr_LONG;
        Fr_toLongNormal(&tmpa,a);
        Fr_toLongNormal(&tmpb,b);
        std::memcpy(&rax, &tmpa, sizeof (FrElement));
        mpn_and_n(rax->longVal,rax->longVal, tmpb.longVal, Fr_N64);
        mpn_and_n(&rax->longVal[3],&rax->longVal[3], &lboMask, 1);
        std::memcpy(&r, &rax, sizeof (FrElement));

        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
        {
            // tmp_15
            // q is bigget so done
            return;
        }
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) < 0)
        {
            // tmp_14
            // q is lower
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }
    }

    if(mpn_cmp(&ecx, &cmpVal, 1) < 0)
    {
        // tmp_13
        r->type = Fr_LONG;
        Fr_toLongNormal(&tmpa,a);
        Fr_toLongNormal(&tmpb,b);
        std::memcpy(&rax, &tmpa, sizeof (FrElement));
        mpn_and_n(rax->longVal,rax->longVal, tmpb.longVal, Fr_N64);
        mpn_and_n(&rax->longVal[3],&rax->longVal[3], &lboMask, 1);
        std::memcpy(&r, &rax, sizeof (FrElement));

        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
        {
            // tmp_15
            // q is bigget so done
            return;
        }
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) < 0)
        {
            // tmp_14
            // q is lower
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }
    }
    edx = eax;
    mpn_and_n(&edx, &edx, &ecx, 1);
    r->shortVal = edx;
}

// Implemented, Not checked 2
void and_l1nl2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    r->type = Fr_LONG;
    std::memcpy(&rax, &a, sizeof (FrElement));
    mpn_and_n(rax.longVal,rax.longVal, b->longVal, Fr_N64);
    mpn_and_n(&rax.longVal[3],&rax.longVal[3], &lboMask, 1);
    std::memcpy(&r, &rax, sizeof (FrElement));

    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
    {
        // tmp_36
        return;
    }
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) != 0)
    {
        // tmp_37
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return ;
    }

}
// Implemented, Not checked 3
void and_l1nl2m(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rdx = {0,0,{0,0,0,0}};
    std::memcpy(&rdx, &b, sizeof (FrElement));
    r->type = Fr_LONG;
    Fr_toNormal(&rdx,&rdx);
    std::memcpy(&rax, &a, sizeof (FrElement));
    mpn_and_n(rax.longVal,rax.longVal, rdx.longVal, Fr_N64);
    mpn_and_n(&rax.longVal[3],&rax.longVal[3], &lboMask, 1);
    std::memcpy(&r, &rax, sizeof (FrElement));
    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
    {
        // tmp_39
        return;
    }
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) != 0)
    {
        // tmp_38
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}
// Implemented, Not checked 4
void and_l1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rsi = {0,0,{0,0,0,0}};
    FrElement rdx = {0,0,{0,0,0,0}};
    std::memcpy(&rsi, &a, sizeof (FrElement));
    std::memcpy(&rdx, &b, sizeof (FrElement));
    r->type = Fr_LONG;
    Fr_toNormal(&rdx,&rdx);
    Fr_toNormal(&rsi,&rsi);
    std::memcpy(&rax, &rsi, sizeof (FrElement));
    mpn_and_n(rax.longVal,rax.longVal, rdx.longVal, Fr_N64);
    mpn_and_n(&rax.longVal[3],&rax.longVal[3], &lboMask, 1);
    std::memcpy(&r, &rax, sizeof (FrElement));
    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
    {
        // tmp_43
        return;
    }
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) != 0)
    {
        // tmp_42
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}
// Implemented, Not checked 5
void and_l1ml2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rsi = {0,0,{0,0,0,0}};
    std::memcpy(&rsi, &a, sizeof (FrElement));
    r->type = Fr_LONG;
    Fr_toNormal(&rsi,&rsi);
    std::memcpy(&rax, &rsi, sizeof (FrElement));
    mpn_and_n(rax.longVal,rax.longVal, b->longVal, Fr_N64);
    mpn_and_n(&rax.longVal[3],&rax.longVal[3], &lboMask, 1);
    std::memcpy(&r, &rax, sizeof (FrElement));
    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
    {
        // tmp_41
        return;
    }
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) != 0)
    {
        // tmp_40
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}

// Implemented, Not checked 6
void and_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rdx = {0,0,{0,0,0,0}};
    FrElement rcx;
    mp_limb_t cmpVal = 0;
    mp_limb_t tmprax = 0;
    mp_limb_t ecx = 0;

    r->type = Fr_LONG;
    std::memcpy(&rcx, &b, sizeof (FrElement));
    std::memcpy(&rax, &a, sizeof (FrElement));
    tmprax = rax.shortVal;
    ecx = rcx.shortVal;
    if(mpn_cmp(&ecx, &cmpVal, 1) < 0)
    {
        // tmp_16
        Fr_toLongNormal(&rdx,b);
        r->type = Fr_LONG;
        mpn_and_n(r->longVal,rax.longVal, rdx.longVal, Fr_N64);
        mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);
        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
        {
            // tmp_20
            return;
        }
        else
        {
            // tmp_19
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }

    }

    rax.longVal[0] = ecx;

    mpn_and_n(r->longVal,rax.longVal, b->longVal, Fr_N64);
    mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);

    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
    {
        // tmp_18
        return;
    }
    else
    {
        // tmp_17
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}
// Implemented, Not checked 7
void and_l1ms2(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    mp_limb_t cmpVal = 0;
    mp_limb_t tmprax = 0;
    mp_limb_t tmprcx = 0;
    rax.shortVal = a->shortVal;
    tmprcx = b->shortVal;
    r->type = Fr_LONG;
    tmprax = rax.shortVal;

    Fr_toNormal(r,r);

    if(mpn_cmp(&tmprcx, &cmpVal, 1) < 0)
    {
        // tmp_21
        Fr_toLongNormal(r,r);
        r->type = Fr_LONG;
        mpn_and_n(&rax.longVal[0],a->longVal, b->longVal, Fr_N64);
        mpn_and_n(&rax.longVal[3],&rax.longVal[3], &lboMask, 1);
        std::memcpy(&r, &rax, sizeof (FrElement));
        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
        {
            // tmp_30
            return;
        }
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) != 0)
        {
            // tmp_29
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }

    }
    mpn_and_n(r->longVal,&tmprcx, a->longVal, Fr_N64);
    mpn_and_n(&r->longVal[3],&tmprax, &lboMask, 1);

    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) > 0)
    {
        // tmp_22
        return;
    }
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) < 0)
    {
        // tmp_23
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}

// Implemented, Not checked 8
void and_s1l2m(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rsi;
    mp_limb_t cmpVal = 0;
    mp_limb_t tmprax = 0;

    r->type = Fr_LONG;
    std::memcpy(&rsi, &b, sizeof (FrElement));
    Fr_toNormal(&rsi,&rsi);
    std::memcpy(&rax, &rsi, sizeof (FrElement));
    tmprax = rsi.shortVal;

    if(mpn_cmp(&tmprax, &cmpVal, 1) < 0)
    {
        // tmp_31
        Fr_toLongNormal(r,r);
        r->type = Fr_LONG;
        mpn_and_n(r->longVal,rax.longVal, b->longVal, Fr_N64);
        mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);
        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
        {
            // tmp_33
            return;
        }
        else
        {
            // tmp_32
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }

    }
    rax.longVal[0] = tmprax;

    mpn_and_n(r->longVal,rax.longVal, b->longVal, Fr_N64);
    mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);

    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
    {
        // tmp_33
        return;
    }
    else
    {
        // tmp_32
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}
// Implemented, Not checked 9
void and_l1ns2(PFrElement r,PFrElement a,PFrElement b)
{
    FrElement rax = {0,0,{0,0,0,0}};
    FrElement rdx = {0,0,{0,0,0,0}};
    FrElement rcx;
    mp_limb_t cmpVal = 0;
    mp_limb_t tmprax = 0;
    mp_limb_t ecx = 0;

    r->type = Fr_LONG;
    std::memcpy(&rcx, &b, sizeof (FrElement));
    std::memcpy(&rax, &a, sizeof (FrElement));
    tmprax = rax.shortVal;
    ecx = rcx.shortVal;
    if(mpn_cmp(&ecx, &cmpVal, 1) < 0)
    {
        // tmp_16
        Fr_toLongNormal(&rdx,b);
        r->type = Fr_LONG;
        mpn_and_n(r->longVal,rax.longVal, rdx.longVal, Fr_N64);
        mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);
        // Compare with q
        if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
        {
            // tmp_20
            return;
        }
        else
        {
            // tmp_19
            mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
            return;
        }

    }

    rax.longVal[0] = ecx;

    mpn_and_n(r->longVal,rax.longVal, b->longVal, Fr_N64);
    mpn_and_n(&r->longVal[3],&r->longVal[3], &lboMask, 1);

    // Compare with q
    if (mpn_cmp(&r->longVal[0], &Fr_rawq[0], Fr_N64) >= 0)
    {
        // tmp_18
        return;
    }
    else
    {
        // tmp_17
        mpn_sub_n(r->longVal,r->longVal, &Fr_rawq[0], Fr_N64);
        return;
    }
}

// Adds two elements of any kind
// Implemented, not checked
void Fr_band(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG) // Check if is short first operand
    {
        // and_l1
        if (b->type & Fr_LONG) //  Check if is short second operand
        {
            // and_l1l2
            if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
            {
                // and_l1ml2
                if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
                {
                    and_l1ml2m(r, a, b);
                }
                else
                {
                    and_l1ml2n(r, a, b);
                }
            }
            else if (b->type == Fr_LONGMONTGOMERY) // check if montgomery second
            {
                and_l1nl2m(r, a, b);
            }
            else
            {
                and_l1nl2n(r, a, b);
            }
        }
        //and_l1s2:
        else if (a->type == Fr_LONGMONTGOMERY) // check if montgomery first
        {
            // and_l1ms2
            and_l1ms2(r, a, b);
        }
        else
        {
            // and_l1ns2
           and_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)// Check if is short second operand
    {
        // and_s1l2
        if (b->type == Fr_LONGMONTGOMERY)// check if montgomery second
        {
            // and_s1l2m
            and_s1l2m(r,a,b);
        }
        else
        {
            // and_s1l2n
            and_s1l2n(r,a,b);
        }
    }
    else // ; Both operands are short
    {
         and_s1s2(r, a, b);
    }
}

void Fr_rawZero(FrRawElement pRawResult)
{
    std::memset(pRawResult, 0, sizeof(FrRawElement));
}


// Adds two elements of any kind
void rawShl(FrRawElement r, FrRawElement a, FrRawElement b)
{
    mp_limb_t cmpVal = 0;
    mp_limb_t cmpVal2 = 254;
    mp_limb_t cmpVal3[Fr_N64] = {0,0,0,0};
    mp_limb_t cmpVal4 = 3;
    mp_limb_t cmpVal5 = 2;
    mp_limb_t cmpVal6 = 1;
    mp_limb_t cmpVal7 = 0;
    mp_limb_t andVal = 0x3F;
    mp_limb_t r8[Fr_N64] = {0,0,0,0};
    mp_limb_t rcx[Fr_N64] = {0,0,0,0};
    mp_limb_t rdx[Fr_N64] = {0,0,0,0};
    mp_limb_t rax[Fr_N64] = {0,0,0,0};
    mp_limb_t rdi[Fr_N64] = {0,0,0,0};

    if (mpn_cmp(&b[0], &cmpVal, 1) == 0)
    {
        Fr_rawCopy(r,a);
    }

    if (mpn_cmp(&b[0], &cmpVal2, 1) >= 0)
    {
        Fr_rawZero(r);
    }
    std::memcpy(r8, b, sizeof(FrRawElement));
    std::memcpy(rcx, b, sizeof(FrRawElement));
    mpn_rshift(r8, r8, 4, 6);
    mpn_and_n (rcx, rcx, &andVal, 4);
    if ( mpn_cmp(rcx, cmpVal3, Fr_N64) ==0)
    {
        // rawShl_aligned
        std::memcpy(rdx, a, sizeof(FrRawElement));
        std::memcpy(rax, r8, sizeof(FrRawElement));
        mpn_lshift(rax, rax, 4, 3);
        mpn_sub_n(rdx, rdx, rax, 4);
        if (mpn_cmp(r8, &cmpVal4, Fr_N64) > 0)
        {
            // rawShl_if3_3
            mpn_xor_n(rax, rax, rax, 4);
            rdi[3] = rax[0];
            // rawShl_endif3_3
            if ( mpn_cmp(r8, &cmpVal5, 1) > 0)
            {
                // ja rawShl_if3_2
                mpn_xor_n(rax, rax, rax, 4);
                rdi[2] = rax[0];
            }
            rax[0] = rdx[2];
            rdi[2] = rax[0];
            // rawShl_endif3_2
            if (mpn_cmp(r8, &cmpVal6, 1) > 0)
            {
                // rawShl_if3_1
                mpn_xor_n(rax, rax, rax, 4);
                rdi[1] = rax[0];
            }
            rax[0] = rdx[1];
            rdi[1] = rax[0];
            // rawShl_endif3_1
            if (mpn_cmp(r8, &cmpVal7, 1) > 0)
            {
                // rawShl_if3_0
                mpn_xor_n(rax, rax, rax, 4);
                rdi[0] = rax[0];
            }
            rax[0] = rdx[0];
            rdi[0] = rax[0];
            // rawShl_endif3_0
            // Compare with q
            std::memcpy(rax, rdi, sizeof(FrRawElement));
            if (mpn_cmp(rax, Fr_rawq, Fr_N64) >= 0)
            {
                // tmp_111
                std::memcpy(rax, Fr_rawq, sizeof(FrRawElement));
                mpn_sub_n(rdi,rdi,rax,4);
                std::memcpy(r, rdi, sizeof(FrRawElement));
                return;
            }

            if (mpn_cmp(rax, Fr_rawq, Fr_N64) < 0)
            {
                // tmp_110
                std::memcpy(r, rdi, sizeof(FrRawElement));
                return;
            }
        }
    }



}



void do_shl(PFrElement r, PFrElement a, PFrElement b)
{
    PFrElement rcx;
    std::memcpy(rcx, a, sizeof(FrElement));
    if (rcx->type & Fr_LONG)
    {
        // do_shll
        if (rcx->type == Fr_LONGMONTGOMERY)
        {
            Fr_toNormal(b,b);
        }
        else
        {
            // do_shlln
            r->type = Fr_LONG;
            //rawShl
        }
    }

}

//Not Implemented, not checked
// Adds two elements of any kind
void Fr_shr(PFrElement r, PFrElement a, PFrElement b)
{
//    mp_limb_t ma[Fr_N64] = {a->longVal[0], pRawA[1], pRawA[2], pRawA[3]};
//    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
//    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
//    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
//    mp_limb_t carry;
      PFrElement rtmp;
      mp_limb_t rcx[Fr_N64] = {0,0,0,0};
      mp_limb_t rax[Fr_N64] = {0,0,0,0};
      mp_limb_t rdx[Fr_N64] = {0,0,0,0};
      uint64_t cmpVal = 254;
      mp_limb_t carry = 0;


    if (b->type & Fr_LONG)
    {
        if (b->type == Fr_LONGMONTGOMERY)
        {
            Fr_toNormal(rtmp, b);
            // tmp_113
            rcx[0] = rtmp->longVal[0];
            if (mpn_cmp(&rcx[0], &cmpVal, 1) >= 0)
            {
                // tmp_114
                rcx[0] = Fr_rawq[0];
                mpn_sub_n(&rcx[0], &rcx[0], &rtmp->longVal[0], 1);
                if (mpn_cmp(&rcx[0], &cmpVal, 1) >= 0)
                {
                   // jae  setzero
                   r->shortVal = 0;
                   return;
                }
                std::memcpy(rax, Fr_rawq, sizeof(FrRawElement));
                std::memcpy(rdx, &rtmp->longVal[0], sizeof(FrRawElement));
                carry = mpn_sub_n(&rax[0], &rax[0], &rdx[0], 4);
                if (carry >= 0)
                {
                    // jae  setzero
                    r->shortVal = 0;
                    return;
                }
                std::memcpy(&rdx, &rcx, Fr_N64);
                // jmp do_shl
                if(b->type & Fr_LONG)
                {
                    // do_shll
                    if (b->type & Fr_LONGMONTGOMERY)
                    {
                        Fr_toNormal(rtmp, b);
                    }
                    else
                    {
                        // do_shlln
                        r->type = Fr_LONG;
                        // rawShl
                    }


                }

            }
            else
            {

            }

        }
        else
        {
            // jnc     tmp_113
        }
    }
    else
    {
        // jnc     tmp_112

    }

}


/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib End
******************************************************************************************/

#endif
