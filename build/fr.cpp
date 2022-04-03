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


// FirstLoop 0
// Second Loop 0
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x2b5f03ec9137536d,0x806e49a91514a16c,0x31762d353b74a158,0x13d4d397da065264};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x169b0b13d72ddc98,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddd};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

////Fr_Rw_mul_test 0:
//FirstLoop 0 product= cd4d769e76216da7, 74e35452ef1a9705, 25f2e5b49bc9d231, d155f4a16a3ed651, 15250af3534de67
//Second Loop 0 result= 81c4c7a252af4887, 81d6fff3f3af68ff, e357f9dbfbeb7aff, fbf7d45beefd1ac1, 19f69453a6d418c1


//carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
////Fr_Rw_mul_test 0:
//FirstLoop 0 product= b1949058c8000000, 20e519a10bbe3d22, 99a96277480e51ac, cf3f23efeaf091ab, 15250af3534de67
//Second Loop 0 result= 0, 2b5f03ec9137536d, 806e49a91514a16c, 31762d353b74a158, 13d4d397da065264
//carry= 0
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x0,0x2b5f03ec9137536d,0x806e49a91514a16c,0x31762d353b74a158};
////Fr_Rw_mul_test 1:
//FirstLoop 0 product= 2, 0, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddf
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x0,0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca};
////Fr_Rw_mul_test 2:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x0,0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca};
////Fr_Rw_mul_test 3:
//FirstLoop 0 product= 2, ffffffffffffffff, ffffffffffffffff, ffffffffffffffff, fffffffffffffffd
//Second Loop 0 result= 0, 169b0b13d72ddc98, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddd
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x0,0x169b0b13d72ddc98,0x6c5b3334dcbfb509,0xad619b286e68fcca};
////Fr_Rw_mul_test 4:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x0,0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca};
////Fr_Rw_mul_test 5:
//FirstLoop 0 product= 0, 0, 0, 0, 0
//Second Loop 0 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 0 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 0 result= 0, 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x0,0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d};


//carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 4);
////Fr_Rw_mul_test 0:
//FirstLoop 0 product= b1949058c8000000, 20e519a10bbe3d22, 99a96277480e51ac, cf3f23efeaf091ab, 15250af3534de67
//Second Loop 0 result= 0, 2b5f03ec9137536d, 806e49a91514a16c, 31762d353b74a158, 0
//carry= 1
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x0,0x2b5f03ec9137536d,0x806e49a91514a16c,0x31762d353b74a158};
////Fr_Rw_mul_test 1:
//FirstLoop 0 product= 2, 0, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 0
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x0,0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca};
////Fr_Rw_mul_test 2:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 0
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x0,0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca};
////Fr_Rw_mul_test 3:
//FirstLoop 0 product= 2, ffffffffffffffff, ffffffffffffffff, ffffffffffffffff, fffffffffffffffd
//Second Loop 0 result= 0, 169b0b13d72ddc98, 6c5b3334dcbfb509, ad619b286e68fcca, 0
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x0,0x169b0b13d72ddc98,0x6c5b3334dcbfb509,0xad619b286e68fcca};
////Fr_Rw_mul_test 4:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 0, 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 0
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x0,0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca};
////Fr_Rw_mul_test 5:
//FirstLoop 0 product= 0, 0, 0, 0, 0
//Second Loop 0 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 0 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 0 result= 0, 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 0
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x0,0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d};



////Fr_Rw_mul_test 0:
//FirstLoop 0 product= b1949058c8000000, 20e519a10bbe3d22, 99a96277480e51ac, cf3f23efeaf091ab, 15250af3534de67
//Second Loop 0 result= 2b5f03ec9137536d, 806e49a91514a16c, 31762d353b74a158, 13d4d397da065264, 0
//carry= 0
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x2b5f03ec9137536d,0x806e49a91514a16c,0x31762d353b74a158,0x13d4d397da065264};
////Fr_Rw_mul_test 1:
//FirstLoop 0 product= 2, 0, 0, 0, 0
//Second Loop 0 result= 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 2:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 3:
//FirstLoop 0 product= 2, ffffffffffffffff, ffffffffffffffff, ffffffffffffffff, fffffffffffffffd
//Second Loop 0 result= 169b0b13d72ddc98, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddd, 0
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x169b0b13d72ddc98,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddd};
////Fr_Rw_mul_test 4:
//FirstLoop 0 product= 2, fffffffffffffffd, 0, 0, 0
//Second Loop 0 result= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 5:
//FirstLoop 0 product= 0, 0, 0, 0, 0
//Second Loop 0 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 0 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 0 result= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};



