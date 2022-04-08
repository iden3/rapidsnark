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

void rawCopyS2L(PFrElement pResult, int64_t val)
{
    mpz_t result, mq;

    mpz_inits(result, mq);

    mpz_set_si(result, val);

    if (val < 0)
    {
        Fr_to_mpz(mq, Fr_rawq);

        mpz_add(result, result, mq);
    }

    pResult->type = Fr_LONG;
    pResult->shortVal = 0;
    Fr_to_rawElement(pResult->longVal, result);

    mpz_clears(result, mq);
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

    carry = mpn_sub_n(&mr[0], &mq[0], &mb[0], 4);
    dl = carry;
    carry = mpn_sub_n(&mr[0], &mr[0], &ma[0], 4);
    dh = carry;
    mpn_ior_n(&carry,&dh,&dl,1);
    if(carry != 0)
    {
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
    Fr_rawSub(&r->longVal[0], &r->longVal[0], &a->longVal[0]);
}

// Implemented, Not checked 6
void sub_s1l2n(PFrElement r,PFrElement a,PFrElement b)
{
    FrRawElement tmp1 = {0,0,0,0};

    r->type = Fr_LONG;
    if (a->shortVal >= 0)
    {
        tmp1[0] = a->shortVal;
        Fr_rawSub(&r->longVal[0], &b->longVal[0], &tmp1[0]);
    }
    else
    {
        tmp1[0] = a->shortVal * (-1);
        rawNegLS(&r->longVal[0], &b->longVal[0], &tmp1[0]);
    }
}
// Implemented, Not checked 7
void sub_l1ms2n(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_toMontgomery(r, b);
    Fr_rawSub(&r->longVal[0], &r->longVal[0], &a->longVal[0]);
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
    if (b->shortVal >= 0)
    {
        tmp1[0] = b->shortVal * (-1);
        Fr_rawAdd(&r->longVal[0], &a->longVal[0], &tmp1[0]);
    }
    else
    {
        tmp1[0] = b->shortVal;
        Fr_rawSub(&r->longVal[0], &a->longVal[0], &tmp1[0]);
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
    if (a->type = Fr_LONGMONTGOMERY) // ; check if montgomery
    {
        // toMontgomery_doNothing
        Fr_copy(r,a);
    }
    else if (a->type = Fr_LONG)
    {
        // toMontgomeryLong
        r->type = Fr_LONGMONTGOMERY;
        Fr_rawMMul(&r->longVal[0], &a->longVal[0], &Fr_rawR2[0]);
    }
    else
    {
        // toMontgomeryShort
        if (a->shortVal < 0)
        {
           // negMontgomeryShort
           r->type = Fr_SHORTMONTGOMERY;
           mp_limb_t ma;
           ma = a->shortVal;
           // ; Do the multiplication positive and then negate the result.
           mpn_neg (&ma, &ma, 1);
           Fr_rawMMul1(&r->longVal[0], &Fr_rawR2[0], ma);
           Fr_rawNeg(&r->longVal[0], &r->longVal[0]);
           r->type = Fr_SHORTMONTGOMERY;
        }
        else
        {
           // posMontgomeryShort
            r->type = Fr_SHORTMONTGOMERY;
            Fr_rawMMul1(&r->longVal[0], &Fr_rawR2[0], a->shortVal);
        }

    }
}

// Implemented, Not checked 1
void add_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    mpz_t rax;
    mpz_init(rax);

    int64_t temp = (int64_t)a->shortVal + (int64_t)b->shortVal;
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

//Not Implemented, not checked
void Fr_lt(PFrElement r, PFrElement a, PFrElement b)
{
   *r = *a;
}

//Not Implemented, not checked
void Fr_shr(PFrElement r, PFrElement a, PFrElement b)
{
//    mp_limb_t ma[Fr_N64] = {a->longVal[0], pRawA[1], pRawA[2], pRawA[3]};
//    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
//    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
//    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
//    mp_limb_t carry;

    if (b->type == Fr_SHORT)
    {
        if (b->type == Fr_LONGMONTGOMERY)
        {

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

//Not Implemented, not checked
void Fr_band(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type == Fr_SHORT)
    {
        // and_l1
    }
    else if (b->type == Fr_SHORT)
    {
        // and_s1l2

    }
}

//Not Implemented, not checked
void Fr_eq(PFrElement r, PFrElement a, PFrElement b)
{
    *r= *a;
}

//Not Implemented, not checked
void Fr_neq(PFrElement r, PFrElement a, PFrElement b)
{
    *r= *a;
}

//Not Implemented, not checked
void Fr_gt(PFrElement r, PFrElement a, PFrElement b)
{
    *r= *a;
}

//Not Implemented, not checked
void Fr_geq(PFrElement r, PFrElement a, PFrElement b)
{
   *r = *a;
}

//Not Implemented, not checked
void Fr_lor(PFrElement r, PFrElement a, PFrElement b)
{
    *r = *a;
}

//Not Implemented, not checked
void Fr_land(PFrElement r, PFrElement a, PFrElement b)
{
    *r = *a;
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
        tmp = a->shortVal;
        mpn_neg(&tmp,&tmp,1);
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


/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib End
******************************************************************************************/

#endif
