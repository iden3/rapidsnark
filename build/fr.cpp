#include "fr.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <cctype>
#include <climits>

static bool initialized = false;

static bool Fr_init() {
    if (initialized) return false;
    initialized = true;
    return true;
}

struct U256 {
    uint64_t w[Fr_N64];
};

static inline U256 u256_zero() {
    U256 x{};
    for (int i = 0; i < Fr_N64; i++) x.w[i] = 0;
    return x;
}

static inline bool u256_is_zero(const U256 &a) {
    for (int i = 0; i < Fr_N64; i++) if (a.w[i] != 0) return false;
    return true;
}

static inline int u256_cmp(const U256 &a, const U256 &b) {
    for (int i = Fr_N64 - 1; i >= 0; i--) {
        if (a.w[i] < b.w[i]) return -1;
        if (a.w[i] > b.w[i]) return 1;
    }
    return 0;
}

static inline uint64_t u256_add_inplace(U256 &a, const U256 &b) {
    unsigned __int128 carry = 0;
    for (int i = 0; i < Fr_N64; i++) {
        unsigned __int128 s = (unsigned __int128)a.w[i] + b.w[i] + carry;
        a.w[i] = (uint64_t)s;
        carry = s >> 64;
    }
    return (uint64_t)carry;
}

static inline void u256_sub_inplace(U256 &a, const U256 &b) {
    unsigned __int128 borrow = 0;
    for (int i = 0; i < Fr_N64; i++) {
        unsigned __int128 ai = a.w[i];
        unsigned __int128 bi = (unsigned __int128)b.w[i] + borrow;
        if (ai >= bi) {
            a.w[i] = (uint64_t)(ai - bi);
            borrow = 0;
        } else {
            a.w[i] = (uint64_t)((((unsigned __int128)1 << 64) + ai) - bi);
            borrow = 1;
        }
    }
}

static inline U256 fr_modulus_u256() {
    U256 q{};
    for (int i = 0; i < Fr_N64; i++) q.w[i] = (uint64_t)Fr_q.longVal[i];
    return q;
}

static inline U256 u256_add_mod(const U256 &a, const U256 &b, const U256 &mod) {
    U256 r = a;
    uint64_t carry = u256_add_inplace(r, b);
    if (carry || u256_cmp(r, mod) >= 0) {
        u256_sub_inplace(r, mod);
    }
    return r;
}

static inline U256 u256_dbl_mod(const U256 &a, const U256 &mod) {
    return u256_add_mod(a, a, mod);
}

static inline U256 u256_add_small_mod(const U256 &a, uint32_t v, const U256 &mod) {
    U256 r = a;
    unsigned __int128 s = (unsigned __int128)r.w[0] + (unsigned __int128)v;
    r.w[0] = (uint64_t)s;
    uint64_t carry = (uint64_t)(s >> 64);
    for (int i = 1; i < Fr_N64 && carry; i++) {
        unsigned __int128 t = (unsigned __int128)r.w[i] + carry;
        r.w[i] = (uint64_t)t;
        carry = (uint64_t)(t >> 64);
    }
    if (carry || u256_cmp(r, mod) >= 0) {
        u256_sub_inplace(r, mod);
    }
    return r;
}

static inline U256 u256_mul_small_mod(U256 a, uint32_t m, const U256 &mod) {
    U256 res = u256_zero();
    U256 cur = a;
    while (m) {
        if (m & 1u) res = u256_add_mod(res, cur, mod);
        m >>= 1u;
        if (m) cur = u256_dbl_mod(cur, mod);
    }
    return res;
}

static inline void u256_to_le_bytes(uint8_t *out, size_t out_len, const U256 &a) {
    const size_t need = (size_t)Fr_N64 * 8;
    if (out_len < need) return;
    for (int i = 0; i < Fr_N64; i++) {
        uint64_t w = a.w[i];
        for (int j = 0; j < 8; j++) {
            out[i * 8 + j] = (uint8_t)(w & 0xFF);
            w >>= 8;
        }
    }
}

static inline U256 u256_from_be_bytes(const uint8_t *in, size_t in_len) {
    U256 a = u256_zero();
    const size_t need = (size_t)Fr_N64 * 8;
    if (in_len < need) return a;

    for (size_t i = 0; i < need; i++) {
        uint8_t byte = in[need - 1 - i];
        a.w[i / 8] |= (uint64_t)byte << (8 * (i % 8));
    }
    return a;
}