// FirstLoop 1
//ASM:
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xb018ee96f0f23265,0xe256414c8486e83,0xc33c6675f156c527,0xec537c68c558e3c2};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x169b0b13d72ddc9a,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddd};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x169b0b13d72ddc98,0x6c5b3334dcbfb507,0xad619b286e68fccb,0x1949259d0e237ddf};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

// C:
////Fr_Rw_mul_test 0:
//FirstLoop 0 product= b018ee96f0f23265, e256414c8486e83, c33c6675f156c527, ec537c68c558e3c2, 13566df098c5aa6
//Second Loop 0 result= 2b5f03ec9137536d, 806e49a91514a16c, 31762d353b74a158, 13d4d397da065264, 0
//carry= 0
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xb018ee96f0f23265,0xe256414c8486e83,0xc33c6675f156c527,0xec537c68c558e3c2};
////Fr_Rw_mul_test 1:
//FirstLoop 0 product= 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddf, 0
//Second Loop 0 result= 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x169b0b13d72ddc99,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 2:
//FirstLoop 0 product= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//Second Loop 0 result= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x169b0b13d72ddc96,0x6c5b3334dcbfb50a,0xad619b286e68fcca,0x1949259d0e237ddf};
////Fr_Rw_mul_test 3:
//FirstLoop 0 product= 169b0b13d72ddc9a, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddd, fffffffffffffffd
//Second Loop 0 result= 169b0b13d72ddc98, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddd, 0
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x169b0b13d72ddc9a,0x6c5b3334dcbfb509,0xad619b286e68fcca,0x1949259d0e237ddd};
////Fr_Rw_mul_test 4:
//FirstLoop 0 product= 169b0b13d72ddc98, 6c5b3334dcbfb507, ad619b286e68fccb, 1949259d0e237ddf, 0
//Second Loop 0 result= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x169b0b13d72ddc98,0x6c5b3334dcbfb507,0xad619b286e68fccb,0x1949259d0e237ddf};
////Fr_Rw_mul_test 5:
//FirstLoop 0 product= 0, 0, 0, 0, 0
//Second Loop 0 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 0 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 0 result= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};


// ASM:
// Second Loop 1
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xb3571702bd2958e5,0x9a382a6c97774a46,0xd9a87dd3463f79dc,0x27beaa5f8eb19105};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x31dcea78edf3b8de,0xa95afc294653ce1e,0x562c6cde9eed09be,0x266201ae3fbe6af2};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x31e554a5232eedfa,0x9aec237e3810f6d9,0xae4226fd3a103abd,0x18a6707c1b21fe37};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x1b397538e18aa72a,0x4b6ea19f77d6f05a,0x50b517979560dbf3,0x1ad46d43563759cb};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x49e6a250a5cca8f,0xdf136e6a9b173b52,0xa3537c6f26f7df2a,0x18b47a64813dbed};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

