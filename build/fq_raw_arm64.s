    .global Fq_rawAdd
    .global Fq_rawSub
    .global Fq_rawNeg
    .global Fq_rawMMul
    .global Fq_rawMMul1
    .global Fq_rawFromMontgomery
    .global Fq_rawCopy
    .global Fq_rawSwap
    .global Fq_rawIsEq
    .global Fq_rawIsZero
    .global Fq_rawCopyS2L

    .text

// void Fq_rawAdd(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
Fq_rawAdd:
        ldp  x3, x4, [x1]
        ldp  x7, x8, [x2]
        adds x3, x3, x7
        adcs x4, x4, x8

        ldp  x5, x6,  [x1, 16]
        ldp  x9, x10, [x2, 16]
        adcs x5, x5, x9
        adcs x6, x6, x10

        cset x16, cs

        adr x11, Fq_rawq
        ldp x12, x13, [x11]
        ldp x14, x15, [x11, 16]

        subs x7,  x3, x12
        sbcs x8,  x4, x13
        sbcs x9,  x5, x14
        sbcs x10, x6, x15

        cbnz x16, Fq_rawAdd_done_s
        b.hs      Fq_rawAdd_done_s

        stp x3, x4, [x0]
        stp x5, x6, [x0, 16]
        ret

Fq_rawAdd_done_s:
        stp x7, x8,  [x0]
        stp x9, x10, [x0, 16]
        ret


// void Fq_rawSub(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
Fq_rawSub:
        ldp  x3, x4, [x1]
        ldp  x7, x8, [x2]
        subs x3, x3, x7
        sbcs x4, x4, x8

        ldp  x5, x6,  [x1, 16]
        ldp  x9, x10, [x2, 16]
        sbcs x5, x5, x9
        sbcs x6, x6, x10

        b.cs Fq_rawSub_done

        adr x11, Fq_rawq
        ldp x12, x13, [x11]
        ldp x14, x15, [x11, 16]

        adds x3, x3, x12
        adcs x4, x4, x13
        adcs x5, x5, x14
        adc  x6, x6, x15

Fq_rawSub_done:
        stp x3, x4, [x0]
        stp x5, x6, [x0, 16]
        ret


// void Fq_rawNeg(FqRawElement pRawResult, FqRawElement pRawA)
Fq_rawNeg:
        ldp x2, x3, [x1]
        orr x6, x2, x3

        ldp x4, x5, [x1, 16]
        orr x7, x4, x5
        orr x8, x6, x7

        cbz x8, Fq_rawNeg_done_zero

        adr x10, Fq_rawq
        ldp x11, x12, [x10]
        ldp x13, x14, [x10, 16]

        subs x2, x11, x2
        sbcs x3, x12, x3
        sbcs x4, x13, x4
        sbc  x5, x14, x5

        stp x2, x3, [x0]
        stp x4, x5, [x0, 16]
        ret

Fq_rawNeg_done_zero:
        stp xzr, xzr, [x0]
        stp xzr, xzr, [x0, 16]
        ret