static inline bool u256_get_bit(const U256 &a, int bit) {
    int limb = bit / 64;
    int off  = bit % 64;
    if (limb < 0 || limb >= Fr_N64) return false;
    return (a.w[limb] >> off) & 1ULL;
}

static inline void u256_set_bit(U256 &a, int bit) {
    int limb = bit / 64;
    int off  = bit % 64;
    if (limb < 0 || limb >= Fr_N64) return;
    a.w[limb] |= (1ULL << off);
}

static inline void u256_shl1_addbit(U256 &a, uint64_t bit) {
    uint64_t carry = bit & 1ULL;
    for (int i = 0; i < Fr_N64; i++) {
        uint64_t new_carry = a.w[i] >> 63;
        a.w[i] = (a.w[i] << 1) | carry;
        carry = new_carry;
    }
}

static inline void u256_divmod(const U256 &num, const U256 &den, U256 &q, U256 &r) {
    if (u256_is_zero(den)) throw std::runtime_error("division by zero");

    q = u256_zero();
    r = u256_zero();

    const int NBITS = Fr_N64 * 64;
    for (int i = NBITS - 1; i >= 0; i--) {
        u256_shl1_addbit(r, u256_get_bit(num, i) ? 1 : 0);
        if (u256_cmp(r, den) >= 0) {
            u256_sub_inplace(r, den);
            u256_set_bit(q, i);
        }
    }
}

static inline U256 u256_from_u64(uint64_t x) {
    U256 a = u256_zero();
    a.w[0] = x;
    return a;
}

static inline bool u256_fits_sint(const U256 &a) {
    for (int i = 1; i < Fr_N64; i++) if (a.w[i] != 0) return false;
    return a.w[0] <= (uint64_t)INT_MAX;
}

static inline void element_set_from_u256(PFrElement pE, const U256 &v) {
    if (u256_fits_sint(v)) {
        pE->type = Fr_SHORT;
        pE->shortVal = (int32_t)v.w[0];
        return;
    }
    pE->type = Fr_LONG;
    for (int i = 0; i < Fr_N64; i++) pE->longVal[i] = v.w[i];
}

static inline U256 element_to_u256_positive(PFrElement pE) {
    const U256 mod = fr_modulus_u256();

    FrElement tmp;
    Fr_toNormal(&tmp, pE);
    if (!(tmp.type & Fr_LONG)) {
        int64_t sv = (int64_t)tmp.shortVal;
        if (sv >= 0) return u256_from_u64((uint64_t)sv);

        uint64_t absv = (uint64_t)(-sv);
        U256 a = u256_from_u64(absv);
        if (u256_is_zero(a)) return a;
        U256 r = mod;
        u256_sub_inplace(r, a);
        return r;
    }

    U256 v = u256_zero();
    for (int i = 0; i < Fr_N64; i++) v.w[i] = (uint64_t)tmp.longVal[i];
    return v;
}

static inline int digit_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

static U256 parse_mod_r(const char *s, uint32_t base) {
    if (base < 2 || base > 16) throw std::invalid_argument("unsupported base");

    while (*s && std::isspace((unsigned char)*s)) s++;

    bool neg = false;
    if (*s == '+') s++;
    else if (*s == '-') { neg = true; s++; }

    const U256 mod = fr_modulus_u256();
    U256 acc = u256_zero();

    for (; *s; s++) {
        if (std::isspace((unsigned char)*s)) break;
        int d = digit_val(*s);
        if (d < 0 || (uint32_t)d >= base) throw std::invalid_argument("invalid digit in number");
        acc = u256_mul_small_mod(acc, base, mod);
        acc = u256_add_small_mod(acc, (uint32_t)d, mod);
    }

    if (neg && !u256_is_zero(acc)) {
        U256 r = mod;
        u256_sub_inplace(r, acc);
        return r;
    }
    return acc;
}