////Fr_Rw_mul_test 0:
//FirstLoop 1 product= b018ee96f0f23265, e256414c8486e83, c33c6675f156c527, ec537c68c558e3c2, 13566df098c5aa6
//Second Loop 1 result= b3571702bd2958e5, 9a382a6c97774a46, d9a87dd3463f79dc, 27beaa5f8eb19105, 0
//carry= 0
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xb3571702bd2958e5,0x9a382a6c97774a46,0xd9a87dd3463f79dc,0x27beaa5f8eb19105};
////Fr_Rw_mul_test 1:
//FirstLoop 1 product= 169b0b13d72ddc99, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddf, 0
//Second Loop 1 result= 31dcea78edf3b8de, a95afc294653ce1e, 562c6cde9eed09be, 266201ae3fbe6af2, 0
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x31dcea78edf3b8de,0xa95afc294653ce1e,0x562c6cde9eed09be,0x266201ae3fbe6af2};
////Fr_Rw_mul_test 2:
//FirstLoop 1 product= 169b0b13d72ddc96, 6c5b3334dcbfb50a, ad619b286e68fcca, 1949259d0e237ddf, 0
//Second Loop 1 result= 31e554a5232eedfa, 9aec237e3810f6d9, ae4226fd3a103abd, 18a6707c1b21fe37, 0
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x31e554a5232eedfa,0x9aec237e3810f6d9,0xae4226fd3a103abd,0x18a6707c1b21fe37};
////Fr_Rw_mul_test 3:
//FirstLoop 1 product= 169b0b13d72ddc9a, 6c5b3334dcbfb509, ad619b286e68fcca, 1949259d0e237ddd, fffffffffffffffd
//Second Loop 1 result= 1b397538e18aa72a, 4b6ea19f77d6f05a, 50b517979560dbf3, 1ad46d43563759cb, 0
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x1b397538e18aa72a,0x4b6ea19f77d6f05a,0x50b517979560dbf3,0x1ad46d43563759cb};
////Fr_Rw_mul_test 4:
//FirstLoop 1 product= 169b0b13d72ddc98, 6c5b3334dcbfb507, ad619b286e68fccb, 1949259d0e237ddf, 0
//Second Loop 1 result= 49e6a250a5cca8f, df136e6a9b173b52, a3537c6f26f7df2a, 18b47a64813dbed, 0
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x49e6a250a5cca8f,0xdf136e6a9b173b52,0xa3537c6f26f7df2a,0x18b47a64813dbed};
////Fr_Rw_mul_test 5:
//FirstLoop 1 product= 0, 0, 0, 0, 0
//Second Loop 1 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 1 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 1 result= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};



// FirstLoop 2
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x165338df7a1740e7,0xfad820a0d2013a25,0x6775353caebf6da5,0xc82462fdff85b4c};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x31dcea78edf3b8de,0xa95afc294653ce1e,0x562c6cde9eed09be,0x266201ae3fbe6af2};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x31e554a5232eedfa,0x9aec237e3810f6d9,0xae4226fd3a103abd,0x18a6707c1b21fe37};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x1b397538e18aa72c,0x4b6ea19f77d6f05a,0x50b517979560dbf3,0x1ad46d43563759cb};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x49e6a250a5cca91,0xdf136e6a9b173b4f,0xa3537c6f26f7df2b,0x18b47a64813dbed};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};


////Fr_Rw_mul_test 0:
//FirstLoop 2 product= b3571702bd2958e5, 9a382a6c97774a46, d9a87dd3463f79dc, 27beaa5f8eb19105, 0
//Second Loop 2 result= b3571702bd2958e5, 9a382a6c97774a46, d9a87dd3463f79dc, 27beaa5f8eb19105, 0
//carry= 0
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xb3571702bd2958e5,0x9a382a6c97774a46,0xd9a87dd3463f79dc,0x27beaa5f8eb19105};
////Fr_Rw_mul_test 1:
//FirstLoop 2 product= 31dcea78edf3b8de, a95afc294653ce1e, 562c6cde9eed09be, 266201ae3fbe6af2, 0
//Second Loop 2 result= 31dcea78edf3b8de, a95afc294653ce1e, 562c6cde9eed09be, 266201ae3fbe6af2, 0
//carry= 0
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0x31dcea78edf3b8de,0xa95afc294653ce1e,0x562c6cde9eed09be,0x266201ae3fbe6af2};
////Fr_Rw_mul_test 2:
//FirstLoop 2 product= 31e554a5232eedfa, 9aec237e3810f6d9, ae4226fd3a103abd, 18a6707c1b21fe37, 0
//Second Loop 2 result= 31e554a5232eedfa, 9aec237e3810f6d9, ae4226fd3a103abd, 18a6707c1b21fe37, 0
//carry= 0
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x31e554a5232eedfa,0x9aec237e3810f6d9,0xae4226fd3a103abd,0x18a6707c1b21fe37};
////Fr_Rw_mul_test 3:
//FirstLoop 2 product= 1b397538e18aa72b, 4b6ea19f77d6f05a, 50b517979560dbf3, 1ad46d43563759cb, 0
//Second Loop 2 result= 1b397538e18aa72a, 4b6ea19f77d6f05a, 50b517979560dbf3, 1ad46d43563759cb, 0
//carry= 1
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0x1b397538e18aa72b,0x4b6ea19f77d6f05a,0x50b517979560dbf3,0x1ad46d43563759cb};
////Fr_Rw_mul_test 4:
//FirstLoop 2 product= 49e6a250a5cca8f, df136e6a9b173b52, a3537c6f26f7df2a, 18b47a64813dbed, 0
//Second Loop 2 result= 49e6a250a5cca8f, df136e6a9b173b52, a3537c6f26f7df2a, 18b47a64813dbed, 0
//carry= 0
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x49e6a250a5cca8f,0xdf136e6a9b173b52,0xa3537c6f26f7df2a,0x18b47a64813dbed};
////Fr_Rw_mul_test 5:
//FirstLoop 2 product= 0, 0, 0, 0, 0
//Second Loop 2 result= 0, 0, 0, 0, 0
//carry= 0
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FirstLoop 2 product= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//Second Loop 2 result= 43e1f593f0000001, 2833e84879b97091, b85045b68181585d, 30644e72e131a029, 0
//carry= 0
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

