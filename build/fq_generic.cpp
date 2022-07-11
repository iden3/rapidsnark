#include "fq.hpp"
#include <cstring>

FqElement Fq_q  = {0, 0x80000000, {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029}};
FqElement Fq_R3 = {0, 0x80000000, {0xb1cd6dafda1530df,0x62f210e6a7283db6,0xef7f0b0c0ada0afb,0x20fd6e902d592544}};


void Fq_copy(PFqElement r, PFqElement a)
{
    *r = *a;
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

static inline int has_mul32_overflow(int64_t val)
{
    int64_t sign = val >> 31;

    if (sign)
    {
        sign = ~sign;
    }

    return sign ? 1 : 0;
}

static inline int Fq_rawSMul(int64_t *r, int32_t a, int32_t b)
{
    *r = (int64_t)a * b;

    return has_mul32_overflow(*r);
}


static inline void mul_s1s2(PFqElement r, PFqElement a, PFqElement b)
{
    int64_t result;

    int overflow = Fq_rawSMul(&result, a->shortVal, b->shortVal);

    if (overflow)
    {
        r->type = Fq_LONG;
        r->shortVal = 0;
        Fq_rawCopyS2L(r->longVal, result);
    }
    else
    {
        // done the same way as in intel asm implementation
        r->shortVal = (int32_t)result;
        r->type = Fq_SHORT;
        //

        r->type = Fq_LONG;
        r->shortVal = 0;
        Fq_rawCopyS2L(r->longVal, result);
    }
}

static inline void mul_l1nl2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;

    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
    Fq_rawMMul(r->longVal, r->longVal, Fq_R3.longVal);
}

static inline void mul_l1nl2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ml2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ml2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ns2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;

    if (b->shortVal < 0)
    {
        Fq_rawMMul1(r->longVal, a->longVal, -b->shortVal);
        Fq_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fq_rawMMul1(r->longVal, a->longVal, b->shortVal);
    }

    Fq_rawMMul(r->longVal, r->longVal, Fq_R3.longVal);
}

static inline void mul_s1nl2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;

    if (a->shortVal < 0)
    {
        Fq_rawMMul1(r->longVal, b->longVal, -a->shortVal);
        Fq_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fq_rawMMul1(r->longVal, b->longVal, a->shortVal);
    }

    Fq_rawMMul(r->longVal, r->longVal, Fq_R3.longVal);
}

static inline void mul_l1ms2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;

    if (b->shortVal < 0)
    {
        Fq_rawMMul1(r->longVal, a->longVal, -b->shortVal);
        Fq_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fq_rawMMul1(r->longVal, a->longVal, b->shortVal);
    }
}

static inline void mul_s1nl2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;

    if (a->shortVal < 0)
    {
        Fq_rawMMul1(r->longVal, b->longVal, -a->shortVal);
        Fq_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fq_rawMMul1(r->longVal, b->longVal, a->shortVal);
    }
}

static inline void mul_l1ns2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ms2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_s1ml2m(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONGMONTGOMERY;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_s1ml2n(PFqElement r, PFqElement a, PFqElement b)
{
    r->type = Fq_LONG;
    Fq_rawMMul(r->longVal, a->longVal, b->longVal);
}

void Fq_mul(PFqElement r, PFqElement a, PFqElement b)
{
    if (a->type & Fq_LONG)
    {
        if (b->type & Fq_LONG)
        {
            if (a->type & Fq_MONTGOMERY)
            {
                if (b->type & Fq_MONTGOMERY)
                {
                    mul_l1ml2m(r, a, b);
                }
                else
                {
                    mul_l1ml2n(r, a, b);
                }
            }
            else
            {
                if (b->type & Fq_MONTGOMERY)
                {
                    mul_l1nl2m(r, a, b);
                }
                else
                {
                    mul_l1nl2n(r, a, b);
                }
            }
        }
        else if (a->type & Fq_MONTGOMERY)
        {
            if (b->type & Fq_MONTGOMERY)
            {
                mul_l1ms2m(r, a, b);
            }
            else
            {
                mul_l1ms2n(r, a, b);
            }
        }
        else
        {
            if (b->type & Fq_MONTGOMERY)
            {
                mul_l1ns2m(r, a, b);
            }
            else
            {
                mul_l1ns2n(r, a, b);
            }
        }
    }
    else if (b->type & Fq_LONG)
    {
        if (a->type & Fq_MONTGOMERY)
        {
            if (b->type & Fq_MONTGOMERY)
            {
                mul_s1ml2m(r, a, b);
            }
            else
            {
                mul_s1ml2n(r,a, b);
            }
        }
        else if (b->type & Fq_MONTGOMERY)
        {
            mul_s1nl2m(r, a, b);
        }
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