static std::string u256_to_string(U256 v, uint32_t base) {
    if (base < 2 || base > 16) throw std::invalid_argument("unsupported base");
    if (u256_is_zero(v)) return "0";

    std::string out;
    while (!u256_is_zero(v)) {
        uint64_t rem = 0;
        U256 q = u256_zero();

        for (int i = Fr_N64 - 1; i >= 0; i--) {
            unsigned __int128 cur = ((unsigned __int128)rem << 64) | (unsigned __int128)v.w[i];
            uint64_t qword = (uint64_t)(cur / base);
            rem = (uint64_t)(cur % base);
            q.w[i] = qword;
        }

        const char digit = (rem < 10) ? char('0' + rem) : char('a' + (rem - 10));
        out.push_back(digit);
        v = q;
    }

    for (size_t i = 0, j = out.size() - 1; i < j; i++, j--) {
        char t = out[i]; out[i] = out[j]; out[j] = t;
    }
    return out;
}

static inline char* malloc_cstr(const std::string &s) {
    char *p = (char*)std::malloc(s.size() + 1);
    if (!p) return nullptr;
    std::memcpy(p, s.c_str(), s.size() + 1);
    return p;
}

void Fr_str2element(PFrElement pE, char const *s, uint base) {
    U256 v = parse_mod_r(s, base);
    element_set_from_u256(pE, v);
}

char *Fr_element2str(PFrElement pE) {
    U256 v = element_to_u256_positive(pE);
    std::string s = u256_to_string(v, 10);
    return malloc_cstr(s);
}

void Fr_idiv(PFrElement r, PFrElement a, PFrElement b) {
    U256 ma = element_to_u256_positive(a);
    U256 mb = element_to_u256_positive(b);

    U256 q, rem;
    u256_divmod(ma, mb, q, rem);
    element_set_from_u256(r, q);
}

void Fr_mod(PFrElement r, PFrElement a, PFrElement b) {
    U256 ma = element_to_u256_positive(a);
    U256 mb = element_to_u256_positive(b);

    U256 q, rem;
    u256_divmod(ma, mb, q, rem);
    element_set_from_u256(r, rem);
}

static inline void u256_to_raw(FrRawElement out, const U256 &a) {
    for (int i = 0; i < Fr_N64; i++) out[i] = a.w[i];
}

static inline U256 u256_from_raw(const FrRawElement in) {
    U256 a = u256_zero();
    for (int i = 0; i < Fr_N64; i++) a.w[i] = in[i];
    return a;
}

static inline void fr_pow_raw_mont(FrRawElement out_mont, const FrRawElement base_norm, const uint8_t *exp_le, unsigned exp_len) {
    FrRawElement base_mont;
    Fr_rawCopy(base_mont, base_norm);
    Fr_rawToMontgomery(base_mont, base_mont);

    RawFr::Element b{};
    RawFr::Element rr{};
    Fr_rawCopy(b.v, base_mont);

    RawFr::field.exp(rr, b, (uint8_t*)exp_le, exp_len);
    Fr_rawCopy(out_mont, rr.v);
}

static inline void fr_q_minus_2_le(uint8_t *out_le, size_t out_len) {
    const U256 mod = fr_modulus_u256();
    U256 e = mod;
    U256 two = u256_from_u64(2);
    u256_sub_inplace(e, two);
    u256_to_le_bytes(out_le, out_len, e);
}

void Fr_pow(PFrElement r, PFrElement a, PFrElement b) {
    const U256 ma = element_to_u256_positive(a);
    const U256 mb = element_to_u256_positive(b);

    uint8_t exp_le[Fr_N64 * 8];
    u256_to_le_bytes(exp_le, sizeof(exp_le), mb);

    FrRawElement base_norm;
    u256_to_raw(base_norm, ma);

    FrRawElement res_mont;
    fr_pow_raw_mont(res_mont, base_norm, exp_le, (unsigned)sizeof(exp_le));

    FrRawElement res_norm;
    Fr_rawFromMontgomery(res_norm, res_mont);

    U256 out = u256_from_raw(res_norm);
    element_set_from_u256(r, out);
}

void Fr_inv(PFrElement r, PFrElement a) {
    const U256 ma = element_to_u256_positive(a);

    uint8_t exp_le[Fr_N64 * 8];
    fr_q_minus_2_le(exp_le, sizeof(exp_le));

    FrRawElement base_norm;
    u256_to_raw(base_norm, ma);

    FrRawElement res_mont;
    fr_pow_raw_mont(res_mont, base_norm, exp_le, (unsigned)sizeof(exp_le));

    FrRawElement res_norm;
    Fr_rawFromMontgomery(res_norm, res_mont);

    U256 out = u256_from_raw(res_norm);
    element_set_from_u256(r, out);
}