// secondLoop 2
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x781f41d8d29b0685,0x35d4f525e4933524,0x7123b1eae1aaed61,0x2c72835fecaffe88};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0xf3776a9834f97c9b,0xee0cbbabe96f11b7,0xa87997923fa2367a,0x25a806e1b2be78d1};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0xd5ea8b36b3a2d59b,0xba4bcf2cab2def57,0xda0fe4b3c933d270,0x10ebbe644acb676a};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0xdf1ef554932135a2,0x86e184acef9f3d3c,0xc8a123737c005fc5,0x21bddee2ff8f8bfe};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0xda88f55bbdffa02a,0x995f3d9746452aa9,0x7d636122f02bb19b,0x1277060a92df4358};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

// FirstLoop 3
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0x2fbbbc6c1774791,0x8cafd66d44fb23ca,0xb1cdb0effb41a060,0xa33fa913776fd198};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0xf3776a9834f97c9b,0xee0cbbabe96f11b7,0xa87997923fa2367a,0x25a806e1b2be78d1};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0xd5ea8b36b3a2d59b,0xba4bcf2cab2def57,0xda0fe4b3c933d270,0x10ebbe644acb676a};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0xdf1ef554932135a4,0x86e184acef9f3d3c,0xc8a123737c005fc5,0x21bddee2ff8f8bfe};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0xda88f55bbdffa02c,0x995f3d9746452aa6,0x7d636122f02bb19c,0x1277060a92df4358};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

// secondLoop 3
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0xd13604f1e300865c,0xba58b3d2a99f4ba5,0x1b4e415146d47f95,0x55c593ff9cfbf0a};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x1d0a8ff4c8e5744c,0x6fd9959908f97ec,0xdfe72d24fcdef34e,0xd1c7f8bb929dbb};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};


////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
////Fr_Rw_mul_test 0:
//FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
//FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
//FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
////Fr_Rw_mul_test 1:
//FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
////Fr_Rw_mul_test 2:
//FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
//FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
////Fr_Rw_mul_test 3:
//FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
//FrRawElement pRawResult3= {0xd13604f1e300865c,0xba58b3d2a99f4ba5,0x1b4e415146d47f95,0x55c593ff9cfbf0a};
////Fr_Rw_mul_test 4:
//FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
//FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
//FrRawElement pRawResult4= {0x1d0a8ff4c8e5744c,0x6fd9959908f97ec,0xdfe72d24fcdef34e,0xd1c7f8bb929dbb};
////Fr_Rw_mul_test 5:
//FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
//FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
//FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};
////Fr_Rw_mul_test 8:
//FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
//FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
//FrRawElement pRawResult8= {0x0,0x0,0x0,0x0};

