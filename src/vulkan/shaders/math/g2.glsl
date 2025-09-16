#include "math/fq.glsl"

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

#define AssignCurvePoint(dst, src) dst = src

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

#include "math/curve.glsl"
