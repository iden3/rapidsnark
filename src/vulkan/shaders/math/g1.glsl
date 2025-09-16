#include "fq.glsl"

#define BaseFieldElement     Element
#define BaseFieldElementZero ElementZero
#define BaseFieldElementOne  ElementOne
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

bool isZero(CurvePoint a)
{
    return a.zz == ElementZero;
}

bool isZero(CurvePointAffine a)
{
    return a.x == ElementZero && a.y == ElementZero;
}

#include "math/curve.glsl"
