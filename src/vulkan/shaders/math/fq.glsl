const int N = 8;

#define Element uint[N]

const Element ElementZero = {0,0,0,0, 0,0,0,0};
const Element ElementOne  = {0xc58f0d9d,0xd35d438d,0xf5c70b3d,0x0a78eb28,0x7879462c,0x666ea36f,0x9a07df2f,0x0e0a77c1};
const Element fq_q        = {0xd87cfd47,0x3c208c16,0x6871ca8d,0x97816a91,0x8181585d,0xb85045b6,0xe131a029,0x30644e72};
const uint    fq_np       = 0xe4866389;

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

void neg(out Element r, Element a)
{
    if (mp_cmp(a, ElementZero) != 0) {
        mp_sub(r, fq_q, a);

    } else {
        r = ElementZero;
    }
}

void mul(out Element r, Element a, Element b)
{
    r = ElementZero;

     for (int i = 0; i < N; i++) {
        uint carry1, carry2;
        uint hi, lo;

        umulExtended(a[0], b[i], hi, lo);

        r[0] = uaddCarry(r[0], lo, carry1);
        carry1 += hi;

        uint np0 = fq_np * r[0];

        umulExtended(fq_q[0], np0, hi, lo);

        uaddCarry(r[0], lo, carry2);
        carry2 += hi;

        for (uint j = 1; j < N; j++) {

            umulExtended(a[j], b[i], hi, lo);

            lo   = uaddCarry(lo, carry1, carry1);
            r[j] = uaddCarry(r[j], lo, lo);
            carry1 += hi + lo;

            umulExtended(fq_q[j], np0, hi, lo);

            lo     = uaddCarry(lo, carry2, carry2);
            r[j-1] = uaddCarry(r[j], lo, lo);
            carry2 += hi + lo;
        }

        r[N-1] = carry1 + carry2;
    }

    if (mp_cmp(r, fq_q) >= 0) {
        mp_sub(r, r, fq_q);
    }
}
