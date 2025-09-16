void copy(out CurvePoint r, CurvePointAffine a)
{
    if (isZero(a)) {
        r.x   = BaseFieldElementOne;
        r.y   = BaseFieldElementOne;
        r.zz  = BaseFieldElementZero;
        r.zzz = BaseFieldElementZero;
    } else {
        r.x   = a.x;
        r.y   = a.y;
        r.zz  = BaseFieldElementOne;
        r.zzz = BaseFieldElementOne;
    }
}

void add(out CurvePoint p3, CurvePoint p1, CurvePointAffine p2)
{
    if (isZero(p1)) {
        copy(p3, p2);
        return;
    }

    if (isZero(p2)) {
        p3 = p1;
        return;
    }

    BaseFieldElement T1;
    BaseFieldElement P;
    BaseFieldElement R;

    mul(P, p2.x, p1.zz);
    mul(R, p2.y, p1.zzz);
    sub(P, P, p1.x);
    sub(R, R, p1.y);

    if (isZero(P) && isZero(R)) {
        add(T1, p2.y, p2.y);
        mul(p3.zz, T1, T1);
        mul(p3.zzz, T1, p3.zz);
        mul(P, p2.x, p3.zz);
        mul(R, p2.x, p2.x);
        add(T1, R, R);
        add(R, T1, R);
        add(R, R, fa);
        mul(p3.x, R, R);
        sub(p3.x, p3.x, P);
        sub(p3.x, p3.x, P);
        mul(T1, p3.zzz, p2.y);
        sub(p3.y, P, p3.x);
        mul(p3.y, R, p3.y);
        sub(p3.y, p3.y, T1);

    } else {
        mul(T1, P, P);
        mul(p3.zz, p1.zz, T1);
        mul(P, P, T1);
        mul(T1, p1.x, T1);
        mul(p3.x, R, R);
        sub(p3.x, p3.x, P);
        sub(p3.x, p3.x, T1);
        sub(p3.x, p3.x, T1);
        sub(p3.y, T1, p3.x);
        mul(T1, p1.y, P);
        mul(p3.y, p3.y, R );
        sub(p3.y, p3.y, T1);
        mul(p3.zzz, p1.zzz, P);
    }
}

void add(out CurvePoint p3, CurvePoint p1, CurvePoint p2)
{
    if (isZero(p1)) {
        p3 = p2;
        return;
    }

    if (isZero(p2)) {
        p3 = p1;
        return;
    }

    BaseFieldElement T1;
    BaseFieldElement U1;
    BaseFieldElement S1;
    BaseFieldElement P;
    BaseFieldElement R;

    mul(U1, p1.x, p2.zz);
    mul(P, p2.x, p1.zz);
    sub(P, P, U1);
    mul(S1, p1.y, p2.zzz);
    mul(R, p2.y, p1.zzz);
    sub(R, R, S1);

    if (isZero(P) && isZero(R)) {
        add(U1, p1.y, p1.y);
        mul(R, U1, U1);
        mul(P, U1, R);
        mul(S1, p1.x, R);
        mul(p3.zz, R, p1.zz);
        mul(p3.zzz, P, p1.zzz);
        mul(R, p1.x, p1.x);
        add(U1, R, R);
        add(R, R, U1);
        mul(p3.x, R, R);
        sub(p3.x, p3.x, S1);
        sub(p3.x, p3.x, S1);
        mul(U1, P, p1.y);
        sub(p3.y, S1, p3.x);
        mul(p3.y, R, p3.y);
        sub(p3.y, p3.y, U1);

    } else {
        mul(T1, P, P);
        mul(p3.zz, p1.zz, p2.zz);
        mul(p3.zz, p3.zz, T1);
        mul(P, P, T1);
        mul(T1, U1, T1);
        mul(p3.x, R, R);
        sub(p3.x, p3.x, P);
        sub(p3.x, p3.x, T1);
        sub(p3.x, p3.x, T1);
        mul(U1, S1, P);
        sub(p3.y, T1, p3.x);
        mul(p3.y, p3.y, R);
        sub(p3.y, p3.y, U1);
        mul(p3.zzz, p1.zzz, p2.zzz);
        mul(p3.zzz, p3.zzz, P);
    }
}