void Fr_rawMMul(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t mz[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t product[Fr_N64 + 1] = {0, 0, 0, 0, 0};
    mp_limb_t result[Fr_N64 + 1]  = {0, 0, 0, 0, 0};
    mp_limb_t np0q[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t np0 = Fr_np;
    mp_limb_t carry = 0;
//    mp_limb_t md= 0;

//    mpz_init_set_ui(md, 1);
//    mpz_mul_2exp(md, md, 256);
//    md = 1;
//    mpn_lshift(&md, &md, 4, 256);

    // FirstLoop 0
    //mpz_mul_ui(product, b, pRawA[0]);
    mpn_mul(&product[0], &mb[0], 4, &ma[0], 1);

    // Second Loop 0
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 1, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
//      if(product[4] != 0)
//      {
//          carry = 1;
//          mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//          std::cout << "product[4] != 0" << "\n";
//      }
//      else
//      {
//          carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 4);
//          std::cout << "product[4] == 0" << "\n";
//      }
//          product[0] = product[1];
//          product[1] = product[2];
//          product[2] = product[3];
//          product[3] = product[4];
//          product[4] = 0;
      mpn_add(&result[0], &np0q[0], 5, &product[0], 5);

    if(product[4] != 0)
    {
        carry = 1;
        //std::cout << "product[4] != 0" << "\n";
    }
    else
    {
        carry = 0;
        //std::cout << "product[4] == 0" << "\n";
    }

//    mpz_tdiv_q_2exp(result, result, 64);
//      mpn_rshift(&result[0], &result[0], 5, 64);
//    //get_carry(result, fcarry);
////      if (mpn_size(val) <= 4)
////      {
////          mpz_set_ui(carry, 0);
////      }
////      else
////      {
////          mpz_set_ui(carry, 1);
////          mpz_mul_2exp(carry, carry, 64);
////      }
//      if (result[4] != 0)
//      {
//          carry = 1;
//          mpn_lshift(&carry, &carry, 4, 64);
//      }
//      else
//      {
//          carry = 0;
//      }
////    mpz_mod(result, result, md);
//      mpn_mod_1 (&result[0] , 5 , md);

    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
    std::cout << "carry= " << carry << "\n";

    //mpz_mul_ui(np0q, mq, np0);
     //if(result[4] != 0 )
     {
        result[0] = result[1];
        result[1] = result[2];
        result[2] = result[3];
        result[3] = result[4];
        result[4] = 0;
     }

//     //mpn_add(&result[0], &result[0], 4, &carry, 1);
     result[0] += carry;



     product[0] = 0;
     product[1] = 0;
     product[2] = 0;
     product[3] = 0;
     product[4] = 0;


     pRawResult[0] = result[0];
     pRawResult[1] = result[1];
     pRawResult[2] = result[2];
     pRawResult[3] = result[3];
    //mpz_add(result, np0q, product);


//    pRawResult[0] = result[0];
//    pRawResult[1] = result[1];
//    pRawResult[2] = result[2];
//    pRawResult[3] = result[3];

    // FirstLoop 1
    // mpz_mul_ui(product, b, pRawA[1]);
    mpn_mul(&product[0], &mb[0], 4, &ma[1], 1);
    //mpz_add(product, result, product);
    mpn_add(&product[0], &result[0], 4, &product[0], 4);
    //mpz_add(product, product, fcarry);
    mpn_add(&product[0], &product[0], 1, &carry, 1);
    //mpn_add(&product[0], &product[0], 1, &carry, 1);
//       mpz_tdiv_q_2exp(result, result, 64);
//       get_carry(result, fcarry);
//       mpz_mod(result, result, md);

//    //mpz_add(result, np0q, product);
//    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//    std::cout << "carry= " << carry << "\n";

//    pRawResult[0] = product[0];
//    pRawResult[1] = product[1];
//    pRawResult[2] = product[2];
//    pRawResult[3] = product[3];

    // Second Loop 1
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//    mpz_tdiv_q_2exp(result, result, 64);
//    get_carry(result, fcarry);
//    mpz_mod(result, result, md);
      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      //if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      result[0] += carry;



//      //mpz_add(result, np0q, product);
//      std::cout << "FirstLoop 1 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//      std::cout << "Second Loop 1 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//      std::cout << "carry= " << carry << "\n";

      product[0] = 0;
      product[1] = 0;
      product[2] = 0;
      product[3] = 0;
      product[4] = 0;


//      pRawResult[0] = result[0];
//      pRawResult[1] = result[1];
//      pRawResult[2] = result[2];
//      pRawResult[3] = result[3];

//    // FirstLoop 2
//    mpz_mul_ui(product, b, pRawA[2]);
      mpn_mul(&product[0], &mb[0], 4, &ma[2], 1);
//    mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//    mpz_add(product, product, fcarry);
      mpn_add(&product[0], &product[0], 4, &carry, 1);
      //product[0] +=carry;

//      //mpz_add(result, np0q, product);
//      std::cout << "FirstLoop 2 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//      std::cout << "Second Loop 2 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//      std::cout << "carry= " << carry << "\n";

//      pRawResult[0] = product[0];
//      pRawResult[1] = product[1];
//      pRawResult[2] = product[2];
//      pRawResult[3] = product[3];

//      // Second Loop 2
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      get_carry(result, fcarry);
//      mpz_mod(result, result, md);

      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      product[0] = 0;
      product[1] = 0;
      product[2] = 0;
      product[3] = 0;
      product[4] = 0;

//      // FirstLoop 3
//      mpz_mul_ui(product, b, pRawA[3]);
      mpn_mul(&product[0], &mb[0], 4, &ma[3], 1);
//      mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//      mpz_add(product, product, fcarry);
      mpn_add(&product[0], &product[0], 4, &carry, 1);

//      // Second Loop 3
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      mpz_mod(result, result, md);

      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      //if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }
      result[0] += carry;


      if (mpn_cmp(&result[0], &mq[0], 4) >= 0)
      {
          mpn_sub(&result[0], &result[0], 4, &mq[0], 4);
      }


//      pRawResult[0] = result[0];
//      pRawResult[1] = result[1];
//      pRawResult[2] = result[2];
//      pRawResult[3] = result[3];

/*
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t mz[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t product[Fr_N64 + 1] = {0, 0, 0, 0, 0};
    mp_limb_t result[Fr_N64 + 1]  = {0, 0, 0, 0, 0};
    mp_limb_t np0q[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t np0 = Fr_np;
    mp_limb_t carry = 0;
//    mp_limb_t md= 0;

//    mpz_init_set_ui(md, 1);
//    mpz_mul_2exp(md, md, 256);
//    md = 1;
//    mpn_lshift(&md, &md, 4, 256);

    // FirstLoop 0
    //mpz_mul_ui(product, b, pRawA[0]);
    mpn_mul(&product[0], &mb[0], 4, &ma[0], 1);

    // Second Loop 0
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 1, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
//      if(product[4] != 0)
//      {
//          carry = 1;
//          mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//          std::cout << "product[4] != 0" << "\n";
//      }
//      else
//      {
//          carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 4);
//          std::cout << "product[4] == 0" << "\n";
//      }
      mpn_add(&result[0], &np0q[0], 4, &product[0], 5);

    if(product[4] != 0)
    {
        carry = 1;
        //std::cout << "product[4] != 0" << "\n";
    }
    else
    {
        carry = 0;
        //std::cout << "product[4] == 0" << "\n";
    }

//    mpz_tdiv_q_2exp(result, result, 64);
//      mpn_rshift(&result[0], &result[0], 5, 64);
//    //get_carry(result, fcarry);
////      if (mpn_size(val) <= 4)
////      {
////          mpz_set_ui(carry, 0);
////      }
////      else
////      {
////          mpz_set_ui(carry, 1);
////          mpz_mul_2exp(carry, carry, 64);
////      }
//      if (result[4] != 0)
//      {
//          carry = 1;
//          mpn_lshift(&carry, &carry, 4, 64);
//      }
//      else
//      {
//          carry = 0;
//      }
////    mpz_mod(result, result, md);
//      mpn_mod_1 (&result[0] , 5 , md);



    //mpz_mul_ui(np0q, mq, np0);
     //if(result[4] != 0 )
     {
        result[0] = result[1];
        result[1] = result[2];
        result[2] = result[3];
        result[3] = result[4];
        result[4] = 0;
     }

     //mpn_add(&result[0], &result[0], 4, &carry, 1);
     result[0] += carry;

     product[0] = 0;
     product[1] = 0;
     product[2] = 0;
     product[3] = 0;
     product[4] = 0;


//     pRawResult[0] = result[0];
//     pRawResult[1] = result[1];
//     pRawResult[2] = result[2];
//     pRawResult[3] = result[3];
//    //mpz_add(result, np0q, product);
//    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//    std::cout << "carry= " << carry << "\n";

//    pRawResult[0] = result[0];
//    pRawResult[1] = result[1];
//    pRawResult[2] = result[2];
//    pRawResult[3] = result[3];

    // FirstLoop 1
    // mpz_mul_ui(product, b, pRawA[1]);
    mpn_mul(&product[0], &mb[0], 4, &ma[1], 1);
    //mpz_add(product, result, product);
    mpn_add(&product[0], &result[0], 4, &product[0], 4);
    //mpz_add(product, product, fcarry);
    mpn_add(&product[0], &product[0], 1, &carry, 1);
    //mpn_add(&product[0], &product[0], 1, &carry, 1);
//       mpz_tdiv_q_2exp(result, result, 64);
//       get_carry(result, fcarry);
//       mpz_mod(result, result, md);

//    //mpz_add(result, np0q, product);
//    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//    std::cout << "carry= " << carry << "\n";

//    pRawResult[0] = product[0];
//    pRawResult[1] = product[1];
//    pRawResult[2] = product[2];
//    pRawResult[3] = product[3];

    // Second Loop 1
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//    mpz_tdiv_q_2exp(result, result, 64);
//    get_carry(result, fcarry);
//    mpz_mod(result, result, md);
      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      //if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      result[0] += carry;



//      //mpz_add(result, np0q, product);
//      std::cout << "FirstLoop 1 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//      std::cout << "Second Loop 1 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//      std::cout << "carry= " << carry << "\n";

      product[0] = 0;
      product[1] = 0;
      product[2] = 0;
      product[3] = 0;
      product[4] = 0;


//      pRawResult[0] = result[0];
//      pRawResult[1] = result[1];
//      pRawResult[2] = result[2];
//      pRawResult[3] = result[3];

//    // FirstLoop 2
//    mpz_mul_ui(product, b, pRawA[2]);
      mpn_mul(&product[0], &mb[0], 4, &ma[2], 1);
//    mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//    mpz_add(product, product, fcarry);
      mpn_add(&product[0], &product[0], 4, &carry, 1);
      //product[0] +=carry;

//      //mpz_add(result, np0q, product);
//      std::cout << "FirstLoop 2 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//      std::cout << "Second Loop 2 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//      std::cout << "carry= " << carry << "\n";

//      pRawResult[0] = product[0];
//      pRawResult[1] = product[1];
//      pRawResult[2] = product[2];
//      pRawResult[3] = product[3];

//      // Second Loop 2
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      get_carry(result, fcarry);
//      mpz_mod(result, result, md);

      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      product[0] = 0;
      product[1] = 0;
      product[2] = 0;
      product[3] = 0;
      product[4] = 0;

//      // FirstLoop 3
//      mpz_mul_ui(product, b, pRawA[3]);
      mpn_mul(&product[0], &mb[0], 4, &ma[3], 1);
//      mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//      mpz_add(product, product, fcarry);
      mpn_add(&product[0], &product[0], 4, &carry, 1);

//      // Second Loop 3
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      mpz_mod(result, result, md);

      if(product[4] != 0)
      {
          carry = 1;
          //std::cout << "product[4] != 0" << "\n";
      }
      else
      {
          carry = 0;
          //std::cout << "product[4] == 0" << "\n";
      }

      //if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }
      result[0] += carry;


      if (mpn_cmp(&result[0], &mq[0], 4) >= 0)
      {
          mpn_sub(&result[0], &result[0], 4, &mq[0], 4);
      }


      pRawResult[0] = result[0];
      pRawResult[1] = result[1];
      pRawResult[2] = result[2];
      pRawResult[3] = result[3];
*/

/*
    mp_limb_t ma[Fr_N64] = {pRawA[0], pRawA[1], pRawA[2], pRawA[3]};
    mp_limb_t mb[Fr_N64] = {pRawB[0], pRawB[1], pRawB[2], pRawB[3]};
    mp_limb_t mq[Fr_N64] = {Fr_rawq[0], Fr_rawq[1], Fr_rawq[2], Fr_rawq[3]};
    mp_limb_t mr[Fr_N64] = {pRawResult[0], pRawResult[1], pRawResult[2], pRawResult[3]};
    mp_limb_t mz[Fr_N64] = {0, 0, 0, 0};
    mp_limb_t product[Fr_N64 + 1] = {0, 0, 0, 0, 0};
    mp_limb_t result[Fr_N64 + 1] = {0, 0, 0, 0, 0};
    mp_limb_t np0q[Fr_N64 + 1] = {0, 0, 0, 0, 0};
    mp_limb_t np0 = Fr_np;
    mp_limb_t carry = 0;

    // FirstLoop 0
    //mpz_mul_ui(product, b, pRawA[0]);
    mpn_mul(&product[0], &mb[0], 4, &ma[0], 1);

    // Second Loop 0
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 1, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
      carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//    mpz_tdiv_q_2exp(result, result, 64);
//    get_carry(result, fcarry);
//    mpz_mod(result, result, md);
    //mpz_mul_ui(np0q, mq, np0);
     if(result[4] != 0 )
     {
        result[0] = result[1];
        result[1] = result[2];
        result[2] = result[3];
        result[3] = result[4];
        result[4] = 0;
     }

    //mpz_add(result, np0q, product);
//    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//    std::cout << "carry= " << carry << "\n";

//    pRawResult[0] = result[0];
//    pRawResult[1] = result[1];
//    pRawResult[2] = result[2];
//    pRawResult[3] = result[3];

    // FirstLoop 1
    // mpz_mul_ui(product, b, pRawA[1]);
    mpn_mul(&product[0], &mb[0], 4, &ma[1], 1);
    //mpz_add(product, result, product);
    mpn_add(&product[0], &result[0], 4, &product[0], 4);
    //mpz_add(product, product, fcarry);
    product[1] +=carry;
    //mpn_add(&product[0], &product[0], 1, &carry, 1);

//    //mpz_add(result, np0q, product);
//    std::cout << "FirstLoop 0 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//    std::cout << "Second Loop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//    std::cout << "carry= " << carry << "\n";

//    pRawResult[0] = product[0];
//    pRawResult[1] = product[1];
//    pRawResult[2] = product[2];
//    pRawResult[3] = product[3];

    // Second Loop 1
//    np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//    mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//    mpz_add(result, np0q, product);
      carry = mpn_add(&result[0], &np0q[0], 4, &product[0], 5);
//    mpz_tdiv_q_2exp(result, result, 64);
//    get_carry(result, fcarry);
//    mpz_mod(result, result, md);
      if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      result[3] += carry;

//      //mpz_add(result, np0q, product);
//      std::cout << "FirstLoop 1 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
//      std::cout << "Second Loop 1 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
//      std::cout << "carry= " << carry << "\n";

//      pRawResult[0] = result[0];
//      pRawResult[1] = result[1];
//      pRawResult[2] = result[2];
//      pRawResult[3] = result[3];

//    // FirstLoop 2
//    mpz_mul_ui(product, b, pRawA[2]);
      mpn_mul(&product[0], &mb[0], 4, &ma[2], 1);
//    mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//    mpz_add(product, product, fcarry);
      //mpn_add(&product[0], &product[0], 4, &carry, 1);
      product[0] +=carry;

      //mpz_add(result, np0q, product);
      std::cout << "FirstLoop 2 product= " << std::hex << product[0] << ", " << product[1] << ", " << product[2] << ", " << product[3] << ", " << product[4] << "\n";
      std::cout << "Second Loop 2 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << ", " << result[4] << "\n";
      std::cout << "carry= " << carry << "\n";

      pRawResult[0] = product[0];
      pRawResult[1] = product[1];
      pRawResult[2] = product[2];
      pRawResult[3] = product[3];

//      // Second Loop 2
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      carry = mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      get_carry(result, fcarry);
//      mpz_mod(result, result, md);
      if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

//      // FirstLoop 3
//      mpz_mul_ui(product, b, pRawA[3]);
      mpn_mul(&product[0], &mb[0], 4, &ma[3], 1);
//      mpz_add(product, result, product);
      mpn_add(&product[0], &result[0], 4, &product[0], 4);
//      mpz_add(product, product, fcarry);
      mpn_add(&product[0], &product[0], 4, &carry, 1);

//      // Second Loop 3
//      np0 = Fr_np * mpz_getlimbn(product, 0);
      mpn_mul(&np0, &Fr_np, 4, &product[0], 1);
//      mpz_mul_ui(np0q, mq, np0);
      mpn_mul(&np0q[0], &mq[0], 4, &np0, 1);
//      mpz_add(result, np0q, product);
      carry = mpn_add(&result[0], &np0q[0], 5, &product[0], 5);
//      mpz_tdiv_q_2exp(result, result, 64);
//      mpz_mod(result, result, md);
      if (result[4] != 0)
      {
         result[0] = result[1];
         result[1] = result[2];
         result[2] = result[3];
         result[3] = result[4];
         result[4] = 0;
      }

      if (mpn_cmp(&result[0], &mq[0], 4) >= 0)
      {
          mpn_sub(&result[0], &result[0], 4, &mq[0], 4);
      }



      //std::cout << "FirstLoop 0 result= " << std::hex << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << "\n";
*/
    /*
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
*/
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

/*****************************************************************************************
 * ASM Functions to C/C++ using GNU MP Lib End
******************************************************************************************/

#endif