// void Fq_rawMMul(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB)
Fq_rawMMul:
        ldr x3,     [x1]    //pRawA[0]
        ldp x5, x6, [x2]    //pRawB
        ldp x7, x8, [x2, 16]

        adr x4, Fq_np
        ldr x4, [x4]

        str x28, [sp, #-16]!

        adr x2, Fq_rawq
        ldp x15, x16, [x2]
        ldp x17, x28, [x2, 16]

        // product0 = pRawB * pRawA[0]
        mul   x10, x5, x3
        umulh x11, x5, x3
        mul   x2,  x6, x3
        adds  x11, x11, x2
        umulh x12, x6, x3
        mul   x2,  x7, x3
        adcs  x12, x12, x2
        umulh x13, x7, x3
        mul   x2,  x8, x3
        adcs  x13, x13, x2
        umulh x14, x8, x3
        adc   x14, x14, xzr

        // np0 = Fq_np * product0[0];
        mul   x9, x4, x10

        // product0 = product0 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x28, x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x28, x9
        adcs  x14, x14, x3
        adc   x9,  xzr, xzr

        // product1 = product0 + pRawB * pRawA[1]
        ldr x3, [x1, 8]    //pRawA[1]
        mul   x10, x5,  x3
        adds  x10, x10, x11
        mul   x11, x6,  x3
        adcs  x11, x11, x12
        mul   x12, x7,  x3
        adcs  x12, x12, x13
        mul   x13, x8,  x3
        adcs  x13, x13, x14
        adc   x14, xzr, xzr

        adds  x11, x11, x9
        umulh x2,  x5,  x3
        adcs  x11, x11, x2
        umulh x9,  x6,  x3
        adcs  x12, x12, x9
        umulh x2,  x7,  x3
        adcs  x13, x13, x2
        umulh x9,  x8,  x3
        adc   x14, x14, x9

        // np0 = Fq_np * product1[0];
        mul   x9, x4, x10

        // product1 = product1 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x28, x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x28, x9
        adcs  x14, x14, x3
        adc   x9,  xzr, xzr


        // product2 = product1 + pRawB * pRawA[2]
        ldr x3, [x1, 16]    //pRawA[2]
        mul   x10, x5,  x3
        adds  x10, x10, x11
        mul   x11, x6,  x3
        adcs  x11, x11, x12
        mul   x12, x7,  x3
        adcs  x12, x12, x13
        mul   x13, x8,  x3
        adcs  x13, x13, x14
        adc   x14, xzr, xzr

        adds  x11, x11, x9
        umulh x2,  x5,  x3
        adcs  x11, x11, x2
        umulh x9,  x6,  x3
        adcs  x12, x12, x9
        umulh x2,  x7,  x3
        adcs  x13, x13, x2
        umulh x9,  x8,  x3
        adc   x14, x14, x9

        // np0 = Fq_np * product2[0];
        mul   x9, x4, x10

        // product2 = product2 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x28, x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x28, x9
        adcs  x14, x14, x3
        adc   x9,  xzr, xzr

        // product3 = product2 + pRawB * pRawA[3]
        ldr x3, [x1, 24]    //pRawA[3]
        mul   x10, x5,  x3
        adds  x10, x10, x11
        mul   x11, x6,  x3
        adcs  x11, x11, x12
        mul   x12, x7,  x3
        adcs  x12, x12, x13
        mul   x13, x8,  x3
        adcs  x13, x13, x14
        adc   x14, xzr, xzr

        adds  x11, x11, x9
        umulh x2,  x5,  x3
        adcs  x11, x11, x2
        umulh x9,  x6,  x3
        adcs  x12, x12, x9
        umulh x2,  x7,  x3
        adcs  x13, x13, x2
        umulh x9,  x8,  x3
        adc   x14, x14, x9

        // np0 = Fq_np * product3[0];
        mul   x9, x4, x10

        // product3 = product3 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x28, x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x28, x9
        adcs  x14, x14, x3

        // result >= Fq_rawq
        subs x5, x11, x15
        sbcs x6, x12, x16
        sbcs x7, x13, x17
        sbcs x8, x14, x28

        ldr x28, [sp], #16

        b.hs Fq_rawMul_done_s

        stp x11, x12, [x0]
        stp x13, x14, [x0, 16]
        ret

Fq_rawMul_done_s:
        stp x5, x6, [x0]
        stp x7, x8, [x0, 16]
        ret


// void Fq_rawMMul1(FqRawElement pRawResult, FqRawElement pRawA, uint64_t pRawB)
Fq_rawMMul1:
        ldp x5, x6, [x1]    //pRawA
        ldp x7, x8, [x1, 16]

        adr x4, Fq_np
        ldr x4, [x4]

        // product0 = pRawA * pRawB
        mul   x10, x5, x2
        umulh x11, x5, x2
        mul   x3,  x6, x2
        adds  x11, x11, x3
        umulh x12, x6, x2
        mul   x3,  x7, x2
        adcs  x12, x12, x3
        umulh x13, x7, x2
        mul   x3,  x8, x2
        adcs  x13, x13, x3
        umulh x14, x8, x2
        adc   x14, x14, xzr

        adr x3, Fq_rawq
        ldp x15, x16, [x3]
        ldp x17, x8,  [x3, 16]

        // np0 = Fq_np * product0[0];
        mul   x9, x4, x10

        // product0 = product0 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x8,  x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product1[0];
        mul   x9, x4, x11

        // product1 = product1 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8,  x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds x11,  x11, x7
        umulh x2,  x15, x9
        adcs  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product2[0];
        mul   x9, x4, x11

        // product2 = product2 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8,  x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds  x11, x11, x7
        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product3[0];
        mul   x9, x4, x11

        // product3 = product3 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8,  x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds  x11, x11, x7
        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3

        // result >= Fq_rawq
        subs x5, x11, x15
        sbcs x6, x12, x16
        sbcs x7, x13, x17
        sbcs x8, x14, x8

        b.hs Fq_rawMul1_done_s

        stp x11, x12, [x0]
        stp x13, x14, [x0, 16]
        ret

        Fq_rawMul1_done_s:
        stp x5, x6, [x0]
        stp x7, x8, [x0, 16]
        ret


// void Fq_rawFromMontgomery(FqRawElement pRawResult, FqRawElement pRawA)
Fq_rawFromMontgomery:
        ldp x10, x11, [x1]    //pRawA
        ldp x12, x13, [x1, 16]
        mov x14, xzr

        adr x4, Fq_np
        ldr x4, [x4]

        adr x3, Fq_rawq
        ldp x15, x16, [x3]
        ldp x17, x8,  [x3, 16]

        // np0 = Fq_np * product0[0];
        mul   x9, x4, x10

        // product0 = product0 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x10, x2
        mul   x3,  x16, x9
        adcs  x11, x11, x3
        mul   x2,  x17, x9
        adcs  x12, x12, x2
        mul   x3,  x8,  x9
        adcs  x13, x13, x3
        adc   x14, x14, xzr

        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product1[0];
        mul   x9, x4, x11

        // product1 = product1 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8 , x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds x11,  x11, x7
        umulh x2,  x15, x9
        adcs  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8 , x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product2[0];
        mul   x9, x4, x11

        // product2 = product2 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8,  x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds  x11, x11, x7
        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3
        adc   x7,  xzr, xzr

        // np0 = Fq_np * product3[0];
        mul   x9, x4, x11

        // product3 = product3 + Fq_rawq * np0
        mul   x2,  x15, x9
        adds  x10, x11, x2
        mul   x3,  x16, x9
        adcs  x11, x12, x3
        mul   x2,  x17, x9
        adcs  x12, x13, x2
        mul   x3,  x8,  x9
        adcs  x13, x14, x3
        adc   x14, xzr, xzr

        adds  x11, x11, x7
        umulh x2,  x15, x9
        adds  x11, x11, x2
        umulh x3,  x16, x9
        adcs  x12, x12, x3
        umulh x2,  x17, x9
        adcs  x13, x13, x2
        umulh x3,  x8,  x9
        adcs  x14, x14, x3

        // result >= Fq_rawq
        subs x5, x11, x15
        sbcs x6, x12, x16
        sbcs x7, x13, x17
        sbcs x8, x14, x8

        b.hs Fq_rawFromMontgomery_s

        stp x11, x12, [x0]
        stp x13, x14, [x0, 16]
        ret

Fq_rawFromMontgomery_s:
        stp x5, x6, [x0]
        stp x7, x8, [x0, 16]
        ret



// void Fq_rawCopy(FqRawElement pRawResult, FqRawElement pRawA)
Fq_rawCopy:
        ldp x2, x3, [x1]
        stp x2, x3, [x0]

        ldp x4, x5, [x1, 16]
        stp x4, x5, [x0, 16]
        ret


// void Fq_rawSwap(FqRawElement pRawResult, FqRawElement pRawA)
Fq_rawSwap:
        ldp  x3, x4, [x0]
        ldp  x7, x8, [x1]

        stp  x3, x4, [x1]
        stp  x7, x8, [x0]

        ldp  x5, x6,  [x0, 16]
        ldp  x9, x10, [x1, 16]

        stp  x5, x6,  [x1, 16]
        stp  x9, x10, [x0, 16]
        ret


// int Fq_rawIsEq(FqRawElement pRawA, FqRawElement pRawB)
Fq_rawIsEq:
        ldp  x3, x4, [x0]
        ldp  x7, x8, [x1]
        eor x11, x3, x7
        eor x12, x4, x8

        ldp  x5, x6,  [x0, 16]
        ldp  x9, x10, [x1, 16]
        eor x13, x5, x9
        eor x14, x6, x10

        orr x15, x11, x12
        orr x16, x13, x14

        orr x0, x15, x16
        cmp  x0, xzr
        cset x0, eq
        ret


// int Fq_rawIsZero(FqRawElement rawA)
Fq_rawIsZero:
        ldp x1, x2, [x0]
        orr x5, x1, x2

        ldp x3, x4, [x0, 16]
        orr x6, x3, x4

        orr  x0, x5, x6
        cmp  x0, xzr
        cset x0, eq
        ret


// void Fq_rawCopyS2L(FqRawElement pRawResult, int64_t val)
Fq_rawCopyS2L:
        cmp  x1, xzr
        b.lt Fq_rawCopyS2L_adjust_neg

        stp x1,  xzr, [x0]
        stp xzr, xzr, [x0, 16]
        ret

Fq_rawCopyS2L_adjust_neg:
        adr x3, Fq_rawq
        ldp x5, x6, [x3]
        ldp x7, x8, [x3, 16]

        mov x9, -1

        adds x1, x1, x5
        adcs x2, x9, x6
        adcs x3, x9, x7
        adc  x4, x9, x8

        stp x1, x2, [x0]
        stp x3, x4, [x0, 16]
        ret

Fq_rawq:    .quad 0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029
Fq_np:      .quad 0x87d20782e4866389