void Fr_div(PFrElement r, PFrElement a, PFrElement b) {
    FrElement invb;
    Fr_inv(&invb, b);
    Fr_mul(r, a, &invb);
}

void Fr_fail() {
    throw std::runtime_error("Fr error");
}

void Fr_longErr() {
    Fr_fail();
}

RawFr::RawFr() {
    Fr_init();
    set(fZero, 0);
    set(fOne, 1);
    neg(fNegOne, fOne);
}

RawFr::~RawFr() {}

void RawFr::fromString(Element &r, const std::string &s, uint32_t radix) {
    U256 v = parse_mod_r(s.c_str(), radix);
    for (int i = 0; i < Fr_N64; i++) r.v[i] = v.w[i];
    Fr_rawToMontgomery(r.v, r.v);
}

void RawFr::fromUI(Element &r, unsigned long int v) {
    U256 x = u256_zero();
    x.w[0] = (uint64_t)v;
    for (int i = 0; i < Fr_N64; i++) r.v[i] = x.w[i];
    Fr_rawToMontgomery(r.v, r.v);
}

RawFr::Element RawFr::set(int value) {
    Element r;
    set(r, value);
    return r;
}

void RawFr::set(Element &r, int value) {
    const U256 mod = fr_modulus_u256();
    U256 v = u256_zero();

    if (value >= 0) {
        v.w[0] = (uint64_t)value;
    } else {
        uint64_t absv = (uint64_t)(-(int64_t)value);
        U256 a = u256_from_u64(absv);
        if (!u256_is_zero(a)) {
            v = mod;
            u256_sub_inplace(v, a);
        }
    }

    for (int i = 0; i < Fr_N64; i++) r.v[i] = v.w[i];
    Fr_rawToMontgomery(r.v, r.v);
}

std::string RawFr::toString(const Element &a, uint32_t radix) {
    Element tmp;
    Fr_rawFromMontgomery(tmp.v, a.v);

    U256 v = u256_zero();
    for (int i = 0; i < Fr_N64; i++) v.w[i] = tmp.v[i];

    return u256_to_string(v, radix);
}

void RawFr::inv(Element &r, const Element &a) {
    uint8_t exp_le[Fr_N64 * 8];
    fr_q_minus_2_le(exp_le, sizeof(exp_le));
    exp(r, a, exp_le, (unsigned)sizeof(exp_le));
}

void RawFr::div(Element &r, const Element &a, const Element &b) {
    Element tmp;
    inv(tmp, b);
    mul(r, a, tmp);
}

#define BIT_IS_SET(s, p) (s[(p)>>3] & (1 << ((p) & 0x7)))
void RawFr::exp(Element &r, const Element &base, uint8_t* scalar, unsigned int scalarSize) {
    bool oneFound = false;
    Element copyBase;
    copy(copyBase, base);
    for (int i = (int)scalarSize*8 - 1; i >= 0; i--) {
        if (!oneFound) {
            if (!BIT_IS_SET(scalar, i)) continue;
            copy(r, copyBase);
            oneFound = true;
            continue;
        }
        square(r, r);
        if (BIT_IS_SET(scalar, i)) {
            mul(r, r, copyBase);
        }
    }
    if (!oneFound) {
        copy(r, fOne);
    }
}

int RawFr::toRprBE(const Element &element, uint8_t *data, int bytes) {
    const int need = Fr_N64 * 8;
    if (bytes < need) return -need;

    Element tmp;
    Fr_rawFromMontgomery(tmp.v, element.v);

    std::memset(data, 0, (size_t)need);
    for (int i = 0; i < need; i++) {
        uint8_t byte = (uint8_t)((tmp.v[i / 8] >> (8 * (i % 8))) & 0xFF);
        data[need - 1 - i] = byte;
    }
    return need;
}

int RawFr::fromRprBE(Element &element, const uint8_t *data, int bytes) {
    const int need = Fr_N64 * 8;
    if (bytes < need) return -need;

    U256 v = u256_from_be_bytes(data, (size_t)need);
    for (int i = 0; i < Fr_N64; i++) element.v[i] = v.w[i];
    Fr_rawToMontgomery(element.v, element.v);
    return need;
}

static bool init = Fr_init();
RawFr RawFr::field;
