#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <limits.h>

#define TEST_FR_C_FUNCTIONS
//#define TEST_FR_C_FUNCTIONS_WITH_RESULT
//#define TEST_FR_ASM_FUNCTIONS

//#define TEST_FQ_C_FUNCTIONS
//#define TEST_FQ_ASM_FUNCTIONS

#ifdef TEST_FR_C_FUNCTIONS`
#include "fr.hpp"
#endif

#ifdef TEST_FR_ASM_FUNCTIONS
#include "fr.hpp"
#endif

#ifdef TEST_FQ_C_FUNCTIONS
#include "fq.hpp"
#endif

#ifdef TEST_FQ_ASM_FUNCTIONS
#include "fq.hpp"
#endif
#include <assert.h>
using namespace std;

//#define Fr_N64 4
//typedef uint64_t FrRawElement[Fr_N64];

#ifdef TEST_C_FUNCTIONS
//void Fr_fail() {
//    assert(false);
//}
#endif


#if defined(TEST_FR_C_FUNCTIONS) || defined(TEST_FR_ASM_FUNCTIONS)
uint64_t uRawResult = 0;
uint64_t uRawResult1 = 0;
uint64_t uRawResult2 = 0;
uint64_t uRawResult3 = 0;
uint64_t uRawResult4 = 0;
uint64_t uRawResult5 = 0;
uint64_t uRawResult6 = 0;
uint64_t uRawResult7 = 0;
uint64_t uRawResult8 = 0;
uint64_t uRawResult9 = 0;


FrRawElement pRawResult = {0,0,0,0};
FrRawElement pRawA = {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
FrRawElement pRawB = {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5};

FrRawElement pRawResult1 = {0,0,0,0};
FrRawElement pRawA1      = {0x1,0,0,0};
FrRawElement pRawB1      = {0x2,0,0,0};

FrRawElement pRawResult2 = {0,0,0,0};
FrRawElement pRawA2      = {0xfffffffffffffffe,0,0,0};
FrRawElement pRawB2      = {0xffffffffffffffff,0,0,0};

FrRawElement pRawResult3 = {0,0,0,0};
FrRawElement pRawA3      = {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
FrRawElement pRawB3      = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};

FrRawElement pRawResult4 = {0,0,0,0};
FrRawElement pRawA4      = {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
FrRawElement pRawB4      = {0xffffffffffffffff,0,0,0};

FrRawElement pRawResult5 = {0,0,0,0};
FrRawElement pRawA5      = {0x0,0,0,0};
FrRawElement pRawB5      = {0x2,0,0,0};

FrRawElement pRawResult6 = {0,0,0,0};
FrRawElement pRawA6      = {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
FrRawElement pRawB6      = {0x0,0,0,0};

FrRawElement pRawResult7 = {0,0,0,0};
FrRawElement pRawA7      = {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
FrRawElement pRawB7      = {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

FrRawElement pRawResult8 = {0,0,0,0};
FrRawElement pRawA8      = {0x1,0,0,0};
FrRawElement pRawB8      = {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};

FrRawElement pRawResult9 = {0,0,0,0};
FrRawElement pRawA9      = {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
FrRawElement pRawB9      = {1,0,0,0};


//#define Fr_SHORT 0x00000000
//#define Fr_SHORTMONTGOMERY 0x40000000
//#define Fr_LONG 0x80000000
//#define Fr_LONGMONTGOMERY 0xC0000000

FrElement RawResult = {0,0,{0,0,0,0}};
FrElement RawA = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement RawB = {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement RawResult1 = {0,0,{0,0,0,0}};
FrElement RawA1 = {0xa1f0, Fr_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement RawB1 = {0x1bb8, Fr_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement RawResult2 = {0,0,{0,0,0,0}};
FrElement RawA2 = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement RawB2 = {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement RawResult3 = {0,0,{0,0,0,0}};
FrElement RawA3 = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement RawB3 = {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};



// mul_s1s2
// sub_s1s2 1
FrElement Result_s1s2 = {0,0,{0,0,0,0}};
FrElement A_s1s2 = {0x1, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B_s1s2 = {0x2, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result1_s1s2 = {0,0,{0,0,0,0}};
FrElement A1_s1s2 = {0x0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B1_s1s2 = {0x2, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result2_s1s2 = {0,0,{0,0,0,0}};
FrElement A2_s1s2 = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1s2 = {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1s2 = {0,0,{0,0,0,0}};
FrElement A3_s1s2 = {INT_MAX, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B3_s1s2 = {INT_MAX, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

// mul_l1nl2n
// sub_l1nl2n 2
FrElement Result_l1nl2n = {0,0,{0,0,0,0}};
FrElement A_l1nl2n = {0x1, Fr_LONG,{0x01,0,0,0}};
FrElement B_l1nl2n = {0x2, Fr_LONG,{0x02,0,0,0}};

FrElement Result1_l1nl2n = {0,0,{0,0,0,0}};
FrElement A1_l1nl2n = {0x0, Fr_LONG,{0x0,0,0,0}};
FrElement B1_l1nl2n = {0x2, Fr_LONG,{0x2,0,0,0}};

FrElement Result2_l1nl2n = {0,0,{0,0,0,0}};
FrElement A2_l1nl2n = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1nl2n= {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1nl2n = {0,0,{0,0,0,0}};
FrElement A3_l1nl2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1nl2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ml2n
// sub_l1ml2n 3
FrElement Result_l1ml2n = {0,0,{0,0,0,0}};
FrElement A_l1ml2n = {0x1, Fr_LONGMONTGOMERY,{0x01,0,0,0}};
FrElement B_l1ml2n = {0x2, Fr_LONG,{0x02,0,0,0}};

FrElement Result1_l1ml2n = {0,0,{0,0,0,0}};
FrElement A1_l1ml2n = {0x0, Fr_LONGMONTGOMERY,{0x0,0,0,0}};
FrElement B1_l1ml2n = {0x2, Fr_LONG,{0x2,0,0,0}};

FrElement Result2_l1ml2n = {0,0,{0,0,0,0}};
FrElement A2_l1ml2n = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ml2n= {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ml2n = {0,0,{0,0,0,0}};
FrElement A3_l1ml2n = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ml2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1nl2m
// sub_l1nl2m 4
FrElement Result_l1nl2m = {0,0,{0,0,0,0}};
FrElement A_l1nl2m = {0x1, Fr_LONG,{0x01,0,0,0}};
FrElement B_l1nl2m = {0x2, Fr_LONGMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_l1nl2m = {0,0,{0,0,0,0}};
FrElement A1_l1nl2m = {0x0, Fr_LONG,{0x0,0,0,0}};
FrElement B1_l1nl2m = {0x2, Fr_LONGMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_l1nl2m = {0,0,{0,0,0,0}};
FrElement A2_l1nl2m = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1nl2m= {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1nl2m = {0,0,{0,0,0,0}};
FrElement A3_l1nl2m = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1nl2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ml2m
// sub_l1ml2m 5
FrElement Result_l1ml2m = {0,0,{0,0,0,0}};
FrElement A_l1ml2m = {0x1, Fr_LONGMONTGOMERY,{0x01,0,0,0}};
FrElement B_l1ml2m = {0x2, Fr_LONGMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_l1ml2m = {0,0,{0,0,0,0}};
FrElement A1_l1ml2m = {0x0, Fr_LONGMONTGOMERY,{0x0,0,0,0}};
FrElement B1_l1ml2m = {0x2, Fr_LONGMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_l1ml2m = {0,0,{0,0,0,0}};
FrElement A2_l1ml2m = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ml2m= {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ml2m = {0,0,{0,0,0,0}};
FrElement A3_l1ml2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ml2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ns2n
FrElement Result_l1ns2n = {0,0,{0,0,0,0}};
FrElement A_l1ns2n = {0x1, Fr_LONG,{0x01,0,0,0}};
FrElement B_l1ns2n = {0x2, Fr_SHORT,{0x02,0,0,0}};

FrElement Result1_l1ns2n = {0,0,{0,0,0,0}};
FrElement A1_l1ns2n = {0x0, Fr_LONG,{0x0,0,0,0}};
FrElement B1_l1ns2n = {0x2, Fr_SHORT,{0x2,0,0,0}};

FrElement Result2_l1ns2n = {0,0,{0,0,0,0}};
FrElement A2_l1ns2n = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ns2n= {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ns2n = {0,0,{0,0,0,0}};
FrElement A3_l1ns2n = {INT_MAX, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ns2n = {-1, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1nl2n
FrElement Result_s1nl2n = {0,0,{0,0,0,0}};
FrElement A_s1nl2n = {0x1, Fr_SHORT,{0x01,0,0,0}};
FrElement B_s1nl2n = {0x2, Fr_LONG,{0x02,0,0,0}};

FrElement Result1_s1nl2n = {0,0,{0,0,0,0}};
FrElement A1_s1nl2n = {0x0, Fr_SHORT,{0x0,0,0,0}};
FrElement B1_s1nl2n = {0x2, Fr_LONG,{0x2,0,0,0}};

FrElement Result2_s1nl2n = {0,0,{0,0,0,0}};
FrElement A2_s1nl2n = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1nl2n= {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1nl2n = {0,0,{0,0,0,0}};
FrElement A3_s1nl2n= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1nl2n= {INT_MAX,Fr_LONG,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};

//mul_s1nl2m
//sub_s1nl2m 6
FrElement Result_s1nl2m = {0,0,{0,0,0,0}};
FrElement A_s1nl2m = {0x1, Fr_SHORT,{0x01,0,0,0}};
FrElement B_s1nl2m = {0x2, Fr_LONGMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_s1nl2m = {0,0,{0,0,0,0}};
FrElement A1_s1nl2m = {0x0, Fr_SHORT,{0x0,0,0,0}};
FrElement B1_s1nl2m = {0x2, Fr_LONGMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_s1nl2m = {0,0,{0,0,0,0}};
FrElement A2_s1nl2m = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1nl2m = {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1nl2m = {0,0,{0,0,0,0}};
FrElement A3_s1nl2m= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1nl2m= {INT_MAX,Fr_LONGMONTGOMERY,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};


//mul_l1ms2n
//sub_l1ms2n 7
FrElement Result_l1ms2n = {0,0,{0,0,0,0}};
FrElement A_l1ms2n = {0x1, Fr_LONGMONTGOMERY,{0x01,0,0,0}};
FrElement B_l1ms2n = {0x2, Fr_SHORT,{0x02,0,0,0}};

FrElement Result1_l1ms2n = {0,0,{0,0,0,0}};
FrElement A1_l1ms2n = {0x0, Fr_LONGMONTGOMERY,{0x0,0,0,0}};
FrElement B1_l1ms2n = {0x2, Fr_SHORT,{0x2,0,0,0}};

FrElement Result2_l1ms2n = {0,0,{0,0,0,0}};
FrElement A2_l1ms2n = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ms2n= {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ms2n = {0,0,{0,0,0,0}};

FrElement A3_l1ms2n= {0xffff,0xc0000000,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};
FrElement B3_l1ms2n= {-1,0x0,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};


//mul_l1ns2m
FrElement Result_l1ns2m = {0,0,{0,0,0,0}};
FrElement A_l1ns2m = {0x1, Fr_LONG,{0x01,0,0,0}};
FrElement B_l1ns2m = {0x2, Fr_SHORTMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_l1ns2m = {0,0,{0,0,0,0}};
FrElement A1_l1ns2m = {0x0, Fr_LONG,{0x0,0,0,0}};
FrElement B1_l1ns2m = {0x2, Fr_SHORTMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_l1ns2m = {0,0,{0,0,0,0}};
FrElement A2_l1ns2m = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ns2m= {0x1bb8, Fr_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ns2m = {0,0,{0,0,0,0}};
FrElement A3_l1ns2m = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ns2m = {0xffff, Fr_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_l1ms2m
//sub_l1ms2m 8
FrElement Result_l1ms2m = {0,0,{0,0,0,0}};
FrElement A_l1ms2m = {0x1, Fr_LONGMONTGOMERY,{0x01,0,0,0}};
FrElement B_l1ms2m = {0x2, Fr_SHORTMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_l1ms2m = {0,0,{0,0,0,0}};
FrElement A1_l1ms2m = {0x0, Fr_LONGMONTGOMERY,{0x0,0,0,0}};
FrElement B1_l1ms2m = {0x2, Fr_SHORTMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_l1ms2m = {0,0,{0,0,0,0}};
FrElement A2_l1ms2m = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ms2m= {0x1bb8, Fr_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ms2m = {0,0,{0,0,0,0}};
FrElement A3_l1ms2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ms2m = {0xffff, Fr_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1ml2m
//sub_s1ml2m 9
FrElement Result_s1ml2m = {0,0,{0,0,0,0}};
FrElement A_s1ml2m = {0x1, Fr_SHORTMONTGOMERY,{0x01,0,0,0}};
FrElement B_s1ml2m = {0x2, Fr_LONGMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_s1ml2m = {0,0,{0,0,0,0}};
FrElement A1_s1ml2m = {0x0, Fr_SHORTMONTGOMERY,{0x0,0,0,0}};
FrElement B1_s1ml2m = {0x2, Fr_LONGMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_s1ml2m = {0,0,{0,0,0,0}};
FrElement A2_s1ml2m = {0xa1f0, Fr_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1ml2m = {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1ml2m = {0,0,{0,0,0,0}};
FrElement A3_s1ml2m = {0xffff, Fr_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1ml2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1ml2n
FrElement Result_s1ml2n = {0,0,{0,0,0,0}};
FrElement A_s1ml2n = {0x1, Fr_SHORTMONTGOMERY,{0x01,0,0,0}};
FrElement B_s1ml2n = {0x2, Fr_LONG,{0x02,0,0,0}};

FrElement Result1_s1ml2n = {0,0,{0,0,0,0}};
FrElement A1_s1ml2n = {0x0, Fr_SHORTMONTGOMERY,{0x0,0,0,0}};
FrElement B1_s1ml2n = {0x2, Fr_LONG,{0x2,0,0,0}};

FrElement Result2_s1ml2n = {0,0,{0,0,0,0}};
FrElement A2_s1ml2n = {0xa1f0, Fr_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1ml2n = {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1ml2n = {0,0,{0,0,0,0}};
FrElement A3_s1ml2n = {0xffff, Fr_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1ml2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// s1l2n
FrElement Result_s1l2n = {0,0,{0,0,0,0}};
FrElement A_s1l2n = {0x1, Fr_SHORT,{0x01,0,0,0}};
FrElement B_s1l2n = {0x2, Fr_LONG,{0x02,0,0,0}};

FrElement Result1_s1l2n = {0,0,{0,0,0,0}};
FrElement A1_s1l2n = {0x0, Fr_SHORT,{0x0,0,0,0}};
FrElement B1_s1l2n = {0x2, Fr_LONG,{0x2,0,0,0}};

FrElement Result2_s1l2n = {0,0,{0,0,0,0}};
FrElement A2_s1l2n = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1l2n = {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1l2n = {0,0,{0,0,0,0}};
FrElement A3_s1l2n = {0xffff, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1l2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

FrElement Result4_s1l2n = {0,0,{0,0,0,0}};
FrElement A4_s1l2n = {-1, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B4_s1l2n = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};


//l1ns2
FrElement Result_l1ns2 = {0,0,{0,0,0,0}};
FrElement A_l1ns2 = {0x1, Fr_LONG,{0x01,0,0,0}};
FrElement B_l1ns2 = {0x2, Fr_SHORT,{0x02,0,0,0}};

FrElement Result1_l1ns2 = {0,0,{0,0,0,0}};
FrElement A1_l1ns2 = {0x0, Fr_LONG,{0x0,0,0,0}};
FrElement B1_l1ns2 = {0x2, Fr_SHORT,{0x2,0,0,0}};

FrElement Result2_l1ns2 = {0,0,{0,0,0,0}};
FrElement A2_l1ns2 = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ns2 = {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ns2 = {0,0,{0,0,0,0}};
FrElement A3_l1ns2 = {0xffff, Fr_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ns2 = {0xffff, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};


// s1l2m
FrElement Result_s1l2m = {0,0,{0,0,0,0}};
FrElement A_s1l2m = {0x1, Fr_SHORT,{0x01,0,0,0}};
FrElement B_s1l2m = {0x2, Fr_LONGMONTGOMERY,{0x02,0,0,0}};

FrElement Result1_s1l2m = {0,0,{0,0,0,0}};
FrElement A1_s1l2m = {0x0, Fr_SHORT,{0x0,0,0,0}};
FrElement B1_s1l2m = {0x2, Fr_LONGMONTGOMERY,{0x2,0,0,0}};

FrElement Result2_s1l2m = {0,0,{0,0,0,0}};
FrElement A2_s1l2m = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_s1l2m = {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_s1l2m = {0,0,{0,0,0,0}};
FrElement A3_s1l2m = {0xffff, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_s1l2m = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//sub_l1ms2
FrElement Result_l1ms2 = {0,0,{0,0,0,0}};
FrElement A_l1ms2 = {0x1, Fr_LONGMONTGOMERY,{0x01,0,0,0}};
FrElement B_l1ms2 = {0x2, Fr_SHORT,{0x02,0,0,0}};

FrElement Result1_l1ms2 = {0,0,{0,0,0,0}};
FrElement A1_l1ms2 = {0x0, Fr_LONGMONTGOMERY,{0x0,0,0,0}};
FrElement B1_l1ms2 = {0x2, Fr_SHORT,{0x2,0,0,0}};

FrElement Result2_l1ms2 = {0,0,{0,0,0,0}};
FrElement A2_l1ms2 = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FrElement B2_l1ms2 = {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FrElement Result3_l1ms2 = {0,0,{0,0,0,0}};
FrElement A3_l1ms2 = {0xffff, Fr_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FrElement B3_l1ms2 = {0xffff, Fr_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};


#endif


#if defined(TEST_FQ_C_FUNCTIONS) || defined(TEST_FQ_ASM_FUNCTIONS)
uint64_t uRawResult  = 0;
uint64_t uRawResult1 = 0;
uint64_t uRawResult2 = 0;
uint64_t uRawResult3 = 0;
uint64_t uRawResult4 = 0;
uint64_t uRawResult5 = 0;
uint64_t uRawResult6 = 0;
uint64_t uRawResult7 = 0;
uint64_t uRawResult8 = 0;
uint64_t uRawResult9 = 0;
FqRawElement pRawResult = {0,0,0,0};
FqRawElement pRawA = {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
FqRawElement pRawB = {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5};

FqRawElement pRawResult1 = {0,0,0,0};
FqRawElement pRawA1      = {0x1,0,0,0};
FqRawElement pRawB1      = {0x2,0,0,0};

FqRawElement pRawResult2 = {0,0,0,0};
FqRawElement pRawA2      = {0xfffffffffffffffe,0,0,0};
FqRawElement pRawB2      = {0xffffffffffffffff,0,0,0};

FqRawElement pRawResult3 = {0,0,0,0};
FqRawElement pRawA3      = {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
FqRawElement pRawB3      = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};

FqRawElement pRawResult4 = {0,0,0,0};
FqRawElement pRawA4      = {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
FqRawElement pRawB4      = {0xffffffffffffffff,0,0,0};

FqRawElement pRawResult5 = {0,0,0,0};
FqRawElement pRawA5      = {0x0,0,0,0};
FqRawElement pRawB5      = {0x2,0,0,0};

FqRawElement pRawResult6 = {0,0,0,0};
FqRawElement pRawA6      = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
FqRawElement pRawB6      = {0,0,0,0};

FqRawElement pRawResult7 = {0,0,0,0};
FqRawElement pRawA7      = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
FqRawElement pRawB7      = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};

FqRawElement pRawResult8 = {0,0,0,0};
FqRawElement pRawA8      = {1,0,0,0};
FqRawElement pRawB8      = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};


FqRawElement pRawResult9 = {0,0,0,0};
FqRawElement pRawA9      = {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
FqRawElement pRawB9      = {1,0,0,0};


FqElement RawResult = {0,0,{0,0,0,0}};
FqElement RawA = {0xa1f0, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement RawB = {0x1bb8, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement RawResult1 = {0,0,{0,0,0,0}};
FqElement RawA1 = {0xa1f0, Fq_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement RawB1 = {0x1bb8, Fq_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement RawResult2 = {0,0,{0,0,0,0}};
FqElement RawA2 = {0xa1f0, Fq_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement RawB2 = {0x1bb8, Fq_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement RawResult3 = {0,0,{0,0,0,0}};
FqElement RawA3 = {0xa1f0, Fq_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement RawB3 = {0x1bb8, Fq_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};



// mul_s1s2
FqElement Result_s1s2 = {0,0,{0,0,0,0}};
FqElement A_s1s2 = {0x1, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B_s1s2 = {0x2, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result1_s1s2 = {0,0,{0,0,0,0}};
FqElement A1_s1s2 = {0x0, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B1_s1s2 = {0x2, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result2_s1s2 = {0,0,{0,0,0,0}};
FqElement A2_s1s2 = {0xa1f0, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_s1s2 = {0x1bb8, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_s1s2 = {0,0,{0,0,0,0}};
FqElement A3_s1s2 = {INT_MAX, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B3_s1s2 = {INT_MAX, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

// mul_l1nl2n
FqElement Result_l1nl2n = {0,0,{0,0,0,0}};
FqElement A_l1nl2n = {0x1, Fq_LONG,{0x01,0,0,0}};
FqElement B_l1nl2n = {0x2, Fq_LONG,{0x02,0,0,0}};

FqElement Result1_l1nl2n = {0,0,{0,0,0,0}};
FqElement A1_l1nl2n = {0x0, Fq_LONG,{0x0,0,0,0}};
FqElement B1_l1nl2n = {0x2, Fq_LONG,{0x2,0,0,0}};

FqElement Result2_l1nl2n = {0,0,{0,0,0,0}};
FqElement A2_l1nl2n = {0xa1f0, Fq_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1nl2n= {0x1bb8, Fq_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1nl2n = {0,0,{0,0,0,0}};
FqElement A3_l1nl2n = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1nl2n = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ml2n
FqElement Result_l1ml2n = {0,0,{0,0,0,0}};
FqElement A_l1ml2n = {0x1, Fq_LONGMONTGOMERY,{0x01,0,0,0}};
FqElement B_l1ml2n = {0x2, Fq_LONG,{0x02,0,0,0}};

FqElement Result1_l1ml2n = {0,0,{0,0,0,0}};
FqElement A1_l1ml2n = {0x0, Fq_LONGMONTGOMERY,{0x0,0,0,0}};
FqElement B1_l1ml2n = {0x2, Fq_LONG,{0x2,0,0,0}};

FqElement Result2_l1ml2n = {0,0,{0,0,0,0}};
FqElement A2_l1ml2n = {0xa1f0, Fq_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ml2n= {0x1bb8, Fq_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ml2n = {0,0,{0,0,0,0}};
FqElement A3_l1ml2n = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1ml2n = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1nl2m
FqElement Result_l1nl2m = {0,0,{0,0,0,0}};
FqElement A_l1nl2m = {0x1, Fq_LONG,{0x01,0,0,0}};
FqElement B_l1nl2m = {0x2, Fq_LONGMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_l1nl2m = {0,0,{0,0,0,0}};
FqElement A1_l1nl2m = {0x0, Fq_LONG,{0x0,0,0,0}};
FqElement B1_l1nl2m = {0x2, Fq_LONGMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_l1nl2m = {0,0,{0,0,0,0}};
FqElement A2_l1nl2m = {0xa1f0, Fq_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1nl2m= {0x1bb8, Fq_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1nl2m = {0,0,{0,0,0,0}};
FqElement A3_l1nl2m = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1nl2m = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ml2m
FqElement Result_l1ml2m = {0,0,{0,0,0,0}};
FqElement A_l1ml2m = {0x1, Fq_LONGMONTGOMERY,{0x01,0,0,0}};
FqElement B_l1ml2m = {0x2, Fq_LONGMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_l1ml2m = {0,0,{0,0,0,0}};
FqElement A1_l1ml2m = {0x0, Fq_LONGMONTGOMERY,{0x0,0,0,0}};
FqElement B1_l1ml2m = {0x2, Fq_LONGMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_l1ml2m = {0,0,{0,0,0,0}};
FqElement A2_l1ml2m = {0xa1f0, Fq_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ml2m= {0x1bb8, Fq_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ml2m = {0,0,{0,0,0,0}};
FqElement A3_l1ml2m = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1ml2m = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

// mul_l1ns2n
FqElement Result_l1ns2n = {0,0,{0,0,0,0}};
FqElement A_l1ns2n = {0x1, Fq_LONG,{0x01,0,0,0}};
FqElement B_l1ns2n = {0x2, Fq_SHORT,{0x02,0,0,0}};

FqElement Result1_l1ns2n = {0,0,{0,0,0,0}};
FqElement A1_l1ns2n = {0x0, Fq_LONG,{0x0,0,0,0}};
FqElement B1_l1ns2n = {0x2, Fq_SHORT,{0x2,0,0,0}};

FqElement Result2_l1ns2n = {0,0,{0,0,0,0}};
FqElement A2_l1ns2n = {0xa1f0, Fq_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ns2n= {0x1bb8, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ns2n = {0,0,{0,0,0,0}};
FqElement A3_l1ns2n = {INT_MAX, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1ns2n = {-1, Fq_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1nl2n
FqElement Result_s1nl2n = {0,0,{0,0,0,0}};
FqElement A_s1nl2n = {0x1, Fq_SHORT,{0x01,0,0,0}};
FqElement B_s1nl2n = {0x2, Fq_LONG,{0x02,0,0,0}};

FqElement Result1_s1nl2n = {0,0,{0,0,0,0}};
FqElement A1_s1nl2n = {0x0, Fq_SHORT,{0x0,0,0,0}};
FqElement B1_s1nl2n = {0x2, Fq_LONG,{0x2,0,0,0}};

FqElement Result2_s1nl2n = {0,0,{0,0,0,0}};
FqElement A2_s1nl2n = {0xa1f0, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_s1nl2n= {0x1bb8, Fq_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_s1nl2n = {0,0,{0,0,0,0}};
FqElement A3_s1nl2n = {-1, Fq_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_s1nl2n = {INT_MAX, Fq_LONG,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};

//mul_s1nl2m
FqElement Result_s1nl2m = {0,0,{0,0,0,0}};
FqElement A_s1nl2m = {0x1, Fq_SHORT,{0x01,0,0,0}};
FqElement B_s1nl2m = {0x2, Fq_LONGMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_s1nl2m = {0,0,{0,0,0,0}};
FqElement A1_s1nl2m = {0x0, Fq_SHORT,{0x0,0,0,0}};
FqElement B1_s1nl2m = {0x2, Fq_LONGMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_s1nl2m = {0,0,{0,0,0,0}};
FqElement A2_s1nl2m = {0xa1f0, Fq_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_s1nl2m = {0x1bb8, Fq_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_s1nl2m = {0,0,{0,0,0,0}};
FqElement A3_s1nl2m = {-1, Fq_SHORT,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_s1nl2m = {INT_MAX, Fq_LONGMONTGOMERY,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};

//mul_l1ms2n
FqElement Result_l1ms2n = {0,0,{0,0,0,0}};
FqElement A_l1ms2n = {0x1, Fq_LONGMONTGOMERY,{0x01,0,0,0}};
FqElement B_l1ms2n = {0x2, Fq_SHORT,{0x02,0,0,0}};

FqElement Result1_l1ms2n = {0,0,{0,0,0,0}};
FqElement A1_l1ms2n = {0x0, Fq_LONGMONTGOMERY,{0x0,0,0,0}};
FqElement B1_l1ms2n = {0x2, Fq_SHORT,{0x2,0,0,0}};

FqElement Result2_l1ms2n = {0,0,{0,0,0,0}};
FqElement A2_l1ms2n = {0xa1f0, Fq_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ms2n= {0x1bb8, Fq_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ms2n = {0,0,{0,0,0,0}};
FqElement A3_l1ms2n = {0xffff, Fq_LONGMONTGOMERY,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};
FqElement B3_l1ms2n = {-1, Fq_SHORT,{LONG_MAX,LONG_MAX,LONG_MAX,LONG_MAX}};

//mul_l1ns2m
FqElement Result_l1ns2m = {0,0,{0,0,0,0}};
FqElement A_l1ns2m = {0x1, Fq_LONG,{0x01,0,0,0}};
FqElement B_l1ns2m = {0x2, Fq_SHORTMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_l1ns2m = {0,0,{0,0,0,0}};
FqElement A1_l1ns2m = {0x0, Fq_LONG,{0x0,0,0,0}};
FqElement B1_l1ns2m = {0x2, Fq_SHORTMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_l1ns2m = {0,0,{0,0,0,0}};
FqElement A2_l1ns2m = {0xa1f0, Fq_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ns2m= {0x1bb8, Fq_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ns2m = {0,0,{0,0,0,0}};
FqElement A3_l1ns2m = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1ns2m = {0xffff, Fq_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_l1ms2m
FqElement Result_l1ms2m = {0,0,{0,0,0,0}};
FqElement A_l1ms2m = {0x1, Fq_LONGMONTGOMERY,{0x01,0,0,0}};
FqElement B_l1ms2m = {0x2, Fq_SHORTMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_l1ms2m = {0,0,{0,0,0,0}};
FqElement A1_l1ms2m = {0x0, Fq_LONGMONTGOMERY,{0x0,0,0,0}};
FqElement B1_l1ms2m = {0x2, Fq_SHORTMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_l1ms2m = {0,0,{0,0,0,0}};
FqElement A2_l1ms2m = {0xa1f0, Fq_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_l1ms2m= {0x1bb8, Fq_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_l1ms2m = {0,0,{0,0,0,0}};
FqElement A3_l1ms2m = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_l1ms2m = {0xffff, Fq_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1ml2m
FqElement Result_s1ml2m = {0,0,{0,0,0,0}};
FqElement A_s1ml2m = {0x1, Fq_SHORTMONTGOMERY,{0x01,0,0,0}};
FqElement B_s1ml2m = {0x2, Fq_LONGMONTGOMERY,{0x02,0,0,0}};

FqElement Result1_s1ml2m = {0,0,{0,0,0,0}};
FqElement A1_s1ml2m = {0x0, Fq_SHORTMONTGOMERY,{0x0,0,0,0}};
FqElement B1_s1ml2m = {0x2, Fq_LONGMONTGOMERY,{0x2,0,0,0}};

FqElement Result2_s1ml2m = {0,0,{0,0,0,0}};
FqElement A2_s1ml2m = {0xa1f0, Fq_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_s1ml2m = {0x1bb8, Fq_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_s1ml2m = {0,0,{0,0,0,0}};
FqElement A3_s1ml2m = {0xffff, Fq_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_s1ml2m = {0xffff, Fq_LONGMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

//mul_s1ml2n
FqElement Result_s1ml2n = {0,0,{0,0,0,0}};
FqElement A_s1ml2n = {0x1, Fq_SHORTMONTGOMERY,{0x01,0,0,0}};
FqElement B_s1ml2n = {0x2, Fq_LONG,{0x02,0,0,0}};

FqElement Result1_s1ml2n = {0,0,{0,0,0,0}};
FqElement A1_s1ml2n = {0x0, Fq_SHORTMONTGOMERY,{0x0,0,0,0}};
FqElement B1_s1ml2n = {0x2, Fq_LONG,{0x2,0,0,0}};

FqElement Result2_s1ml2n = {0,0,{0,0,0,0}};
FqElement A2_s1ml2n = {0xa1f0, Fq_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
FqElement B2_s1ml2n = {0x1bb8, Fq_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

FqElement Result3_s1ml2n = {0,0,{0,0,0,0}};
FqElement A3_s1ml2n = {0xffff, Fq_SHORTMONTGOMERY,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
FqElement B3_s1ml2n = {0xffff, Fq_LONG,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
#endif

#if defined(TEST_FR_C_FUNCTIONS) || defined(TEST_FR_ASM_FUNCTIONS)
void compare_rawResult(FrRawElement pRawResult_asm, FrRawElement pRawResult_c, int idx, std::string TestName)
{
    if (pRawResult_asm[0] != pRawResult_c[0] ||
        pRawResult_asm[1] != pRawResult_c[1] ||
        pRawResult_asm[2] != pRawResult_c[2] ||
        pRawResult_asm[3] != pRawResult_c[3])
    {
        std::cout << TestName << idx << " failed!" << "\n";
    }
    else
    {
        std::cout << TestName << idx << " succeed!" << "\n";
    }
}

void compare_Result(PFrElement pResult_asm, PFrElement pResult_c, int idx, std::string TestName)
{
    if (pResult_asm->shortVal != pResult_c->shortVal     ||
        pResult_asm->longVal[0] != pResult_c->longVal[0] ||
        pResult_asm->longVal[1] != pResult_c->longVal[1] ||
        pResult_asm->longVal[2] != pResult_c->longVal[2] ||
        pResult_asm->longVal[3] != pResult_c->longVal[3])
    {
        std::cout << TestName << idx << " failed!" << "\n";
    }
    else
    {
        std::cout << TestName << idx << " succeed!" << "\n";
    }
}

void Fr_Rw_Neg_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_Neg_test " << idx << ": " <<  '\n';
    Fr_rawNeg(pRawResult, pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_Rw_Neg_unit_test()
{
    //Fr_Rw_Neg_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    //Fr_Rw_Neg_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x43e1f593f0000003,0x2833e84879b97090,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x43e1f593f0000003,0x2833e84879b97092,0xb85045b68181585e,0x30644e72e131a02a}; 
    //Fr_Rw_Neg_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult5_c;

    Fr_rawNeg(pRawResult0_c, pRawA0);
    Fr_rawNeg(pRawResult1_c, pRawA1);
    Fr_rawNeg(pRawResult2_c, pRawA2);
    Fr_rawNeg(pRawResult3_c, pRawA3);
    Fr_rawNeg(pRawResult5_c, pRawA5);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_Neg_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_Neg_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_Neg_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_Neg_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fr_Rw_Neg_unit_test");
}


void Fr_Rw_copy_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_copy_test " << idx << ": " <<  '\n';
    Fr_rawCopy(pRawResult, pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_Rw_copy_unit_test()
{
    //Fr_Rw_copy_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    //Fr_Rw_copy_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1,0x0,0x0,0x0};
    //Fr_Rw_copy_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xfffffffffffffffe,0x0,0x0,0x0};
    //Fr_Rw_copy_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawCopy(pRawResult0_c, pRawA0);
    Fr_rawCopy(pRawResult1_c, pRawA1);
    Fr_rawCopy(pRawResult2_c, pRawA2);
    Fr_rawCopy(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_copy_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_copy_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_copy_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_copy_unit_test");
}


void Fr_Rw_add_unit_test()
{
    //Fr_rawAdd Test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba};
    //Fr_rawAdd Test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x3,0x0,0x0,0x0};
    //Fr_rawAdd Test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xfffffffffffffffd,0x1,0x0,0x0};
    //Fr_rawAdd Test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0xbc1e0a6c0ffffffc,0xd7cc17b786468f6d,0x47afba497e7ea7a1,0xcf9bb18d1ece5fd5};
    //Fr_rawAdd Test 6:
    FrRawElement pRawA6= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB6= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult6= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult6_c;

    Fr_rawAdd(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawAdd(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawAdd(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawAdd(pRawResult3_c, pRawA3, pRawB3);
    Fr_rawAdd(pRawResult6_c, pRawA6, pRawB6);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_add_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_add_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_add_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_add_unit_test");
    compare_rawResult(pRawResult6, pRawResult6_c, 6, "Fr_Rw_add_unit_test");
}

void Fr_Rw_sub_unit_test()
{
    //Fr_Rw_sub_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f};
    //Fr_Rw_sub_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_sub_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_sub_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x43e1f593f0000000,0x2833e84879b97090,0xb85045b68181585c,0x30644e72e131a028};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawSub(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawSub(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawSub(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawSub(pRawResult3_c, pRawA3, pRawB3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_sub_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_sub_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_sub_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_sub_unit_test");


}

void Fr_Rw_add_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_rawAdd Test " << idx << ": " <<  '\n';
    Fr_rawAdd(pRawResult, pRawA, pRawB);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fr_Rw_sub_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_sub_test " << idx << ": " <<  '\n';
    Fr_rawSub(pRawResult, pRawA, pRawB);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_Rw_mul_unit_test()
{
    //Fr_Rw_mul_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
    //Fr_Rw_mul_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
    //Fr_Rw_mul_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
    //Fr_Rw_mul_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0xd13604f1e300865c,0xba58b3d2a99f4ba5,0x1b4e415146d47f95,0x55c593ff9cfbf0a};
    //Fr_Rw_mul_test 4:
    FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult4= {0x1d0a8ff4c8e5744c,0x6fd9959908f97ec,0xdfe72d24fcdef34e,0xd1c7f8bb929dbb};
    //Fr_Rw_mul_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};   
    //Fr_Rw_mul_test 8:
    FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawResult8= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult4_c;
    FrRawElement pRawResult5_c;
    FrRawElement pRawResult8_c;

    Fr_rawMMul(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawMMul(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawMMul(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawMMul(pRawResult3_c, pRawA3, pRawB3);
    Fr_rawMMul(pRawResult4_c, pRawA4, pRawB4);
    Fr_rawMMul(pRawResult5_c, pRawA5, pRawB5);
    Fr_rawMMul(pRawResult8_c, pRawA8, pRawB8);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult4, pRawResult4_c, 4, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fr_Rw_mul_unit_test");
    compare_rawResult(pRawResult8, pRawResult8_c, 8, "Fr_Rw_mul_unit_test");
}

void Fr_Rw_mul_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_mul_test " << idx << ": " <<  '\n';
    Fr_rawMMul(pRawResult, pRawA, pRawB);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};" << '\n';
}


void Fr_Rw_Msquare_unit_test()
{
    //Fr_Rw_Msquare_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x9907e2cb536c4654,0xd65db18eb521336a,0xe31a6546c6ec385,0x1dad258dd14a255c};
    //Fr_Rw_Msquare_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xdc5ba0056db1194e,0x90ef5a9e111ec87,0xc8260de4aeb85d5d,0x15ebf95182c5551c};
    //Fr_Rw_Msquare_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xa36e2021c3cb4871,0x9ccfdd64549375be,0xfabb3edd8b138d5d,0x1f90d859c5779848};
    //Fr_Rw_Msquare_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x3ff409a0d3b30d18,0xca2027949dd16d47,0x6c8c4187ce125dad,0x3b5af5c48558e40};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawMSquare(pRawResult0_c, pRawA0);
    Fr_rawMSquare(pRawResult1_c, pRawA1);
    Fr_rawMSquare(pRawResult2_c, pRawA2);
    Fr_rawMSquare(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_Msquare_unit_test");
}

void Fr_Rw_Msquare_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_Msquare_test " << idx << ": " <<  '\n';
    Fr_rawMSquare(pRawResult, pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_Rw_mul1_unit_test()
{
    //Fr_Rw_mul1_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xf599ddfbad86bc06,0xec1c0a17893c85cd,0x5d482c29ab80ec64,0x4d4face96bf58f3};
    //Fr_Rw_mul1_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
    //Fr_Rw_mul1_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
    //Fr_Rw_mul1_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x35f905313fdf50bb,0x5bab176e33b97efa,0xafd63944c55782d,0x1402c8cfdb71d335};    
    //Fr_Rw_mul1_test 9:
    FrRawElement pRawA9= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB9= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult9= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult9_c;

    Fr_rawMMul1(pRawResult0_c, pRawA0, pRawB0[0]);
    Fr_rawMMul1(pRawResult1_c, pRawA1, pRawB1[0]);
    Fr_rawMMul1(pRawResult2_c, pRawA2, pRawB2[0]);
    Fr_rawMMul1(pRawResult3_c, pRawA3, pRawB3[0]);
    Fr_rawMMul1(pRawResult9_c, pRawA9, pRawB9[0]);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_mul1_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_mul1_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_mul1_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_mul1_unit_test");
    compare_rawResult(pRawResult9, pRawResult9_c, 9, "Fr_Rw_mul1_unit_test");
}

void Fr_Rw_mul1_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_mul1_test " << idx << ": " <<  '\n';
    Fr_rawMMul1(pRawResult, pRawA, pRawB[0]);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_Rw_ToMontgomery_unit_test()
{
    //Fr_Rw_ToMontgomery_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
    //Fr_Rw_ToMontgomery_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xac96341c4ffffffb,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f};
    //Fr_Rw_ToMontgomery_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x5b9a85c0dc5fb590,0x293a0258129f96b,0xd31fd70514055493,0x546132966296a07};
    //Fr_Rw_ToMontgomery_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x8eaddd03c0bcc45a,0x1d0775cf53f57853,0xacb9a1fdb8079310,0x1b7838d45d9b3577};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawToMontgomery(pRawResult0_c, pRawA0);
    Fr_rawToMontgomery(pRawResult1_c, pRawA1);
    Fr_rawToMontgomery(pRawResult2_c, pRawA2);
    Fr_rawToMontgomery(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_ToMontgomery_unit_test");
}

void Fr_Rw_ToMontgomery_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_ToMontgomery_test " << idx << ": " <<  '\n';
    Fr_rawToMontgomery(pRawResult, pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_rawIsEq_test(uint64_t uRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_rawIsEq " << idx << ": " <<  '\n';
    uRawResult = Fr_rawIsEq(pRawA, pRawB);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< uRawResult << "};"<< '\n';// << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fr_Rw_IsEq_unit_test()
{
    //Fr_rawIsEq 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0x0};
    //Fr_rawIsEq 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1};
    //Fr_rawIsEq 2:
    FrRawElement pRawA2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x1};
    //Fr_rawIsEq 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x0};

    //Fr_rawIsEq 7:
    FrRawElement pRawA7= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB7= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawResult7= {0x1};

    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};
    FrRawElement pRawResult3_c = {0};
    FrRawElement pRawResult7_c = {0};

    pRawResult0_c[0] = Fr_rawIsEq(pRawA0, pRawB0);
    pRawResult1_c[0] = Fr_rawIsEq(pRawA1, pRawB1);
    pRawResult2_c[0] = Fr_rawIsEq(pRawA2, pRawB2);
    pRawResult3_c[0] = Fr_rawIsEq(pRawA3, pRawB3);
    pRawResult7_c[0] = Fr_rawIsEq(pRawA7, pRawB7);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult7, pRawResult7_c, 7, "Fr_Rw_IsEq_unit_test");
}


void Fr_rawIsZero_test(uint64_t uRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_rawIsZero_test " << idx << ": " <<  '\n';
    uRawResult = Fr_rawIsZero(pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< uRawResult << "};"<< '\n';// << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fr_rawIsZero_unit_test()
{
    //Fr_rawIsZero_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x0};
    //Fr_rawIsZero_test 1:
    FrRawElement pRawA1= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1};
    //Fr_rawIsZero_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x0};
    //Fr_rawIsZero_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x0};

    //Fr_rawIsZero_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x1};

    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};
    FrRawElement pRawResult3_c = {0};
    FrRawElement pRawResult5_c = {0};

    pRawResult0_c[0] = Fr_rawIsZero(pRawA0);
    pRawResult1_c[0] = Fr_rawIsZero(pRawA1);
    pRawResult2_c[0] = Fr_rawIsZero(pRawA2);
    pRawResult3_c[0] = Fr_rawIsZero(pRawA3);
    pRawResult5_c[0] = Fr_rawIsZero(pRawA5);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_rawIsZero_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_rawIsZero_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_rawIsZero_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_rawIsZero_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fr_rawIsZero_unit_test");
}

void Fr_Rw_FromMontgomery_unit_test()
{
    //Fr_Rw_FromMontgomery_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x55b425913927735a,0xa3ac6d7389307a4d,0x543d3ec42a2529ae,0x256e51ca1fcef59b};
    //Fr_Rw_FromMontgomery_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xdc5ba0056db1194e,0x90ef5a9e111ec87,0xc8260de4aeb85d5d,0x15ebf95182c5551c};
    //Fr_Rw_FromMontgomery_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x26d7659f271a8bb3,0x21364eeee929d8a6,0xd869189184a2650f,0x2f92867a259f026d};
    //Fr_Rw_FromMontgomery_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x3114fb0a8790445e,0x3c686fb82b0dbda3,0xa509fd6ff15d77e,0x247132c3c886548};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawFromMontgomery(pRawResult0_c, pRawA0);
    Fr_rawFromMontgomery(pRawResult1_c, pRawA1);
    Fr_rawFromMontgomery(pRawResult2_c, pRawA2);
    Fr_rawFromMontgomery(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_Rw_FromMontgomery_unit_test");
}

void Fr_Rw_FromMontgomery_test(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_FromMontgomery_test " << idx << ": " <<  '\n';
    Fr_rawFromMontgomery(pRawResult, pRawA);
    std::cout << "FrRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FrRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fr_toNormal_unit_test()
{
    //Fr_toNormal_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0x0,0x80000000,{0x55b425913927735a,0xa3ac6d7389307a4d,0x543d3ec42a2529ae,0x256e51ca1fcef59b}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_toNormal(&Result0_c, &pA0);
    Fr_toNormal(&Result1_c, &pA1);
    Fr_toNormal(&Result2_c, &pA2);
    Fr_toNormal(&Result3_c, &pA3);

    compare_Result(&pResult0, &Result0_c, 0, "Fr_toNormal_unit_test");
    compare_Result(&pResult1, &Result1_c, 1, "Fr_toNormal_unit_test");
    compare_Result(&pResult2, &Result2_c, 2, "Fr_toNormal_unit_test");
    compare_Result(&pResult3, &Result3_c, 3, "Fr_toNormal_unit_test");
}

void Fr_toNormal_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_toNormal_test " << idx << ": " <<  '\n';
    Fr_toNormal(pResult, pA);
    std::cout << "FrElement pA" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    //std::cout << "FrElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrElement pResult" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_s1s2_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_s1s2_unit_test()
{
    //Fr_mul_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x80000000,{0x1188b480,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x80000000,{0x3fffffff00000001,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_mul(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_mul(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_mul(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_mul_s1s2_unit_test");
}

void Fr_mul_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_l1nl2n_unit_test()
{
    //Fr_mul_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0xc0000000,{0x1497892315a07fe1,0x930f99e96b3b9535,0x73b1e28430b17066,0x29e821cd214b6d6b}};
    //Fr_mul_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0xc0000000,{0x19094ca438fc19d0,0x4f1502bc99846068,0x5cc3236f2303a977,0x17808a731cd75a48}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_mul(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_mul(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_mul(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_mul_l1nl2n_unit_test");
}

void Fr_mul_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_l1ml2n_unit_test()
{
    //Fr_mul_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_mul(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_mul(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_mul(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_mul_l1ml2n_unit_test");
}


void Fr_mul_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_l1ml2m_unit_test()
{
    //Fr_mul_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_mul(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_mul(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_mul(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_mul_l1ml2m_unit_test");
}

void Fr_mul_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_l1nl2m_unit_test()
{
    //Fr_mul_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_mul(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_mul(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_mul(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_mul_l1nl2m_unit_test");
}

void Fr_mul_l1ns2n_unit_test()
{
    //Fr_mul_l1ns2n_test 0:
    FrElement pA_l1ns2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_l1ns2n_test 1:
    FrElement pA_l1ns2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ns2n_test 2:
    FrElement pA_l1ns2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns2n2= {0x0,0xc0000000,{0x2d67d8d2e0004952,0xaddd11ecde7f7ae3,0xed975f635da0de4d,0x1a7fe303489132eb}};
    //Fr_mul_l1ns2n_test 3:
    FrElement pA_l1ns2n3= {0x7fffffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns2n3= {0x0,0xc0000000,{0x90dd4dd6a1de9254,0xe2fe3be3bc047346,0xda25203224bdc5a8,0xbf3a7101ab99a89}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ns2n0, &pB_l1ns2n0);
    Fr_mul(&Result1_c, &pA_l1ns2n1, &pB_l1ns2n1);
    Fr_mul(&Result2_c, &pA_l1ns2n2, &pB_l1ns2n2);
    Fr_mul(&Result3_c, &pA_l1ns2n3, &pB_l1ns2n3);

    compare_Result(&pResult_l1ns2n0, &Result0_c, 0, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n1, &Result1_c, 1, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n2, &Result2_c, 2, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n3, &Result3_c, 3, "Fr_mul_l1ns2n_unit_test");
}

void Fr_mul_l1ns2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ns2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_s1nl2n_unit_test()
{
    //Fr_mul_s1nl2n_test 0:
    FrElement pA_s1nl2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_s1nl2n_test 1:
    FrElement pA_s1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1nl2n_test 2:
    FrElement pA_s1nl2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2n2= {0x0,0xc0000000,{0x3c79e7002385099,0x69bfe0da5a608f7b,0x3dbd93ce32b4e2b3,0x773561b6a940451}};
    //Fr_mul_s1nl2n_test 3:
    FrElement pA_s1nl2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2n3= {0x7fffffff,0x80000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2n3= {0x0,0xc0000000,{0x7c8b07120fa19dd4,0x19b02d60cfbeb467,0xe1f374b7a57d8ed5,0x22a83208b264056d}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1nl2n0, &pB_s1nl2n0);
    Fr_mul(&Result1_c, &pA_s1nl2n1, &pB_s1nl2n1);
    Fr_mul(&Result2_c, &pA_s1nl2n2, &pB_s1nl2n2);
    Fr_mul(&Result3_c, &pA_s1nl2n3, &pB_s1nl2n3);

    compare_Result(&pResult_s1nl2n0, &Result0_c, 0, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n1, &Result1_c, 1, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n2, &Result2_c, 2, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n3, &Result3_c, 3, "Fr_mul_s1nl2n_unit_test");
}

void Fr_mul_s1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_s1nl2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_s1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_s1nl2m_unit_test()
{
    //Fr_mul_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0x80000000,{0xd708561abffca754,0x6c6d984a2702a36a,0xc0f6e8587da122fb,0x164b29d2c31ce3ab}};
    //Fr_mul_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0x80000000,{0xab57780eac37ddd2,0x9ffb06c643291bf,0xb327f5cb01f66c9e,0x2f40c4dcc2ed6d85}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_mul(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_mul(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_mul(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c, 0, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c, 1, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c, 2, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c, 3, "Fr_mul_s1nl2m_unit_test");
}

void Fr_mul_s1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_s1nl2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_s1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fr_mul_l1ms2n_unit_test()
{
    //Fr_mul_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0x80000000,{0x5d70bdff3d855140,0xfab648d14060e580,0xc8cd54f7f14513ba,0x23995be618ce6b27}};
    //Fr_mul_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0x80000000,{0xab57780eac37ddd2,0x9ffb06c643291bf,0xb327f5cb01f66c9e,0x2f40c4dcc2ed6d85}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_mul(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_mul(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_mul(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c, 0, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c, 1, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c, 2, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c, 3, "Fr_mul_l1ms2n_unit_test");
}

void Fr_mul_l1ms2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ms2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fr_mul_l1ns2m_unit_test()
{
    //Fr_mul_l1ns2m_test 0:
    FrElement pA_l1ns2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ns2m_test 1:
    FrElement pA_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ns2m_test 2:
    FrElement pA_l1ns2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns2m2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ns2m_test 3:
    FrElement pA_l1ns2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns2m3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ns2m0, &pB_l1ns2m0);
    Fr_mul(&Result1_c, &pA_l1ns2m1, &pB_l1ns2m1);
    Fr_mul(&Result2_c, &pA_l1ns2m2, &pB_l1ns2m2);
    Fr_mul(&Result3_c, &pA_l1ns2m3, &pB_l1ns2m3);

    compare_Result(&pResult_l1ns2m0, &Result0_c, 0, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m1, &Result1_c, 1, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m2, &Result2_c, 2, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m3, &Result3_c, 3, "Fr_mul_l1ns2m_unit_test");
}

void Fr_mul_l1ns2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ns2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_l1ms2m_unit_test()
{
    //Fr_mul_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_mul(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_mul(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_mul(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c, 0, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c, 1, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c, 2, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c, 3, "Fr_mul_l1ms2m_unit_test");
}

void Fr_mul_l1ms2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_l1ms2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fr_mul_s1ml2m_unit_test()
{
    //Fr_mul_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_mul(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_mul(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_mul(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c, 0, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c, 1, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c, 2, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c, 3, "Fr_mul_s1ml2m_unit_test");
}

void Fr_mul_s1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_s1ml2m_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_s1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_mul_s1ml2n_unit_test()
{
    //Fr_mul_s1ml2n_test 0:
    FrElement pA_s1ml2n0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1ml2n_test 1:
    FrElement pA_s1ml2n1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1ml2n_test 2:
    FrElement pA_s1ml2n2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2n2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_s1ml2n_test 3:
    FrElement pA_s1ml2n3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2n3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1ml2n0, &pB_s1ml2n0);
    Fr_mul(&Result1_c, &pA_s1ml2n1, &pB_s1ml2n1);
    Fr_mul(&Result2_c, &pA_s1ml2n2, &pB_s1ml2n2);
    Fr_mul(&Result3_c, &pA_s1ml2n3, &pB_s1ml2n3);

    compare_Result(&pResult_s1ml2n0, &Result0_c, 0, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n1, &Result1_c, 1, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n2, &Result2_c, 2, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n3, &Result3_c, 3, "Fr_mul_s1ml2n_unit_test");
}

void Fr_mul_s1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_mul_s1ml2n_test " << idx << ": " <<  '\n';
    Fr_mul(pResult, pA, pB);
    std::cout << "FrElement pA_s1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

















// 1
void Fr_sub_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_s1s2_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_sub_s1s2_unit_test()
{
    //Fr_sub_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {-1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {-2,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x8638,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_sub(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_sub(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_sub(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_sub_s1s2_unit_test");
}

// 2
void Fr_sub_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_sub_l1nl2n_unit_test()
{
    //Fr_sub_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_sub(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_sub(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_sub(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_sub_l1nl2n_unit_test");
}

// 3
void Fr_sub_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_sub_l1ml2n_unit_test()
{
    //Fr_sub_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0xc0000000,{0xeab58d5b5000000c,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0xc0000000,{0xeab58d5b5000000b,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0xc0000000,{0x435c21e84340ffc0,0x69d157661fe10190,0x52eb5c769f20dc41,0xb39cdedf0cc6a98}};
    //Fr_sub_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0xc0000000,{0x4cfb5842b1de9252,0xbaca539b424b02b5,0x21d4da7ba33c6d4b,0xdb8f589d3987fa60}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_sub(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_sub(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_sub(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_sub_l1ml2n_unit_test");
}

// 4
void Fr_sub_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_sub_l1ml2m_unit_test()
{
    //Fr_sub_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_sub(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_sub(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_sub(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_sub_l1ml2m_unit_test");
}

// 5
void Fr_sub_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_sub_l1nl2m_unit_test()
{
    //Fr_sub_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffff9,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_sub_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0xc0000000,{0xafecfa7621de925c,0x249d7e2789cff7d0,0x9ca74de630c88892,0xf161aa724469bd7}};
    //Fr_sub_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0xc0000000,{0xf6e69d513e216daf,0x6d6994ad376e6ddb,0x967b6b3ade44eb11,0x54d4f5d5a7a9a5c9}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_sub(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_sub(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_sub(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_sub_l1nl2m_unit_test");
}

// 6
void Fr_sub_s1nl2m_unit_test()
{
    //Fr_sub_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffff9,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_sub_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0xc0000000,{0xbb4f6fd511db39ad,0x186f5d9843a64987,0x34ad651b29e5a276,0x1434592143ce9f06}};
    //Fr_sub_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0xc0000000,{0x5b2db70b90000008,0x996b59fb541213f9,0x8a31e7fd8a896a8c,0xd2be2524285b6124}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_sub(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_sub(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_sub(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c, 0, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c, 1, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c, 2, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c, 3, "Fr_sub_s1nl2m_unit_test");
}

void Fr_sub_s1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_s1nl2m_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_s1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_sub_l1ms2n_unit_test()
{
    //Fr_sub_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0xc0000000,{0xeab58d5b5000000c,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0xc0000000,{0xeab58d5b5000000b,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0xc0000000,{0xb8deb6dbc80092a3,0xc7a02fb580223d7d,0xff069beb7a81106c,0x1ccd9ecd208995c2}};
    //Fr_sub_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0xc0000000,{0xe8b43e885ffffff9,0x8ec88e4d25a75c97,0x2e1e5db8f6f7edd0,0x5da6294eb8d63f05}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_sub(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_sub(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_sub(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c, 0, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c, 1, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c, 2, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c, 3, "Fr_sub_l1ms2n_unit_test");
}

void Fr_sub_l1ms2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1ms2n_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 8
void Fr_sub_l1ms2m_unit_test()
{
    //Fr_sub_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_sub(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_sub(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_sub(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c, 0, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c, 1, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c, 2, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c, 3, "Fr_sub_l1ms2m_unit_test");
}

void Fr_sub_l1ms2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1ms2m_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 9
void Fr_sub_s1ml2m_unit_test()
{
    //Fr_sub_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_sub(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_sub(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_sub(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c, 0, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c, 1, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c, 2, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c, 3, "Fr_sub_s1ml2m_unit_test");
}

void Fr_sub_s1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_s1ml2m_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_s1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 10
void Fr_sub_l1ns2_unit_test()
{
    //Fr_sub_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0xa1f0fac9f7ffe448,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_sub_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_sub(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_sub(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_sub(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_sub_l1ns2_unit_test");
}

void Fr_sub_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_l1ns2_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 11
void Fr_sub_s1l2n_unit_test()
{
    //Fr_sub_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x28290f4e41df344a,0xd435ad96965d16ae,0x2c06c2792dc5d7d7,0x2e4d7dc161e35b84}};
    //Fr_sub_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0x43e1f593f0010001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 4:
    FrElement pA_s1l2n4= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n4= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n4= {0x0,0x80000000,{0x87c3eb27e0000002,0x5067d090f372e122,0x70a08b6d0302b0ba,0x60c89ce5c2634053}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};
    FrElement Result4_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_sub(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_sub(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_sub(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);
    Fr_sub(&Result4_c, &pA_s1l2n4, &pB_s1l2n4);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n4, &Result4_c, 4, "Fr_sub_s1l2n_unit_test");
}

void Fr_sub_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_sub_s1l2n_test " << idx << ": " <<  '\n';
    Fr_sub(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


















// 1
void Fr_add_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_s1s2_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_add_s1s2_unit_test()
{
    //Fr_add_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x3,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x2,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0xbda8,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x80000000,{0xfffffffe,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_add(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_add(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_add(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_add_s1s2_unit_test");
}

// 2
void Fr_add_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_add_l1nl2n_unit_test()
{
    //Fr_add_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_add(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_add(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_add(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_add_l1nl2n_unit_test");
}

// 3
void Fr_add_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_add_l1ml2n_unit_test()
{
    //Fr_add_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0xc0000000,{0x592c68389ffffff7,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0xc0000000,{0x85d3abacbf0040,0xbe6290e259d86f01,0x6564e93fe2607c1b,0x252a8084f0653591}};
    //Fr_add_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0xc0000000,{0x6f22b2295e216dab,0x1d01c41c43fb8cb9,0x25dadfcddb423a57,0xf40c58efe5466576}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_add(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_add(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_add(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_add_l1ml2n_unit_test");
}

// 4
void Fr_add_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_add_l1ml2m_unit_test()
{
    //Fr_add_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_add(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_add(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_add(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_add_l1ml2m_unit_test");
}

// 5
void Fr_add_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_add_l1nl2m_unit_test()
{
    //Fr_add_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffffd,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_add_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0xc0000000,{0xe75ec7017e216daa,0xcc99f38b5088ab96,0xb53a5460d83f899c,0x1343bc0a22e32522}};
    //Fr_add_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0xc0000000,{0x6f22b2295e216dab,0x1d01c41c43fb8cb9,0x25dadfcddb423a57,0xf40c58efe5466576}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_add(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_add(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_add(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_add_l1nl2m_unit_test");
}

// 6
void Fr_add_s1nl2m_unit_test()
{
    //Fr_add_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffffd,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_add_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0xc0000000,{0xf2c13c606e1e14fb,0xc06bd2fc0a5efd4d,0x4d406b95d15ca380,0x1861fa84426b2851}};
    //Fr_add_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0xc0000000,{0xd369cbe3b0000004,0x4903896a609f32d5,0x19915c908786b9d1,0x71f5883e65f820d0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_add(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_add(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_add(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c, 0, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c, 1, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c, 2, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c, 3, "Fr_add_s1nl2m_unit_test");
}

void Fr_add_s1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_s1nl2m_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_s1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_add_l1ms2n_unit_test()
{
    //Fr_add_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0xc0000000,{0x592c68389ffffff7,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0xc0000000,{0x8b033eb827ff6d5d,0x6093b892f9973313,0xb949a9cb070047f0,0x1396afa5c0a80a66}};
    //Fr_add_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0xc0000000,{0xd369cbe3b0000004,0x4903896a609f32d5,0x19915c908786b9d1,0x71f5883e65f820d0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_add(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_add(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_add(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c, 0, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c, 1, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c, 2, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c, 3, "Fr_add_l1ms2n_unit_test");
}

void Fr_add_l1ms2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1ms2n_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 8
void Fr_add_l1ms2m_unit_test()
{
    //Fr_add_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_add(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_add(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_add(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c, 0, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c, 1, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c, 2, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c, 3, "Fr_add_l1ms2m_unit_test");
}

void Fr_add_l1ms2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1ms2m_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 9
void Fr_add_s1ml2m_unit_test()
{
    //Fr_add_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_add(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_add(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_add(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c, 0, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c, 1, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c, 2, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c, 3, "Fr_add_s1ml2m_unit_test");
}

void Fr_add_s1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_s1ml2m_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_s1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 10
void Fr_add_l1ns2_unit_test()
{
    //Fr_add_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0xa1f0fac9f8001bb8,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_add_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xbc1e0a6c1000fffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_add(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_add(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_add(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_add_l1ns2_unit_test");
}

void Fr_add_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_l1ns2_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 11
void Fr_add_s1l2n_unit_test()
{
    //Fr_add_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x1bb8e645ae220f97,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    //Fr_add_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0xbc1e0a6c1000fffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_add(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_add(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_add(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_add_s1l2n_unit_test");
}

void Fr_add_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_add_s1l2n_test " << idx << ": " <<  '\n';
    Fr_add(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fr_toInt_test(uint64_t uRawResult, PFrElement pA, int idx)
{
    std::cout << "//Fr_toInt_test " << idx << ": " <<  '\n';
    uRawResult = Fr_toInt(pA);
    std::cout << "FrElement pA" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< uRawResult << "};"<< '\n';// << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fr_toInt_unit_test()
{
    FrRawElement pRawResult0 = {0,0,0,0};
    FrElement RawA = {0xa1f0, Fr_SHORT,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement RawB = {0x1bb8, Fr_SHORT,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

    FrRawElement pRawResult1 = {0,0,0,0};
    FrElement RawA1 = {0xa1f0, Fr_SHORTMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement RawB1 = {0x1bb8, Fr_SHORTMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

    FrRawElement pRawResult2 = {0,0,0,0};
    FrElement RawA2 = {0xa1f0, Fr_LONG,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement RawB2 = {0x1bb8, Fr_LONG,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};

    FrRawElement pRawResult3 = {0,0,0,0};
    FrElement RawA3 = {0xa1f0, Fr_LONGMONTGOMERY,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement RawB3 = {0x1bb8, Fr_LONGMONTGOMERY,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x0216d0b17f4e44a5}};



    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};
    FrRawElement pRawResult3_c = {0};

    pRawResult0_c[0] = Fr_toInt(&RawA);
    pRawResult1_c[0] = Fr_toInt(&RawA1);
    pRawResult2_c[0] = Fr_toInt(&RawA2);
    pRawResult3_c[0] = Fr_toInt(&RawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fr_toInt_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fr_toInt_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fr_toInt_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fr_toInt_unit_test");
}




// 1
void Fr_lt_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_s1s2_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lt_s1s2_unit_test()
{
    //Fr_lt_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_lt(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_lt(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_lt(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_lt_s1s2_unit_test");
}

// 2
void Fr_lt_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lt_l1nl2n_unit_test()
{
    //Fr_lt_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_lt(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_lt(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_lt(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_lt_l1nl2n_unit_test");
}

// 3
void Fr_lt_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lt_l1ml2n_unit_test()
{
    //Fr_lt_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_lt(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_lt(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_lt(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_lt_l1ml2n_unit_test");
}

// 4
void Fr_lt_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lt_l1ml2m_unit_test()
{
    //Fr_lt_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_lt(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_lt(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_lt(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_lt_l1ml2m_unit_test");
}

// 5
void Fr_lt_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lt_l1nl2m_unit_test()
{
    //Fr_lt_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_lt(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_lt(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_lt(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_lt_l1nl2m_unit_test");
}

// 6
void Fr_lt_s1l2m_unit_test()
{
    //Fr_lt_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_lt(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_lt(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_lt(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_lt_s1l2m_unit_test");
}

void Fr_lt_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_s1l2m_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_lt_l1ms2_unit_test()
{
    //Fr_lt_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_lt(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_lt(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_lt(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_lt_l1ms2_unit_test");
}

void Fr_lt_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1ms2_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_lt_l1ns2_unit_test()
{
    //Fr_lt_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_lt(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_lt(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_lt(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_lt_l1ns2_unit_test");
}

void Fr_lt_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_l1ns2_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_lt_s1l2n_unit_test()
{
    //Fr_lt_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_lt(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_lt(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_lt(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_lt_s1l2n_unit_test");
}

void Fr_lt_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lt_s1l2n_test " << idx << ": " <<  '\n';
    Fr_lt(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}



// 1
void Fr_geq_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_s1s2_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_geq_s1s2_unit_test()
{
    //Fr_geq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_geq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_geq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_geq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_geq_s1s2_unit_test");
}

// 2
void Fr_geq_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_geq_l1nl2n_unit_test()
{
    //Fr_geq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_geq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_geq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_geq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_geq_l1nl2n_unit_test");
}

// 3
void Fr_geq_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_geq_l1ml2n_unit_test()
{
    //Fr_geq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_geq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_geq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_geq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_geq_l1ml2n_unit_test");
}

// 4
void Fr_geq_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_geq_l1ml2m_unit_test()
{
    //Fr_geq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_geq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_geq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_geq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_geq_l1ml2m_unit_test");
}

// 5
void Fr_geq_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_geq_l1nl2m_unit_test()
{
    //Fr_geq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_geq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_geq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_geq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_geq_l1nl2m_unit_test");
}

// 6
void Fr_geq_s1l2m_unit_test()
{
    //Fr_geq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_geq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_geq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_geq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_geq_s1l2m_unit_test");
}

void Fr_geq_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_s1l2m_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_geq_l1ms2_unit_test()
{
    //Fr_geq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_geq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_geq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_geq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_geq_l1ms2_unit_test");
}

void Fr_geq_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1ms2_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_geq_l1ns2_unit_test()
{
    //Fr_geq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_geq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_geq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_geq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_geq_l1ns2_unit_test");
}

void Fr_geq_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_l1ns2_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_geq_s1l2n_unit_test()
{
    //Fr_geq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_geq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_geq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_geq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_geq_s1l2n_unit_test");
}

void Fr_geq_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_geq_s1l2n_test " << idx << ": " <<  '\n';
    Fr_geq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}



void Fr_neg_unit_test()
{
    //Fr_neg_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //FrElement pResult0= {0xffff5e10,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pResult0= {-41456,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neg_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {-41456,0x0,{0x0,0x0,0x0,0x0}};
    //FrElement pResult1= {0xffff5e10,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neg_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_neg_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neg(&Result0_c, &pA0);
    Fr_neg(&Result1_c, &pA1);
    Fr_neg(&Result2_c, &pA2);
    Fr_neg(&Result3_c, &pA3);

    compare_Result(&pResult0, &Result0_c, 0, "Fr_neg_unit_test");
    compare_Result(&pResult1, &Result1_c, 1, "Fr_neg_unit_test");
    compare_Result(&pResult2, &Result2_c, 2, "Fr_neg_unit_test");
    compare_Result(&pResult3, &Result3_c, 3, "Fr_neg_unit_test");
}

void Fr_neg_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neg_test " << idx << ": " <<  '\n';
    Fr_neg(pResult, pA);
    std::cout << "FrElement pA" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    //std::cout << "FrElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FrElement pResult" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}








// 1
void Fr_eq_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_s1s2_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_eq_s1s2_unit_test()
{
    //Fr_eq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_eq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_eq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_eq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_eq_s1s2_unit_test");
}

// 2
void Fr_eq_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_eq_l1nl2n_unit_test()
{
    //Fr_eq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_eq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_eq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_eq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_eq_l1nl2n_unit_test");
}

// 3
void Fr_eq_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_eq_l1ml2n_unit_test()
{
    //Fr_eq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_eq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_eq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_eq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_eq_l1ml2n_unit_test");
}

// 4
void Fr_eq_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_eq_l1ml2m_unit_test()
{
    //Fr_eq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_eq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_eq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_eq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_eq_l1ml2m_unit_test");
}

// 5
void Fr_eq_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_eq_l1nl2m_unit_test()
{
    //Fr_eq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_eq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_eq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_eq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_eq_l1nl2m_unit_test");
}

// 6
void Fr_eq_s1l2m_unit_test()
{
    //Fr_eq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_eq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_eq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_eq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_eq_s1l2m_unit_test");
}

void Fr_eq_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_s1l2m_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_eq_l1ms2_unit_test()
{
    //Fr_eq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_eq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_eq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_eq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_eq_l1ms2_unit_test");
}

void Fr_eq_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1ms2_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_eq_l1ns2_unit_test()
{
    //Fr_eq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_eq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_eq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_eq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_eq_l1ns2_unit_test");
}

void Fr_eq_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_l1ns2_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_eq_s1l2n_unit_test()
{
    //Fr_eq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_eq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_eq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_eq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_eq_s1l2n_unit_test");
}

void Fr_eq_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_eq_s1l2n_test " << idx << ": " <<  '\n';
    Fr_eq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}



// 1
void Fr_neq_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_s1s2_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_neq_s1s2_unit_test()
{
    //Fr_neq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_neq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_neq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_neq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_neq_s1s2_unit_test");
}

// 2
void Fr_neq_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_neq_l1nl2n_unit_test()
{
    //Fr_neq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_neq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_neq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_neq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_neq_l1nl2n_unit_test");
}

// 3
void Fr_neq_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_neq_l1ml2n_unit_test()
{
    //Fr_neq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_neq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_neq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_neq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_neq_l1ml2n_unit_test");
}

// 4
void Fr_neq_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_neq_l1ml2m_unit_test()
{
    //Fr_neq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_neq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_neq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_neq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_neq_l1ml2m_unit_test");
}

// 5
void Fr_neq_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_neq_l1nl2m_unit_test()
{
    //Fr_neq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_neq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_neq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_neq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_neq_l1nl2m_unit_test");
}

// 6
void Fr_neq_s1l2m_unit_test()
{
    //Fr_neq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_neq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_neq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_neq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_neq_s1l2m_unit_test");
}

void Fr_neq_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_s1l2m_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_neq_l1ms2_unit_test()
{
    //Fr_neq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_neq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_neq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_neq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_neq_l1ms2_unit_test");
}

void Fr_neq_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1ms2_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_neq_l1ns2_unit_test()
{
    //Fr_neq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_neq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_neq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_neq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_neq_l1ns2_unit_test");
}

void Fr_neq_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_l1ns2_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_neq_s1l2n_unit_test()
{
    //Fr_neq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_neq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_neq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_neq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_neq_s1l2n_unit_test");
}

void Fr_neq_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_neq_s1l2n_test " << idx << ": " <<  '\n';
    Fr_neq(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}



// 1
void Fr_gt_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_s1s2_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_gt_s1s2_unit_test()
{
    //Fr_gt_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_gt(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_gt(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_gt(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_gt_s1s2_unit_test");
}

// 2
void Fr_gt_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_gt_l1nl2n_unit_test()
{
    //Fr_gt_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_gt(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_gt(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_gt(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_gt_l1nl2n_unit_test");
}

// 3
void Fr_gt_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_gt_l1ml2n_unit_test()
{
    //Fr_gt_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_gt(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_gt(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_gt(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_gt_l1ml2n_unit_test");
}

// 4
void Fr_gt_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_gt_l1ml2m_unit_test()
{
    //Fr_gt_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_gt(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_gt(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_gt(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_gt_l1ml2m_unit_test");
}

// 5
void Fr_gt_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_gt_l1nl2m_unit_test()
{
    //Fr_gt_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_gt(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_gt(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_gt(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_gt_l1nl2m_unit_test");
}

// 6
void Fr_gt_s1l2m_unit_test()
{
    //Fr_gt_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_gt(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_gt(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_gt(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_gt_s1l2m_unit_test");
}

void Fr_gt_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_s1l2m_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_gt_l1ms2_unit_test()
{
    //Fr_gt_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_gt(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_gt(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_gt(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_gt_l1ms2_unit_test");
}

void Fr_gt_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1ms2_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_gt_l1ns2_unit_test()
{
    //Fr_gt_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_gt(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_gt(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_gt(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_gt_l1ns2_unit_test");
}

void Fr_gt_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_l1ns2_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_gt_s1l2n_unit_test()
{
    //Fr_gt_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_gt(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_gt(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_gt(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_gt_s1l2n_unit_test");
}

void Fr_gt_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_gt_s1l2n_test " << idx << ": " <<  '\n';
    Fr_gt(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}







// 1
void Fr_band_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_s1s2_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_band_s1s2_unit_test()
{
    //Fr_band_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1b0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x7fffffff,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_band(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_band(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_band(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_band_s1s2_unit_test");
}

// 2
void Fr_band_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_band_l1nl2n_unit_test()
{
    //Fr_band_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0x1b0e241a8000000,0x10183020205c1840,0x8c08021940808004,0x12003170084004}};
    //Fr_band_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0xbc1e0a6c0ffffffe,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_band(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_band(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_band(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_band_l1nl2n_unit_test");
}

// 3
void Fr_band_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_band_l1ml2n_unit_test()
{
    //Fr_band_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_band_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x80000000,{0x11b0240128216102,0x3ac283181105841,0x409020402210084,0x650801f4e4481}};
    //Fr_band_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_band(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_band(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_band(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_band_l1ml2n_unit_test");
}

// 4
void Fr_band_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_band_l1ml2m_unit_test()
{
    //Fr_band_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x80000000,{0x981300004920100c,0xce101c001c807,0x800409c00c301818,0x1c3f00100800018}};
    //Fr_band_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x80000000,{0x49424100927735a,0x22ac641189204809,0x442c22442821002e,0x40a51c01a06d50b}};
    //Fr_band_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_band(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_band(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_band(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_band_l1ml2m_unit_test");
}

// 5
void Fr_band_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_band_l1nl2m_unit_test()
{
    //Fr_band_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x80000000,{0xa090300848000000,0x141874041c408808,0x4428224b4040042e,0x80227011000d004}};
    //Fr_band_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_band(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_band(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_band(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_band_l1nl2m_unit_test");
}

// 6
void Fr_band_s1l2m_unit_test()
{
    //Fr_band_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x80000000,{0xa1f0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x80000000,{0xe6b4,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_band(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_band(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_band(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_band_s1l2m_unit_test");
}

void Fr_band_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_s1l2m_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_band_l1ms2_unit_test()
{
    //Fr_band_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x80000000,{0x1318,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x80000000,{0xe6b4,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_band(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_band(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_band(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_band_l1ms2_unit_test");
}

void Fr_band_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1ms2_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_band_l1ns2_unit_test()
{
    //Fr_band_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xffff,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_band(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_band(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_band(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_band_l1ns2_unit_test");
}

void Fr_band_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_l1ns2_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_band_s1l2n_unit_test()
{
    //Fr_band_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x21a0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0xffff,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_band(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_band(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_band(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_band_s1l2n_unit_test");
}

void Fr_band_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_band_s1l2n_test " << idx << ": " <<  '\n';
    Fr_band(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}




// 1
void Fr_land_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_s1s2_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_land_s1s2_unit_test()
{
    //Fr_land_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_land(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_land(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_land(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_land_s1s2_unit_test");
}

// 2
void Fr_land_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_land_l1nl2n_unit_test()
{
    //Fr_land_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_land(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_land(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_land(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_land_l1nl2n_unit_test");
}

// 3
void Fr_land_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_land_l1ml2n_unit_test()
{
    //Fr_land_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_land(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_land(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_land(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_land_l1ml2n_unit_test");
}

// 4
void Fr_land_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_land_l1ml2m_unit_test()
{
    //Fr_land_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_land(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_land(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_land(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_land_l1ml2m_unit_test");
}

// 5
void Fr_land_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_land_l1nl2m_unit_test()
{
    //Fr_land_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_land(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_land(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_land(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_land_l1nl2m_unit_test");
}

// 6
void Fr_land_s1l2m_unit_test()
{
    //Fr_land_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_land(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_land(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_land(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_land_s1l2m_unit_test");
}

void Fr_land_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_s1l2m_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_land_l1ms2_unit_test()
{
    //Fr_land_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_land(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_land(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_land(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_land_l1ms2_unit_test");
}

void Fr_land_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1ms2_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_land_l1ns2_unit_test()
{
    //Fr_land_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_land(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_land(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_land(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_land_l1ns2_unit_test");
}

void Fr_land_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_l1ns2_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_land_s1l2n_unit_test()
{
    //Fr_land_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_land(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_land(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_land(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_land_s1l2n_unit_test");
}

void Fr_land_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_land_s1l2n_test " << idx << ": " <<  '\n';
    Fr_land(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}



// 1
void Fr_lor_s1s2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_s1s2_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lor_s1s2_unit_test()
{
    //Fr_lor_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_lor(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_lor(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_lor(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fr_lor_s1s2_unit_test");
}

// 2
void Fr_lor_l1nl2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1nl2n_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lor_l1nl2n_unit_test()
{
    //Fr_lor_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_lor(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_lor(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_lor(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fr_lor_l1nl2n_unit_test");
}

// 3
void Fr_lor_l1ml2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1ml2n_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lor_l1ml2n_unit_test()
{
    //Fr_lor_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_lor(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_lor(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_lor(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fr_lor_l1ml2n_unit_test");
}

// 4
void Fr_lor_l1ml2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1ml2m_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lor_l1ml2m_unit_test()
{
    //Fr_lor_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_lor(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_lor(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_lor(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fr_lor_l1ml2m_unit_test");
}

// 5
void Fr_lor_l1nl2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1nl2m_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fr_lor_l1nl2m_unit_test()
{
    //Fr_lor_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_lor(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_lor(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_lor(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fr_lor_l1nl2m_unit_test");
}

// 6
void Fr_lor_s1l2m_unit_test()
{
    //Fr_lor_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_lor(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_lor(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_lor(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c, 0, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c, 1, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, 2, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c, 3, "Fr_lor_s1l2m_unit_test");
}

void Fr_lor_s1l2m_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_s1l2m_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

// 7
void Fr_lor_l1ms2_unit_test()
{
    //Fr_lor_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_lor(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_lor(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_lor(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c, 0, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c, 1, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c, 2, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, 3, "Fr_lor_l1ms2_unit_test");
}

void Fr_lor_l1ms2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1ms2_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1ms2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ms2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ms2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


// 8
void Fr_lor_l1ns2_unit_test()
{
    //Fr_lor_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_lor(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_lor(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_lor(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, 0, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, 1, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, 2, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c, 3, "Fr_lor_l1ns2_unit_test");
}

void Fr_lor_l1ns2_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_l1ns2_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_l1ns2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_l1ns2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_l1ns2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}
 // 9
void Fr_lor_s1l2n_unit_test()
{
    //Fr_lor_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_lor(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_lor(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_lor(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c, 0, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c, 1, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c, 2, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c, 3, "Fr_lor_s1l2n_unit_test");
}

void Fr_lor_s1l2n_test(PFrElement pResult, PFrElement pA, PFrElement pB, int idx)
{
    std::cout << "//Fr_lor_s1l2n_test " << idx << ": " <<  '\n';
    Fr_lor(pResult, pA, pB);
    std::cout << "FrElement pA_s1l2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pB_s1l2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FrElement pResult_s1l2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}






#endif

#if defined(TEST_FQ_C_FUNCTIONS) || defined(TEST_FQ_ASM_FUNCTIONS)
void compare_rawResult(FqRawElement pRawResult_asm, FqRawElement pRawResult_c, int idx, std::string TestName)
{
    if (pRawResult_asm[0] != pRawResult_c[0] ||
        pRawResult_asm[1] != pRawResult_c[1] ||
        pRawResult_asm[2] != pRawResult_c[2] ||
        pRawResult_asm[3] != pRawResult_c[3])
    {
        std::cout << TestName << idx << " failed!" << "\n";
    }
    else
    {
        std::cout << TestName << idx << " succeed!" << "\n";
    }
}

void compare_Result(PFqElement pResult_asm, PFqElement pResult_c, int idx, std::string TestName)
{
    if (pResult_asm->shortVal != pResult_c->shortVal     ||
        pResult_asm->longVal[0] != pResult_c->longVal[0] ||
        pResult_asm->longVal[1] != pResult_c->longVal[1] ||
        pResult_asm->longVal[2] != pResult_c->longVal[2] ||
        pResult_asm->longVal[3] != pResult_c->longVal[3])
    {
        std::cout << TestName << idx << " failed!" << "\n";
    }
    else
    {
        std::cout << TestName << idx << " succeed!" << "\n";
    }
}

void Fq_Rw_Neg_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fr_Rw_Neg_test " << idx << ": " <<  '\n';
    Fq_rawNeg(pRawResult, pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_Rw_Neg_unit_test()
{
    //Fr_Rw_Neg_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0x9a2f914ce07cfd47,0x367766d2b951244,0xdc2822db40c0ac2f,0x183227397098d014};
    //Fr_Rw_Neg_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x3c208c16d87cfd46,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x3c208c16d87cfd49,0x97816a916871ca8c,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0x3c208c16d87cfd49,0x97816a916871ca8e,0xb85045b68181585e,0x30644e72e131a02a};
    //Fr_Rw_Neg_test 5:
    FqRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FqRawElement pRawResult5= {0x0,0x0,0x0,0x0};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;
    FqRawElement pRawResult5_c;

    Fq_rawNeg(pRawResult0_c, pRawA0);
    Fq_rawNeg(pRawResult1_c, pRawA1);
    Fq_rawNeg(pRawResult2_c, pRawA2);
    Fq_rawNeg(pRawResult3_c, pRawA3);
    Fq_rawNeg(pRawResult5_c, pRawA5);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_Neg_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_Neg_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_Neg_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_Neg_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fq_Rw_Neg_unit_test");
}


void Fq_Rw_copy_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_copy_test " << idx << ": " <<  '\n';
    Fq_rawCopy(pRawResult, pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_Rw_copy_unit_test()
{
    //Fq_Rw_copy_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    //Fq_Rw_copy_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x1,0x0,0x0,0x0};
    //Fq_Rw_copy_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0xfffffffffffffffe,0x0,0x0,0x0};
    //Fq_Rw_copy_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;

    Fq_rawCopy(pRawResult0_c, pRawA0);
    Fq_rawCopy(pRawResult1_c, pRawA1);
    Fq_rawCopy(pRawResult2_c, pRawA2);
    Fq_rawCopy(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_copy_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_copy_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_copy_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_copy_unit_test");
}


void Fq_Rw_add_unit_test()
{
    //Fq_rawAdd Test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FqRawElement pRawResult0= {0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba};
    //Fq_rawAdd Test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x3,0x0,0x0,0x0};
    //Fq_rawAdd Test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0xfffffffffffffffd,0x1,0x0,0x0};
    //Fq_rawAdd Test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FqRawElement pRawResult3= {0xc3df73e9278302b6,0x687e956e978e3571,0x47afba497e7ea7a1,0xcf9bb18d1ece5fd5};
    //Fq_rawAdd Test 6:
    FqRawElement pRawA6= {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    FqRawElement pRawB6= {0x0,0x0,0x0,0x0};
    FqRawElement pRawResult6= {0x0,0x0,0x0,0x0};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;
    FqRawElement pRawResult6_c;

    Fq_rawAdd(pRawResult0_c, pRawA0, pRawB0);
    Fq_rawAdd(pRawResult1_c, pRawA1, pRawB1);
    Fq_rawAdd(pRawResult2_c, pRawA2, pRawB2);
    Fq_rawAdd(pRawResult3_c, pRawA3, pRawB3);
    Fq_rawAdd(pRawResult6_c, pRawA6, pRawB6);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_add_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_add_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_add_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_add_unit_test");
    compare_rawResult(pRawResult6, pRawResult6_c, 6, "Fq_Rw_add_unit_test");
}

void Fq_Rw_sub_unit_test()
{
    //Fq_Rw_sub_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FqRawElement pRawResult0= {0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f};
    //Fq_Rw_sub_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x3c208c16d87cfd46,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    //Fq_Rw_sub_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x3c208c16d87cfd46,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    //Fq_Rw_sub_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FqRawElement pRawResult3= {0x3c208c16d87cfd46,0x97816a916871ca8c,0xb85045b68181585c,0x30644e72e131a028};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;

    Fq_rawSub(pRawResult0_c, pRawA0, pRawB0);
    Fq_rawSub(pRawResult1_c, pRawA1, pRawB1);
    Fq_rawSub(pRawResult2_c, pRawA2, pRawB2);
    Fq_rawSub(pRawResult3_c, pRawA3, pRawB3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_sub_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_sub_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_sub_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_sub_unit_test");


}

void Fq_Rw_add_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_rawAdd Test " << idx << ": " <<  '\n';
    Fq_rawAdd(pRawResult, pRawA, pRawB);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fq_Rw_sub_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_sub_test " << idx << ": " <<  '\n';
    Fq_rawSub(pRawResult, pRawA, pRawB);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_Rw_sub_unit_test()
{
    //Fq_Rw_mul_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FqRawElement pRawResult0= {0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb};
    //Fq_Rw_mul_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49};
    //Fq_Rw_mul_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x1b332e37e22aea3c,0x6d7519cca22ac926,0xa2b9e2fdbc1f2a77,0x3058d8944ed69677};
    //Fq_Rw_mul_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FqRawElement pRawResult3= {0x1e51892c7f798de,0x49c1eec88964fb31,0xe7524f2299ec0ee2,0x337a0489fce7555};
    //Fq_Rw_mul_test 4:
    FqRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult4= {0xebb3da0ac591a7d2,0xdc19acc8059254c6,0xc31f14f32c65f257,0x373ff2663c811ac};
    //Fq_Rw_mul_test 5:
    FqRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FqRawElement pRawB5= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult5= {0x0,0x0,0x0,0x0};
    //Fq_Rw_mul_test 8:
    FqRawElement pRawA8= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB8= {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    FqRawElement pRawResult8= {0x0,0x0,0x0,0x0};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;
    FqRawElement pRawResult4_c;
    FqRawElement pRawResult5_c;
    FqRawElement pRawResult8_c;

    Fq_rawMMul(pRawResult0_c, pRawA0, pRawB0);
    Fq_rawMMul(pRawResult1_c, pRawA1, pRawB1);
    Fq_rawMMul(pRawResult2_c, pRawA2, pRawB2);
    Fq_rawMMul(pRawResult3_c, pRawA3, pRawB3);
    Fq_rawMMul(pRawResult4_c, pRawA4, pRawB4);
    Fq_rawMMul(pRawResult5_c, pRawA5, pRawB5);
    Fq_rawMMul(pRawResult8_c, pRawA8, pRawB8);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult4, pRawResult4_c, 4, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fq_Rw_mul_unit_test");
    compare_rawResult(pRawResult8, pRawResult8_c, 8, "Fq_Rw_mul_unit_test");
}

void Fq_Rw_mul_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_mul_test " << idx << ": " <<  '\n';
    Fq_rawMMul(pRawResult, pRawA, pRawB);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};" << '\n';
}


void Fq_Rw_Msquare_unit_test()
{
    //Fq_Rw_Msquare_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0xac0b6f222f67487d,0x364d764ea56127d9,0xe5ad1f8aa6ef1ae1,0x2dffef30a4034c35};
    //Fq_Rw_Msquare_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0xed84884a014afa37,0xeb2022850278edf8,0xcf63e9cfb74492d9,0x2e67157159e5c639};
    //Fq_Rw_Msquare_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0xcac67c2bcf3f94c9,0xb20d5c033f4b535e,0xad88b23a6703c471,0x3688947d16d07fa};
    //Fq_Rw_Msquare_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0x4c78ebc8ab4ce00d,0xdcbaf4c118eb7001,0x1c8e537a8c87e0f4,0x1fdf7ac5e6e8ec32};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;

    Fq_rawMSquare(pRawResult0_c, pRawA0);
    Fq_rawMSquare(pRawResult1_c, pRawA1);
    Fq_rawMSquare(pRawResult2_c, pRawA2);
    Fq_rawMSquare(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_Msquare_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_Msquare_unit_test");
}

void Fq_Rw_Msquare_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_Msquare_test " << idx << ": " <<  '\n';
    Fq_rawMSquare(pRawResult, pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_Rw_mul1_unit_test()
{
    //Fq_Rw_mul1_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FqRawElement pRawResult0= {0x8b363b7691ff055d,0xb5ada052b1165e8f,0x4b56ee9c6be00e25,0x2cb43dbcbe503199};
    //Fq_Rw_mul1_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49};
    //Fq_Rw_mul1_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x1b332e37e22aea3c,0x6d7519cca22ac926,0xa2b9e2fdbc1f2a77,0x3058d8944ed69677};
    //Fq_Rw_mul1_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FqRawElement pRawResult3= {0x95b6aeefa3f8e52,0x3bca00aff22ad49,0x78ca497c3a602fb9,0x217bf6416a170b5e};
    //Fq_Rw_mul1_test 9:
    FqRawElement pRawA9= {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    FqRawElement pRawB9= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult9= {0x0,0x0,0x0,0x0};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;
    FqRawElement pRawResult9_c;

    Fq_rawMMul1(pRawResult0_c, pRawA0, pRawB0[0]);
    Fq_rawMMul1(pRawResult1_c, pRawA1, pRawB1[0]);
    Fq_rawMMul1(pRawResult2_c, pRawA2, pRawB2[0]);
    Fq_rawMMul1(pRawResult3_c, pRawA3, pRawB3[0]);
    Fq_rawMMul1(pRawResult9_c, pRawA9, pRawB9[0]);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_mul1_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_mul1_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_mul1_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_mul1_unit_test");
    compare_rawResult(pRawResult9, pRawResult9_c, 9, "Fq_Rw_mul1_unit_test");
}

void Fq_Rw_mul1_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_mul1_test " << idx << ": " <<  '\n';
    Fq_rawMMul1(pRawResult, pRawA, pRawB[0]);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_Rw_ToMontgomery_unit_test()
{
    //Fq_Rw_ToMontgomery_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0x6a85f78919821592,0x49e80c88cd27dd10,0x386fe049d2e0e036,0xbf6322e9912c187};
    //Fq_Rw_ToMontgomery_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0xd35d438dc58f0d9d,0xa78eb28f5c70b3d,0x666ea36f7879462c,0xe0a77c19a07df2f};
    //Fq_Rw_ToMontgomery_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x86e3b42426baaaf0,0x6f40101ffae5e7b,0x8650e6f06c9181cb,0x546132966296a05};
    //Fq_Rw_ToMontgomery_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0x8898357aa26c8d3a,0xa38cd66a3a80dbbc,0xbe78fcfa9301038b,0x66c76b0259fe60};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;

    Fq_rawToMontgomery(pRawResult0_c, pRawA0);
    Fq_rawToMontgomery(pRawResult1_c, pRawA1);
    Fq_rawToMontgomery(pRawResult2_c, pRawA2);
    Fq_rawToMontgomery(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_ToMontgomery_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_ToMontgomery_unit_test");
}

void Fq_Rw_ToMontgomery_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_ToMontgomery_test " << idx << ": " <<  '\n';
    Fq_rawToMontgomery(pRawResult, pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_rawIsEq_test(uint64_t uRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_rawIsEq " << idx << ": " <<  '\n';
    uRawResult = Fq_rawIsEq(pRawA, pRawB);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< uRawResult << "};"<< '\n';// << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fq_Rw_IsEq_unit_test()
{
    //Fq_rawIsEq 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FqRawElement pRawResult0= {0x0};
    //Fq_rawIsEq 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x0};
    //Fq_rawIsEq 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x0};
    //Fq_rawIsEq 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FqRawElement pRawResult3= {0x0};
    //Fq_rawIsEq 7:
    FqRawElement pRawA7= {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    FqRawElement pRawB7= {0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029};
    FqRawElement pRawResult7= {0x1};

    FqRawElement pRawResult0_c = {0};
    FqRawElement pRawResult1_c = {0};
    FqRawElement pRawResult2_c = {0};
    FqRawElement pRawResult3_c = {0};
    FqRawElement pRawResult7_c = {0};

    pRawResult0_c[0] = Fq_rawIsEq(pRawA0, pRawB0);
    pRawResult1_c[0] = Fq_rawIsEq(pRawA1, pRawB1);
    pRawResult2_c[0] = Fq_rawIsEq(pRawA2, pRawB2);
    pRawResult3_c[0] = Fq_rawIsEq(pRawA3, pRawB3);
    pRawResult7_c[0] = Fq_rawIsEq(pRawA7, pRawB7);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_IsEq_unit_test");
    compare_rawResult(pRawResult7, pRawResult7_c, 7, "Fq_Rw_IsEq_unit_test");
}


void Fq_rawIsZero_test(uint64_t uRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_rawIsZero_test " << idx << ": " <<  '\n';
    uRawResult = Fq_rawIsZero(pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< uRawResult << "};"<< '\n';// << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}


void Fq_rawIsZero_unit_test()
{
    //Fq_rawIsZero_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0x0};
    //Fq_rawIsZero_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0x0};
    //Fq_rawIsZero_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x0};
    //Fq_rawIsZero_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0x0};
    //Fq_rawIsZero_test 5:
    FqRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FqRawElement pRawResult5= {0x1};

    FqRawElement pRawResult0_c = {0};
    FqRawElement pRawResult1_c = {0};
    FqRawElement pRawResult2_c = {0};
    FqRawElement pRawResult3_c = {0};
    FqRawElement pRawResult5_c = {0};

    pRawResult0_c[0] = Fq_rawIsZero(pRawA0);
    pRawResult1_c[0] = Fq_rawIsZero(pRawA1);
    pRawResult2_c[0] = Fq_rawIsZero(pRawA2);
    pRawResult3_c[0] = Fq_rawIsZero(pRawA3);
    pRawResult5_c[0] = Fq_rawIsZero(pRawA5);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_rawIsZero_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_rawIsZero_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_rawIsZero_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_rawIsZero_unit_test");
    compare_rawResult(pRawResult5, pRawResult5_c, 5, "Fq_rawIsZero_unit_test");
}

void Fq_Rw_FromMontgomery_unit_test()
{
    //Fq_Rw_FromMontgomery_test 0:
    FqRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FqRawElement pRawResult0= {0xf245ae79cebd048,0x6b3ef4a83ac6acff,0xa9c9ec7ebdf450e,0x240191410e7c4b2a};
    //Fq_Rw_FromMontgomery_test 1:
    FqRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FqRawElement pRawResult1= {0xed84884a014afa37,0xeb2022850278edf8,0xcf63e9cfb74492d9,0x2e67157159e5c639};
    //Fq_Rw_FromMontgomery_test 2:
    FqRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FqRawElement pRawResult2= {0x506cb20c12eb5573,0xbb67bdc962df75c7,0xf53130c3551b6605,0x2cf04f4c7d698e7c};
    //Fq_Rw_FromMontgomery_test 3:
    FqRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FqRawElement pRawResult3= {0x121f6855ad310d9b,0x21ee6f188a0865f2,0x3fbf1ab5ddb67cc1,0x418a171f094820a};

    FqRawElement pRawResult0_c;
    FqRawElement pRawResult1_c;
    FqRawElement pRawResult2_c;
    FqRawElement pRawResult3_c;

    Fq_rawFromMontgomery(pRawResult0_c, pRawA0);
    Fq_rawFromMontgomery(pRawResult1_c, pRawA1);
    Fq_rawFromMontgomery(pRawResult2_c, pRawA2);
    Fq_rawFromMontgomery(pRawResult3_c, pRawA3);

    compare_rawResult(pRawResult0, pRawResult0_c, 0, "Fq_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult1, pRawResult1_c, 1, "Fq_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult2, pRawResult2_c, 2, "Fq_Rw_FromMontgomery_unit_test");
    compare_rawResult(pRawResult3, pRawResult3_c, 3, "Fq_Rw_FromMontgomery_unit_test");
}

void Fq_Rw_FromMontgomery_test(FqRawElement pRawResult, FqRawElement pRawA, FqRawElement pRawB, int idx)
{
    std::cout << "//Fq_Rw_FromMontgomery_test " << idx << ": " <<  '\n';
    Fq_rawFromMontgomery(pRawResult, pRawA);
    std::cout << "FqRawElement pRawA" << idx << "= " << std::hex << "{0x" << pRawA[0] << ",0x" << pRawA[1] << ",0x" << pRawA[2] << ",0x" << pRawA[3] << "};"<< '\n';
    //std::cout << "FqRawElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqRawElement pRawResult" << idx << "= " << std::hex << "{0x"<< pRawResult[0] << ",0x" << pRawResult[1] << ",0x" << pRawResult[2] << ",0x" << pRawResult[3] << "};"<< '\n';
}

void Fq_toNormal_unit_test()
{
    //Fq_toNormal_test 0:
    FqElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pResult0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fq_toNormal_test 1:
    FqElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pResult1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fq_toNormal_test 2:
    FqElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fq_toNormal_test 3:
    FqElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pResult3= {0x0,0x80000000,{0xf245ae79cebd048,0x6b3ef4a83ac6acff,0xa9c9ec7ebdf450e,0x240191410e7c4b2a}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_toNormal(&Result0_c, &pA0);
    Fq_toNormal(&Result1_c, &pA1);
    Fq_toNormal(&Result2_c, &pA2);
    Fq_toNormal(&Result3_c, &pA3);

    compare_Result(&pResult0, &Result0_c, 0, "Fq_toNormal_unit_test");
    compare_Result(&pResult1, &Result1_c, 1, "Fq_toNormal_unit_test");
    compare_Result(&pResult2, &Result2_c, 2, "Fq_toNormal_unit_test");
    compare_Result(&pResult3, &Result3_c, 3, "Fq_toNormal_unit_test");
}

void Fq_toNormal_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_toNormal_test " << idx << ": " <<  '\n';
    Fq_toNormal(pResult, pA);
    std::cout << "FqElement pA" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    //std::cout << "FqElement pRawB" << idx << "= " << std::hex << "{0x" << pRawB[0] << ",0x" << pRawB[1] << ",0x" << pRawB[2] << ",0x" << pRawB[3] << "};"<< '\n';
    std::cout << "FqElement pResult" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}





void Fq_mul_s1s2_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_s1s2_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_s1s2" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_s1s2" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_s1s2" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_s1s2_unit_test()
{
    //Fq_mul_s1s2_test 0:
    FqElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1s20= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fq_mul_s1s2_test 1:
    FqElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1s21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_s1s2_test 2:
    FqElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1s22= {0x0,0x80000000,{0x1188b480,0x0,0x0,0x0}};
    //Fq_mul_s1s2_test 3:
    FqElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1s23= {0x0,0x80000000,{0x3fffffff00000001,0x0,0x0,0x0}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fq_mul(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fq_mul(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fq_mul(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, 0, "Fq_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, 1, "Fq_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, 2, "Fq_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, 3, "Fq_mul_s1s2_unit_test");
}

void Fq_mul_l1nl2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1nl2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_l1nl2n_unit_test()
{
    //Fq_mul_l1nl2n_test 0:
    FqElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1nl2n0= {0x0,0xc0000000,{0xa6ba871b8b1e1b3a,0x14f1d651eb8e167b,0xccdd46def0f28c58,0x1c14ef83340fbe5e}};
    //Fq_mul_l1nl2n_test 1:
    FqElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1nl2n_test 2:
    FqElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1nl2n2= {0x0,0xc0000000,{0xcf8964868a91901b,0x7a6a901fa0148d8,0x4db71dbbc02a5dd1,0x16d1da0bfe7853b1}};
    //Fq_mul_l1nl2n_test 3:
    FqElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1nl2n3= {0x0,0xc0000000,{0xe41f9cbef04da0d3,0x688ae85d2304ac,0x96aa7c6cf3ab1e4f,0x1e0b0a49c35b0816}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fq_mul(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fq_mul(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fq_mul(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, 0, "Fq_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, 1, "Fq_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, 2, "Fq_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, 3, "Fq_mul_l1nl2n_unit_test");
}

void Fq_mul_l1ml2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ml2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_l1ml2n_unit_test()
{
    //Fq_mul_l1ml2n_test 0:
    FqElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ml2n0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1ml2n_test 1:
    FqElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ml2n_test 2:
    FqElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ml2n2= {0x0,0x80000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_l1ml2n_test 3:
    FqElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1ml2n3= {0x0,0x80000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fq_mul(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fq_mul(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fq_mul(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c, 0, "Fq_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c, 1, "Fq_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c, 2, "Fq_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c, 3, "Fq_mul_l1ml2n_unit_test");
}


void Fq_mul_l1ml2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ml2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_l1ml2m_unit_test()
{
    //Fq_mul_l1ml2m_test 0:
    FqElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ml2m0= {0x0,0xc0000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1ml2m_test 1:
    FqElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ml2m_test 2:
    FqElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ml2m2= {0x0,0xc0000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_l1ml2m_test 3:
    FqElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1ml2m3= {0x0,0xc0000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fq_mul(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fq_mul(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fq_mul(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c, 0, "Fq_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c, 1, "Fq_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c, 2, "Fq_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c, 3, "Fq_mul_l1ml2m_unit_test");
}

void Fq_mul_l1nl2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1nl2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_l1nl2m_unit_test()
{
    //Fq_mul_l1nl2m_test 0:
    //Fq_mul_l1nl2m_test 0:
    FqElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1nl2m0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1nl2m_test 1:
    FqElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1nl2m_test 2:
    FqElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1nl2m2= {0x0,0x80000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_l1nl2m_test 3:
    FqElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1nl2m3= {0x0,0x80000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fq_mul(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fq_mul(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fq_mul(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c, 0, "Fq_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c, 1, "Fq_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c, 2, "Fq_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c, 3, "Fq_mul_l1nl2m_unit_test");
}

void Fq_mul_l1ns2n_unit_test()
{
    //Fq_mul_l1ns2n_test 0:
    FqElement pA_l1ns2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ns2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ns2n0= {0x0,0xc0000000,{0xa6ba871b8b1e1b3a,0x14f1d651eb8e167b,0xccdd46def0f28c58,0x1c14ef83340fbe5e}};
    //Fq_mul_l1ns2n_test 1:
    FqElement pA_l1ns2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ns2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ns2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ns2n_test 2:
    FqElement pA_l1ns2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ns2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ns2n2= {0x0,0xc0000000,{0xba658bb3c5668e7a,0x8b6747b10d51d35a,0x871359d9f90f6f90,0xfd7c8811e0fe4b}};
    //Fq_mul_l1ns2n_test 3:
    FqElement pA_l1ns2n3= {0x7fffffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1ns2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1ns2n3= {0x0,0xc0000000,{0xe030473272041314,0x5491d21721820941,0x1ec384706e37c635,0x731d84fcf4faa10}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ns2n0, &pB_l1ns2n0);
    Fq_mul(&Result1_c, &pA_l1ns2n1, &pB_l1ns2n1);
    Fq_mul(&Result2_c, &pA_l1ns2n2, &pB_l1ns2n2);
    Fq_mul(&Result3_c, &pA_l1ns2n3, &pB_l1ns2n3);

    compare_Result(&pResult_l1ns2n0, &Result0_c, 0, "Fq_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n1, &Result1_c, 1, "Fq_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n2, &Result2_c, 2, "Fq_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n3, &Result3_c, 3, "Fq_mul_l1ns2n_unit_test");
}

void Fq_mul_l1ns2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ns2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ns2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ns2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ns2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_s1nl2n_unit_test()
{
    //Fq_mul_s1nl2n_test 0:
    FqElement pA_s1nl2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FqElement pB_s1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1nl2n0= {0x0,0xc0000000,{0xa6ba871b8b1e1b3a,0x14f1d651eb8e167b,0xccdd46def0f28c58,0x1c14ef83340fbe5e}};
    //Fq_mul_s1nl2n_test 1:
    FqElement pA_s1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FqElement pB_s1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_s1nl2n_test 2:
    FqElement pA_s1nl2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1nl2n2= {0x0,0xc0000000,{0xa1ebd3b0c50a79a5,0x991c1c5109e913a5,0x556dc7319816b73,0x12e84d0df59a5777}};
    //Fq_mul_s1nl2n_test 3:
    FqElement pA_s1nl2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_s1nl2n3= {0x7fffffff,0x80000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FqElement pResult_s1nl2n3= {0x0,0xc0000000,{0xf7d471598746b6aa,0xc5baff5c4b315cae,0x5913c7393800d697,0x3030eabd6004a0f9}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_s1nl2n0, &pB_s1nl2n0);
    Fq_mul(&Result1_c, &pA_s1nl2n1, &pB_s1nl2n1);
    Fq_mul(&Result2_c, &pA_s1nl2n2, &pB_s1nl2n2);
    Fq_mul(&Result3_c, &pA_s1nl2n3, &pB_s1nl2n3);

    compare_Result(&pResult_s1nl2n0, &Result0_c, 0, "Fq_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n1, &Result1_c, 1, "Fq_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n2, &Result2_c, 2, "Fq_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n3, &Result3_c, 3, "Fq_mul_s1nl2n_unit_test");
}

void Fq_mul_s1nl2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_s1nl2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_s1nl2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_s1nl2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_s1nl2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_s1nl2m_unit_test()
{
    //Fq_mul_s1nl2m_test 0:
    FqElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FqElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1nl2m0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_s1nl2m_test 1:
    FqElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FqElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_s1nl2m_test 2:
    FqElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1nl2m2= {0x0,0x80000000,{0xf8fb48ccc33018d3,0xc94964a5af8c4718,0x1a3ee6c0af9b914e,0x137994681281dfa3}};
    //Fq_mul_s1nl2m_test 3:
    FqElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FqElement pResult_s1nl2m3= {0x0,0x80000000,{0x950091e095a5f7d6,0x3ac97dbc6f34b24d,0xbc48958051e56dce,0x1625d680784e8f0f}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fq_mul(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fq_mul(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fq_mul(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c, 0, "Fq_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c, 1, "Fq_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c, 2, "Fq_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c, 3, "Fq_mul_s1nl2m_unit_test");
}

void Fq_mul_s1nl2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_s1nl2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_s1nl2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_s1nl2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_s1nl2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fq_mul_l1ms2n_unit_test()
{
    //Fq_mul_l1ms2n_test 0:
    FqElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ms2n0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1ms2n_test 1:
    FqElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ms2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ms2n_test 2:
    FqElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ms2n2= {0x0,0x80000000,{0xd48ef8eb6f0a70a7,0x83590aa4708b6780,0x6603a7198a84f5b5,0x27049057c6edb906}};
    //Fq_mul_l1ms2n_test 3:
    FqElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FqElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FqElement pResult_l1ms2n3= {0x0,0x80000000,{0x950091e095a5f7d6,0x3ac97dbc6f34b24d,0xbc48958051e56dce,0x1625d680784e8f0f}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fq_mul(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fq_mul(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fq_mul(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c, 0, "Fq_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c, 1, "Fq_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c, 2, "Fq_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c, 3, "Fq_mul_l1ms2n_unit_test");
}

void Fq_mul_l1ms2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ms2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ms2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ms2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ms2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fq_mul_l1ns2m_unit_test()
{
    //Fq_mul_l1ns2m_test 0:
    FqElement pA_l1ns2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ns2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ns2m0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1ns2m_test 1:
    FqElement pA_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ns2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ns2m_test 2:
    FqElement pA_l1ns2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ns2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ns2m2= {0x0,0x80000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_l1ns2m_test 3:
    FqElement pA_l1ns2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1ns2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1ns2m3= {0x0,0x80000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ns2m0, &pB_l1ns2m0);
    Fq_mul(&Result1_c, &pA_l1ns2m1, &pB_l1ns2m1);
    Fq_mul(&Result2_c, &pA_l1ns2m2, &pB_l1ns2m2);
    Fq_mul(&Result3_c, &pA_l1ns2m3, &pB_l1ns2m3);

    compare_Result(&pResult_l1ns2m0, &Result0_c, 0, "Fq_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m1, &Result1_c, 1, "Fq_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m2, &Result2_c, 2, "Fq_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m3, &Result3_c, 3, "Fq_mul_l1ns2m_unit_test");
}

void Fq_mul_l1ns2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ns2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ns2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ns2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ns2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_l1ms2m_unit_test()
{
    //Fq_mul_l1ms2m_test 0:
    FqElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ms2m0= {0x0,0xc0000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_l1ms2m_test 1:
    FqElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_l1ms2m_test 2:
    FqElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_l1ms2m2= {0x0,0xc0000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_l1ms2m_test 3:
    FqElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_l1ms2m3= {0x0,0xc0000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fq_mul(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fq_mul(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fq_mul(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c, 0, "Fq_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c, 1, "Fq_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c, 2, "Fq_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c, 3, "Fq_mul_l1ms2m_unit_test");
}

void Fq_mul_l1ms2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_l1ms2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_l1ms2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_l1ms2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_l1ms2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}


void Fq_mul_s1ml2m_unit_test()
{
    //Fq_mul_s1ml2m_test 0:
    FqElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1ml2m0= {0x0,0xc0000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_s1ml2m_test 1:
    FqElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_s1ml2m_test 2:
    FqElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1ml2m2= {0x0,0xc0000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_s1ml2m_test 3:
    FqElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_s1ml2m3= {0x0,0xc0000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fq_mul(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fq_mul(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fq_mul(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c, 0, "Fq_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c, 1, "Fq_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c, 2, "Fq_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c, 3, "Fq_mul_s1ml2m_unit_test");
}

void Fq_mul_s1ml2m_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_s1ml2m_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_s1ml2m" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_s1ml2m" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_s1ml2m" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

void Fq_mul_s1ml2n_unit_test()
{
    //Fq_mul_s1ml2n_test 0:
    FqElement pA_s1ml2n0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FqElement pB_s1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1ml2n0= {0x0,0x80000000,{0x9ee8847d2a18f727,0x3ebeda789c801164,0xe6778de8ed07cd56,0x2c69dc6fd299ec49}};
    //Fq_mul_s1ml2n_test 1:
    FqElement pA_s1ml2n1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FqElement pB_s1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FqElement pResult_s1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fq_mul_s1ml2n_test 2:
    FqElement pA_s1ml2n2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FqElement pB_s1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FqElement pResult_s1ml2n2= {0x0,0x80000000,{0x1187da3e296269a8,0xd0139eb206e57eeb,0xdb5973382f0e9301,0x2e40d99a3c8089fb}};
    //Fq_mul_s1ml2n_test 3:
    FqElement pA_s1ml2n3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pB_s1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FqElement pResult_s1ml2n3= {0x0,0x80000000,{0xc5687d1b9df6a369,0xbf4f15d4ad74848f,0x3e250df1ad65c620,0x55308b909171d71}};

    FqElement Result0_c = {0,0,{0,0,0,0}};
    FqElement Result1_c = {0,0,{0,0,0,0}};
    FqElement Result2_c= {0,0,{0,0,0,0}};
    FqElement Result3_c= {0,0,{0,0,0,0}};

    Fq_mul(&Result0_c, &pA_s1ml2n0, &pB_s1ml2n0);
    Fq_mul(&Result1_c, &pA_s1ml2n1, &pB_s1ml2n1);
    Fq_mul(&Result2_c, &pA_s1ml2n2, &pB_s1ml2n2);
    Fq_mul(&Result3_c, &pA_s1ml2n3, &pB_s1ml2n3);

    compare_Result(&pResult_s1ml2n0, &Result0_c, 0, "Fq_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n1, &Result1_c, 1, "Fq_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n2, &Result2_c, 2, "Fq_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n3, &Result3_c, 3, "Fq_mul_s1ml2n_unit_test");
}

void Fq_mul_s1ml2n_test(PFqElement pResult, PFqElement pA, PFqElement pB, int idx)
{
    std::cout << "//Fq_mul_s1ml2n_test " << idx << ": " <<  '\n';
    Fq_mul(pResult, pA, pB);
    std::cout << "FqElement pA_s1ml2n" << idx << "= " << std::hex << "{0x" << pA->shortVal << ",0x" << pA->type << ",{0x" << pA->longVal[0] << ",0x" << pA->longVal[1] << ",0x" << pA->longVal[2] << ",0x" << pA->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pB_s1ml2n" << idx << "= " << std::hex << "{0x" << pB->shortVal << ",0x" << pB->type << ",{0x" << pB->longVal[0] << ",0x" << pB->longVal[1] << ",0x" << pB->longVal[2] << ",0x" << pB->longVal[3] << "}};"<< '\n';
    std::cout << "FqElement pResult_s1ml2n" << idx << "= " << std::hex << "{0x" << pResult->shortVal << ",0x" << pResult->type << ",{0x" << pResult->longVal[0] << ",0x" << pResult->longVal[1] << ",0x" << pResult->longVal[2] << ",0x" << pResult->longVal[3] << "}};"<< '\n';
}

#endif


int main()
{

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_add_unit_test();
//    Fr_Rw_add_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_add_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_add_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_add_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_add_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_add_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_add_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_add_test(pRawResult3, pRawA3, pRawB3, 3);
    Fr_Rw_add_test(pRawResult6, pRawA6, pRawB6, 6);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_sub_unit_test();
//    Fr_Rw_sub_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_sub_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_sub_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_sub_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_sub_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_sub_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_sub_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_sub_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_copy_unit_test();
//    Fr_Rw_copy_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_copy_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_copy_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_copy_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_copy_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_copy_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_copy_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_copy_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_Neg_unit_test();
//    Fr_Rw_Neg_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_Neg_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_Neg_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_Neg_test(pRawResult3, pRawA3, pRawB3, 3);
//    Fr_Rw_Neg_test(pRawResult5, pRawA5, pRawB5, 5);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_Neg_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_Neg_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_Neg_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_Neg_test(pRawResult3, pRawA3, pRawB3, 3);
    Fr_Rw_Neg_test(pRawResult5, pRawA5, pRawB5, 5);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_mul_unit_test();
//    Fr_Rw_mul_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_mul_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_mul_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_mul_test(pRawResult3, pRawA3, pRawB3, 3);
//    Fr_Rw_mul_test(pRawResult4, pRawA4, pRawB4, 4);
//    Fr_Rw_mul_test(pRawResult5, pRawA5, pRawB5, 5);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_mul_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_mul_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_mul_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_mul_test(pRawResult3, pRawA3, pRawB3, 3);
    Fr_Rw_mul_test(pRawResult4, pRawA4, pRawB4, 4);
    Fr_Rw_mul_test(pRawResult5, pRawA5, pRawB5, 5);
    Fr_Rw_mul_test(pRawResult8, pRawA8, pRawB8, 8);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_Msquare_unit_test();
//    Fr_Rw_Msquare_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_Msquare_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_Msquare_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_Msquare_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_Msquare_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_Msquare_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_Msquare_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_Msquare_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_mul1_unit_test();
//    Fr_Rw_mul1_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_mul1_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_mul1_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_mul1_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_mul1_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_mul1_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_mul1_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_mul1_test(pRawResult3, pRawA3, pRawB3, 3);
    Fr_Rw_mul1_test(pRawResult9, pRawA9, pRawB9, 9);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_ToMontgomery_unit_test();
//    Fr_Rw_ToMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_ToMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_ToMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_ToMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_ToMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_ToMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_ToMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_ToMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_IsEq_unit_test();
//    Fr_rawIsEq_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_rawIsEq_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_rawIsEq_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_rawIsEq_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_rawIsEq_test(uRawResult,  pRawA,  pRawB, 0);
    Fr_rawIsEq_test(uRawResult1, pRawA1, pRawB1, 1);
    Fr_rawIsEq_test(uRawResult2, pRawA2, pRawB2, 2);
    Fr_rawIsEq_test(uRawResult3, pRawA3, pRawB3, 3);
    Fr_rawIsEq_test(uRawResult7, pRawA7, pRawB7, 7);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_rawIsZero_unit_test();
//    Fr_rawIsZero_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_rawIsZero_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_rawIsZero_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_rawIsZero_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_rawIsZero_test(uRawResult,  pRawA,  pRawB, 0);
    Fr_rawIsZero_test(uRawResult1, pRawA1, pRawB1, 1);
    Fr_rawIsZero_test(uRawResult2, pRawA2, pRawB2, 2);
    Fr_rawIsZero_test(uRawResult3, pRawA3, pRawB3, 3);
    Fr_rawIsZero_test(uRawResult5, pRawA5, pRawB5, 5);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_Rw_FromMontgomery_unit_test();
//    Fr_Rw_FromMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_Rw_FromMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_Rw_FromMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_Rw_FromMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_Rw_FromMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
    Fr_Rw_FromMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
    Fr_Rw_FromMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
    Fr_Rw_FromMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_toNormal_unit_test();
//    Fr_toNormal_test(&RawResult,  &RawA,  &RawB, 0);
//    Fr_toNormal_test(&RawResult1, &RawA1, &RawB1, 1);
//    Fr_toNormal_test(&RawResult2, &RawA2, &RawB2, 2);
//    Fr_toNormal_test(&RawResult3, &RawA3, &RawB3, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_toNormal_test(&RawResult,  &RawA,  &RawB, 0);
    Fr_toNormal_test(&RawResult1, &RawA1, &RawB1, 1);
    Fr_toNormal_test(&RawResult2, &RawA2, &RawB2, 2);
    Fr_toNormal_test(&RawResult3, &RawA3, &RawB3, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_s1s2_unit_test();
//    Fr_mul_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
//    Fr_mul_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
//    Fr_mul_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
//    Fr_mul_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_mul_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_mul_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_mul_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1nl2n_unit_test();
//    Fr_mul_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
//    Fr_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
//    Fr_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
//    Fr_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_mul_l1ml2n_unit_test();
//    Fr_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fr_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fr_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fr_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1ml2m_unit_test();
//    Fr_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fr_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fr_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fr_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_mul_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_mul_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_mul_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1nl2m_unit_test();
//    Fr_mul_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fr_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fr_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fr_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_mul_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_mul_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_mul_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1ns2n_unit_test();
//    Fr_mul_l1ns2n_test(&Result_l1ns2n,  &A_l1ns2n,  &B_l1ns2n, 0);
//    Fr_mul_l1ns2n_test(&Result1_l1ns2n, &A1_l1ns2n, &B1_l1ns2n, 1);
//    Fr_mul_l1ns2n_test(&Result2_l1ns2n, &A2_l1ns2n, &B2_l1ns2n, 2);
//    Fr_mul_l1ns2n_test(&Result3_l1ns2n, &A3_l1ns2n, &B3_l1ns2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ns2n_test(&Result_l1ns2n,  &A_l1ns2n,  &B_l1ns2n, 0);
    Fr_mul_l1ns2n_test(&Result1_l1ns2n, &A1_l1ns2n, &B1_l1ns2n, 1);
    Fr_mul_l1ns2n_test(&Result2_l1ns2n, &A2_l1ns2n, &B2_l1ns2n, 2);
    Fr_mul_l1ns2n_test(&Result3_l1ns2n, &A3_l1ns2n, &B3_l1ns2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_s1nl2n_unit_test();
//    Fr_mul_s1nl2n_test(&Result_s1nl2n,   &A_s1nl2n,   &B_s1nl2n, 0);
//    Fr_mul_s1nl2n_test(&Result1_s1nl2n,  &A1_s1nl2n,  &B1_s1nl2n, 1);
//    Fr_mul_s1nl2n_test(&Result2_s1nl2n,  &A2_s1nl2n,  &B2_s1nl2n, 2);
//    Fr_mul_s1nl2n_test(&Result3_s1nl2n,  &A3_s1nl2n,  &B3_s1nl2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_s1nl2n_test(&Result_s1nl2n,   &A_s1nl2n,   &B_s1nl2n, 0);
    Fr_mul_s1nl2n_test(&Result1_s1nl2n,  &A1_s1nl2n,  &B1_s1nl2n, 1);
    Fr_mul_s1nl2n_test(&Result2_s1nl2n,  &A2_s1nl2n,  &B2_s1nl2n, 2);
    Fr_mul_s1nl2n_test(&Result3_s1nl2n,  &A3_s1nl2n,  &B3_s1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_s1nl2m_unit_test();
//    Fr_mul_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
//    Fr_mul_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
//    Fr_mul_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
//    Fr_mul_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fr_mul_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fr_mul_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fr_mul_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1ms2n_unit_test();
//    Fr_mul_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ns2n, 0);
//    Fr_mul_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ns2n, 1);
//    Fr_mul_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ns2n, 2);
//    Fr_mul_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ns2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ms2n, 0);
    Fr_mul_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ms2n, 1);
    Fr_mul_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ms2n, 2);
    Fr_mul_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ms2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1ns2m_unit_test();
//    Fr_mul_l1ns2m_test(&Result_l1ns2m,  &A_l1ns2m,  &B_l1ns2m, 0);
//    Fr_mul_l1ns2m_test(&Result1_l1ns2m, &A1_l1ns2m, &B1_l1ns2m, 1);
//    Fr_mul_l1ns2m_test(&Result2_l1ns2m, &A2_l1ns2m, &B2_l1ns2m, 2);
//    Fr_mul_l1ns2m_test(&Result3_l1ns2m, &A3_l1ns2m, &B3_l1ns2m, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ns2m_test(&Result_l1ns2m,  &A_l1ns2m,  &B_l1ns2m, 0);
    Fr_mul_l1ns2m_test(&Result1_l1ns2m, &A1_l1ns2m, &B1_l1ns2m, 1);
    Fr_mul_l1ns2m_test(&Result2_l1ns2m, &A2_l1ns2m, &B2_l1ns2m, 2);
    Fr_mul_l1ns2m_test(&Result3_l1ns2m, &A3_l1ns2m, &B3_l1ns2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_l1ms2m_unit_test();
//    Fr_mul_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
//    Fr_mul_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
//    Fr_mul_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
//    Fr_mul_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fr_mul_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fr_mul_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fr_mul_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_s1ml2m_unit_test();
//    Fr_mul_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
//    Fr_mul_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
//    Fr_mul_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
//    Fr_mul_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fr_mul_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fr_mul_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fr_mul_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_mul_s1ml2n_unit_test();
//    Fr_mul_s1ml2n_test(&Result_s1ml2n,   &A_s1ml2n,   &B_s1ml2n, 0);
//    Fr_mul_s1ml2n_test(&Result1_s1ml2n,  &A1_s1ml2n,  &B1_s1ml2n, 1);
//    Fr_mul_s1ml2n_test(&Result2_s1ml2n,  &A2_s1ml2n,  &B2_s1ml2n, 2);
//    Fr_mul_s1ml2n_test(&Result3_s1ml2n,  &A3_s1ml2n,  &B3_s1ml2n, 3);
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_mul_s1ml2n_test(&Result_s1ml2n,   &A_s1ml2n,   &B_s1ml2n, 0);
    Fr_mul_s1ml2n_test(&Result1_s1ml2n,  &A1_s1ml2n,  &B1_s1ml2n, 1);
    Fr_mul_s1ml2n_test(&Result2_s1ml2n,  &A2_s1ml2n,  &B2_s1ml2n, 2);
    Fr_mul_s1ml2n_test(&Result3_s1ml2n,  &A3_s1ml2n,  &B3_s1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_sub_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_sub_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_sub_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_sub_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_sub_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_sub_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_sub_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_sub_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_sub_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_sub_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_sub_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_sub_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_sub_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_sub_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_sub_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_sub_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_sub_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_sub_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_sub_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_sub_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_sub_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_sub_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_sub_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_sub_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_sub_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_sub_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_sub_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_sub_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_sub_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_sub_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_sub_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_s1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fr_sub_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fr_sub_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fr_sub_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fr_sub_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fr_sub_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fr_sub_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1ms2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ns2n, 0);
    Fr_sub_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ns2n, 1);
    Fr_sub_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ns2n, 2);
    Fr_sub_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ns2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ms2n, 0);
    Fr_sub_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ms2n, 1);
    Fr_sub_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ms2n, 2);
    Fr_sub_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ms2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1ms2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fr_sub_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fr_sub_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fr_sub_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fr_sub_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fr_sub_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fr_sub_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_s1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fr_sub_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fr_sub_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fr_sub_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fr_sub_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fr_sub_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fr_sub_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_sub_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_sub_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_sub_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_sub_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_sub_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_sub_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_sub_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_sub_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_sub_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_sub_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_sub_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
    Fr_sub_s1l2n_test(&Result4_s1l2n,  &A4_s1l2n,  &B4_s1l2n, 4);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_sub_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_sub_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_sub_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_sub_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
    Fr_sub_s1l2n_test(&Result4_s1l2n,  &A4_s1l2n,  &B4_s1l2n, 4);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_add_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_add_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_add_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_add_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_add_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_add_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_add_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_add_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_add_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_add_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_add_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_add_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_add_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_add_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_add_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_add_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_add_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_add_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_add_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_add_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_add_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_add_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_add_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_add_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_add_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_add_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_add_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_add_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_add_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_add_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_add_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_s1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fr_add_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fr_add_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fr_add_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fr_add_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fr_add_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fr_add_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1ms2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ns2n, 0);
    Fr_add_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ns2n, 1);
    Fr_add_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ns2n, 2);
    Fr_add_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ns2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ms2n, 0);
    Fr_add_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ms2n, 1);
    Fr_add_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ms2n, 2);
    Fr_add_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ms2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1ms2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fr_add_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fr_add_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fr_add_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fr_add_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fr_add_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fr_add_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_s1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fr_add_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fr_add_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fr_add_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fr_add_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fr_add_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fr_add_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_add_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_add_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_add_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_add_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_add_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_add_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_add_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_add_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_add_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_add_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_add_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_add_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_add_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_add_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_add_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif


//#ifdef TEST_FR_C_FUNCTIONS
//    Fr_toInt_unit_test();
//    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
//    Fr_toInt_test(uRawResult,  &RawA, 0);
//    Fr_toInt_test(uRawResult1, &RawA1, 1);
//    Fr_toInt_test(uRawResult2, &RawA2, 2);
//    Fr_toInt_test(uRawResult3, &RawA3, 3);
//#endif
//#endif
//#ifdef TEST_FR_ASM_FUNCTIONS
//    Fr_toInt_test(uRawResult,  &RawA, 0);
//    Fr_toInt_test(uRawResult1, &RawA1, 1);
//    Fr_toInt_test(uRawResult2, &RawA2, 2);
//    Fr_toInt_test(uRawResult3, &RawA3, 3);
//#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_lt_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_lt_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_lt_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_lt_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_lt_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_lt_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_lt_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_lt_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_lt_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_lt_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_lt_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_lt_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_lt_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lt_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lt_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lt_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lt_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lt_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lt_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_lt_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_lt_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_lt_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_lt_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_lt_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_lt_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_lt_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_lt_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_lt_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_lt_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_lt_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_lt_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_lt_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_lt_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_lt_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_lt_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_lt_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_lt_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_lt_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_lt_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_lt_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_lt_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_lt_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_lt_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_lt_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_lt_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_lt_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_lt_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_lt_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_lt_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lt_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lt_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_lt_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_lt_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_lt_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lt_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_lt_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_lt_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_lt_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_geq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_geq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_geq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_geq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_geq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_geq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_geq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_geq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_geq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_geq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_geq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_geq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_geq_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_geq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_geq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_geq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_geq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_geq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_geq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_geq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_geq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_geq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_geq_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_geq_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_geq_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_geq_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_geq_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_geq_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_geq_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_geq_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_geq_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_geq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_geq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_geq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_geq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_geq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_geq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_geq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_geq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_geq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_geq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_geq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_geq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_geq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_geq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_geq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_geq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_geq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_geq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_geq_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_geq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_geq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_geq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_geq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_geq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_geq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_geq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_geq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_neg_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neg_test(&RawResult,  &RawA,  &RawB, 0);
    Fr_neg_test(&RawResult1, &RawA1, &RawB1, 1);
    Fr_neg_test(&RawResult2, &RawA2, &RawB2, 2);
    Fr_neg_test(&RawResult3, &RawA3, &RawB3, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neg_test(&RawResult,  &RawA,  &RawB, 0);
    Fr_neg_test(&RawResult1, &RawA1, &RawB1, 1);
    Fr_neg_test(&RawResult2, &RawA2, &RawB2, 2);
    Fr_neg_test(&RawResult3, &RawA3, &RawB3, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_eq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_eq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_eq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_eq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_eq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_eq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_eq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_eq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_eq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_eq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_eq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_eq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_eq_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_eq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_eq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_eq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_eq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_eq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_eq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_eq_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_eq_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_eq_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_eq_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_eq_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_eq_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_eq_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_eq_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_eq_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_eq_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_eq_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_eq_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_eq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_eq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_eq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_eq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_eq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_eq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_eq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_eq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_eq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_eq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_eq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_eq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_eq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_eq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_eq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_eq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_eq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_eq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_eq_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_eq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_eq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_eq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_eq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_eq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_eq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_eq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_eq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_neq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_neq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_neq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_neq_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_neq_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_neq_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_neq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_neq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_neq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_neq_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_neq_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_neq_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_neq_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_neq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_neq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_neq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_neq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_neq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_neq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_neq_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_neq_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_neq_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_neq_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_neq_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_neq_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_neq_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_neq_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_neq_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_neq_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_neq_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_neq_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_neq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_neq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_neq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TESxorValT_FR_ASM_FUNCTIONS
    Fr_neq_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_neq_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_neq_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_neq_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_neq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_neq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_neq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_neq_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_neq_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_neq_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_neq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_neq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_neq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_neq_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_neq_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_neq_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_neq_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_neq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_neq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_neq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_neq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_neq_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_neq_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_neq_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_neq_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_gt_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_gt_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_gt_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_gt_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_gt_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_gt_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_gt_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_gt_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_gt_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_gt_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_gt_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_gt_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_gt_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_gt_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_gt_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_gt_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_gt_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_gt_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_gt_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_gt_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_gt_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_gt_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_gt_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_gt_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_gt_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_gt_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_gt_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_gt_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_gt_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_gt_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_gt_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_gt_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_gt_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_gt_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_gt_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_gt_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_gt_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_gt_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_gt_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_gt_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_gt_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_gt_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_gt_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_gt_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_gt_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_gt_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_gt_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_gt_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_gt_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_gt_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_gt_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_gt_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_gt_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_gt_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_gt_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_gt_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_gt_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_gt_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_band_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_band_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_band_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_band_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_band_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_band_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_band_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_band_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_band_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_band_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_band_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_band_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_band_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_band_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_band_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_band_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_band_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_band_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_band_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_band_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_band_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_band_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_band_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_band_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_band_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_band_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_band_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_band_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_band_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_band_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_band_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_band_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_band_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_band_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_band_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_band_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_band_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_band_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_band_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_band_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_band_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_band_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_band_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_band_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_band_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_band_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_band_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_band_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_band_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_band_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_band_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_band_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_band_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_band_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_band_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_band_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_band_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_band_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_land_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_land_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_land_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_land_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_land_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_land_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_land_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_land_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_land_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_land_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_land_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_land_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_land_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_land_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_land_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_land_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_land_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_land_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_land_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_land_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_land_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_land_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_land_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_land_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_land_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_land_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_land_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_land_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_land_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_land_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_land_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_land_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_land_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_land_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_land_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_land_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_land_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_land_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_land_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_land_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_land_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_land_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_land_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_land_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_land_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_land_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_land_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_land_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_land_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_land_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_land_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_land_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_land_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_land_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_land_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_land_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_land_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_land_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif


#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_s1s2_unit_test();
#ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_lor_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_lor_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_lor_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fr_lor_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fr_lor_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fr_lor_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_l1nl2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_lor_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_lor_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_lor_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fr_lor_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fr_lor_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fr_lor_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
   Fr_lor_l1ml2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lor_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lor_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lor_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lor_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lor_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lor_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_l1ml2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lor_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lor_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lor_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fr_lor_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fr_lor_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fr_lor_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_l1nl2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fr_lor_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fr_lor_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fr_lor_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fr_lor_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fr_lor_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fr_lor_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_s1l2m_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_lor_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_lor_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_lor_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_s1l2m_test(&Result_s1l2m,   &A_s1l2m,   &B_s1l2m, 0);
    Fr_lor_s1l2m_test(&Result1_s1l2m,  &A1_s1l2m,  &B1_s1l2m, 1);
    Fr_lor_s1l2m_test(&Result2_s1l2m,  &A2_s1l2m,  &B2_s1l2m, 2);
    Fr_lor_s1l2m_test(&Result3_s1l2m,  &A3_s1l2m,  &B3_s1l2m, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_l1ms2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_lor_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_lor_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_lor_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
    #endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1ms2_test(&Result_l1ms2,  &A_l1ms2,  &B_l1ms2, 0);
    Fr_lor_l1ms2_test(&Result1_l1ms2, &A1_l1ms2, &B1_l1ms2, 1);
    Fr_lor_l1ms2_test(&Result2_l1ms2, &A2_l1ms2, &B2_l1ms2, 2);
    Fr_lor_l1ms2_test(&Result3_l1ms2, &A3_l1ms2, &B3_l1ms2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_l1ns2_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_lor_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_lor_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_lor_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_l1ns2_test(&Result_l1ns2,  &A_l1ns2,  &B_l1ns2, 0);
    Fr_lor_l1ns2_test(&Result1_l1ns2, &A1_l1ns2, &B1_l1ns2, 1);
    Fr_lor_l1ns2_test(&Result2_l1ns2, &A2_l1ns2, &B2_l1ns2, 2);
    Fr_lor_l1ns2_test(&Result3_l1ns2, &A3_l1ns2, &B3_l1ns2, 3);
#endif

#ifdef TEST_FR_C_FUNCTIONS
    Fr_lor_s1l2n_unit_test();
    #ifdef TEST_FR_C_FUNCTIONS_WITH_RESULT
    Fr_lor_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_lor_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_lor_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_lor_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif
#endif
#ifdef TEST_FR_ASM_FUNCTIONS
    Fr_lor_s1l2n_test(&Result_s1l2n,   &A_s1l2n,   &B_s1l2n, 0);
    Fr_lor_s1l2n_test(&Result1_s1l2n,  &A1_s1l2n,  &B1_s1l2n, 1);
    Fr_lor_s1l2n_test(&Result2_s1l2n,  &A2_s1l2n,  &B2_s1l2n, 2);
    Fr_lor_s1l2n_test(&Result3_s1l2n,  &A3_s1l2n,  &B3_s1l2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_add_unit_test();
//    Fq_Rw_add_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_add_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_add_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_add_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_add_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_add_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_add_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_add_test(pRawResult3, pRawA3, pRawB3, 3);
    Fq_Rw_add_test(pRawResult6, pRawA6, pRawB6, 6);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_sub_unit_test();
//    Fq_Rw_sub_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_sub_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_sub_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_sub_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_sub_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_sub_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_sub_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_sub_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_copy_unit_test();
//    Fq_Rw_copy_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_copy_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_copy_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_copy_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_copy_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_copy_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_copy_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_copy_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_Neg_unit_test();
//    Fq_Rw_Neg_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_Neg_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_Neg_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_Neg_test(pRawResult3, pRawA3, pRawB3, 3);
//    Fq_Rw_Neg_test(pRawResult5, pRawA5, pRawB5, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_Neg_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_Neg_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_Neg_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_Neg_test(pRawResult3, pRawA3, pRawB3, 3);
    Fq_Rw_Neg_test(pRawResult5, pRawA5, pRawB5, 5);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_sub_unit_test();
//    Fq_Rw_mul_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_mul_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_mul_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_mul_test(pRawResult3, pRawA3, pRawB3, 3);
//    Fq_Rw_mul_test(pRawResult4, pRawA4, pRawB4, 4);
//    Fq_Rw_mul_test(pRawResult5, pRawA5, pRawB5, 5);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_mul_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_mul_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_mul_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_mul_test(pRawResult3, pRawA3, pRawB3, 3);
    Fq_Rw_mul_test(pRawResult4, pRawA4, pRawB4, 4);
    Fq_Rw_mul_test(pRawResult5, pRawA5, pRawB5, 5);
    Fq_Rw_mul_test(pRawResult8, pRawA8, pRawB8, 8);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_Msquare_unit_test();
//    Fq_Rw_Msquare_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_Msquare_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_Msquare_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_Msquare_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_Msquare_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_Msquare_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_Msquare_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_Msquare_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_mul1_unit_test();
//    Fq_Rw_mul1_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_mul1_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_mul1_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_mul1_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_mul1_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_mul1_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_mul1_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_mul1_test(pRawResult3, pRawA3, pRawB3, 3);
    Fq_Rw_mul1_test(pRawResult9, pRawA9, pRawB9, 9);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_ToMontgomery_unit_test();
//    Fq_Rw_ToMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_ToMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_ToMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_ToMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_ToMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_ToMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_ToMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_ToMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_IsEq_unit_test();
//    Fr_rawIsEq_test(pRawResult,  pRawA,  pRawB, 0);
//    Fr_rawIsEq_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fr_rawIsEq_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fr_rawIsEq_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_rawIsEq_test(uRawResult,  pRawA,  pRawB, 0);
    Fq_rawIsEq_test(uRawResult1, pRawA1, pRawB1, 1);
    Fq_rawIsEq_test(uRawResult2, pRawA2, pRawB2, 2);
    Fq_rawIsEq_test(uRawResult3, pRawA3, pRawB3, 3);
    Fq_rawIsEq_test(uRawResult7, pRawA7, pRawB7, 7);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_rawIsZero_unit_test();
//    Fq_rawIsZero_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_rawIsZero_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_rawIsZero_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_rawIsZero_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_rawIsZero_test(uRawResult,  pRawA,  pRawB, 0);
    Fq_rawIsZero_test(uRawResult1, pRawA1, pRawB1, 1);
    Fq_rawIsZero_test(uRawResult2, pRawA2, pRawB2, 2);
    Fq_rawIsZero_test(uRawResult3, pRawA3, pRawB3, 3);
    Fq_rawIsZero_test(uRawResult5, pRawA5, pRawB5, 5);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_Rw_FromMontgomery_unit_test();
//    Fq_Rw_FromMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
//    Fq_Rw_FromMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
//    Fq_Rw_FromMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
//    Fq_Rw_FromMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_Rw_FromMontgomery_test(pRawResult,  pRawA,  pRawB, 0);
    Fq_Rw_FromMontgomery_test(pRawResult1, pRawA1, pRawB1, 1);
    Fq_Rw_FromMontgomery_test(pRawResult2, pRawA2, pRawB2, 2);
    Fq_Rw_FromMontgomery_test(pRawResult3, pRawA3, pRawB3, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_toNormal_unit_test();
//    Fq_toNormal_test(&RawResult,  &RawA,  &RawB, 0);
//    Fq_toNormal_test(&RawResult1, &RawA1, &RawB1, 1);
//    Fq_toNormal_test(&RawResult2, &RawA2, &RawB2, 2);
//    Fq_toNormal_test(&RawResult3, &RawA3, &RawB3, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_toNormal_test(&RawResult,  &RawA,  &RawB, 0);
    Fq_toNormal_test(&RawResult1, &RawA1, &RawB1, 1);
    Fq_toNormal_test(&RawResult2, &RawA2, &RawB2, 2);
    Fq_toNormal_test(&RawResult3, &RawA3, &RawB3, 3);
#endif


#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_s1s2_unit_test();
//    Fq_mul_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
//    Fq_mul_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
//    Fq_mul_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
//    Fq_mul_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_s1s2_test(&Result_s1s2,  &A_s1s2,  &B_s1s2, 0);
    Fq_mul_s1s2_test(&Result1_s1s2, &A1_s1s2, &B1_s1s2, 1);
    Fq_mul_s1s2_test(&Result2_s1s2, &A2_s1s2, &B2_s1s2, 2);
    Fq_mul_s1s2_test(&Result3_s1s2, &A3_s1s2, &B3_s1s2, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1nl2n_unit_test();
//    Fq_mul_l1nl2n_test(&Result_l1nl2n, &A_l1nl2n,  &B_l1nl2n, 0);
//    Fq_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
//    Fq_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
//    Fq_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1nl2n_test(&Result_l1nl2n,  &A_l1nl2n,  &B_l1nl2n, 0);
    Fq_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1nl2n, &B1_l1nl2n, 1);
    Fq_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1nl2n, &B2_l1nl2n, 2);
    Fq_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1nl2n, &B3_l1nl2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
   Fq_mul_l1ml2n_unit_test();
//    Fq_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fq_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fq_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fq_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
    Fq_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
    Fq_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
    Fq_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1ml2m_unit_test();
//    Fq_mul_l1ml2n_test(&Result_l1ml2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fq_mul_l1ml2n_test(&Result1_l1ml2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fq_mul_l1ml2n_test(&Result2_l1ml2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fq_mul_l1ml2n_test(&Result3_l1ml2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ml2m_test(&Result_l1ml2m, &A_l1ml2m,  &B_l1ml2m, 0);
    Fq_mul_l1ml2m_test(&Result1_l1ml2m, &A1_l1ml2m, &B1_l1ml2m, 1);
    Fq_mul_l1ml2m_test(&Result2_l1ml2m, &A2_l1ml2m, &B2_l1ml2m, 2);
    Fq_mul_l1ml2m_test(&Result3_l1ml2m, &A3_l1ml2m, &B3_l1ml2m, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1nl2m_unit_test();
//    Fq_mul_l1nl2n_test(&Result_l1nl2n, &A_l1ml2n,  &B_l1ml2n, 0);
//    Fq_mul_l1nl2n_test(&Result1_l1nl2n, &A1_l1ml2n, &B1_l1ml2n, 1);
//    Fq_mul_l1nl2n_test(&Result2_l1nl2n, &A2_l1ml2n, &B2_l1ml2n, 2);
//    Fq_mul_l1nl2n_test(&Result3_l1nl2n, &A3_l1ml2n, &B3_l1ml2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1nl2m_test(&Result_l1nl2m, &A_l1nl2m,  &B_l1nl2m, 0);
    Fq_mul_l1nl2m_test(&Result1_l1nl2m, &A1_l1nl2m, &B1_l1nl2m, 1);
    Fq_mul_l1nl2m_test(&Result2_l1nl2m, &A2_l1nl2m, &B2_l1nl2m, 2);
    Fq_mul_l1nl2m_test(&Result3_l1nl2m, &A3_l1nl2m, &B3_l1nl2m, 3);
#endif


#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1ns2n_unit_test();
//    Fq_mul_l1ns2n_test(&Result_l1ns2n,  &A_l1ns2n,  &B_l1ns2n, 0);
//    Fq_mul_l1ns2n_test(&Result1_l1ns2n, &A1_l1ns2n, &B1_l1ns2n, 1);
//    Fq_mul_l1ns2n_test(&Result2_l1ns2n, &A2_l1ns2n, &B2_l1ns2n, 2);
//    Fq_mul_l1ns2n_test(&Result3_l1ns2n, &A3_l1ns2n, &B3_l1ns2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ns2n_test(&Result_l1ns2n,  &A_l1ns2n,  &B_l1ns2n, 0);
    Fq_mul_l1ns2n_test(&Result1_l1ns2n, &A1_l1ns2n, &B1_l1ns2n, 1);
    Fq_mul_l1ns2n_test(&Result2_l1ns2n, &A2_l1ns2n, &B2_l1ns2n, 2);
    Fq_mul_l1ns2n_test(&Result3_l1ns2n, &A3_l1ns2n, &B3_l1ns2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_s1nl2n_unit_test();
//    Fq_mul_s1nl2n_test(&Result_s1nl2n,   &A_s1nl2n,   &B_s1nl2n, 0);
//    Fq_mul_s1nl2n_test(&Result1_s1nl2n,  &A1_s1nl2n,  &B1_s1nl2n, 1);
//    Fq_mul_s1nl2n_test(&Result2_s1nl2n,  &A2_s1nl2n,  &B2_s1nl2n, 2);
//    Fq_mul_s1nl2n_test(&Result3_s1nl2n,  &A3_s1nl2n,  &B3_s1nl2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_s1nl2n_test(&Result_s1nl2n,   &A_s1nl2n,   &B_s1nl2n, 0);
    Fq_mul_s1nl2n_test(&Result1_s1nl2n,  &A1_s1nl2n,  &B1_s1nl2n, 1);
    Fq_mul_s1nl2n_test(&Result2_s1nl2n,  &A2_s1nl2n,  &B2_s1nl2n, 2);
    Fq_mul_s1nl2n_test(&Result3_s1nl2n,  &A3_s1nl2n,  &B3_s1nl2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_s1nl2m_unit_test();
//    Fq_mul_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
//    Fq_mul_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
//    Fq_mul_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
//    Fq_mul_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_s1nl2m_test(&Result_s1nl2m,   &A_s1nl2m,   &B_s1nl2m, 0);
    Fq_mul_s1nl2m_test(&Result1_s1nl2m,  &A1_s1nl2m,  &B1_s1nl2m, 1);
    Fq_mul_s1nl2m_test(&Result2_s1nl2m,  &A2_s1nl2m,  &B2_s1nl2m, 2);
    Fq_mul_s1nl2m_test(&Result3_s1nl2m,  &A3_s1nl2m,  &B3_s1nl2m, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1ms2n_unit_test();
//    Fq_mul_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ns2n, 0);
//    Fq_mul_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ns2n, 1);
//    Fq_mul_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ns2n, 2);
//    Fq_mul_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ns2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ms2n_test(&Result_l1ms2n,  &A_l1ms2n,  &B_l1ms2n, 0);
    Fq_mul_l1ms2n_test(&Result1_l1ms2n, &A1_l1ms2n, &B1_l1ms2n, 1);
    Fq_mul_l1ms2n_test(&Result2_l1ms2n, &A2_l1ms2n, &B2_l1ms2n, 2);
    Fq_mul_l1ms2n_test(&Result3_l1ms2n, &A3_l1ms2n, &B3_l1ms2n, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1ns2m_unit_test();
//    Fq_mul_l1ns2m_test(&Result_l1ns2m,  &A_l1ns2m,  &B_l1ns2m, 0);
//    Fq_mul_l1ns2m_test(&Result1_l1ns2m, &A1_l1ns2m, &B1_l1ns2m, 1);
//    Fq_mul_l1ns2m_test(&Result2_l1ns2m, &A2_l1ns2m, &B2_l1ns2m, 2);
//    Fq_mul_l1ns2m_test(&Result3_l1ns2m, &A3_l1ns2m, &B3_l1ns2m, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ns2m_test(&Result_l1ns2m,  &A_l1ns2m,  &B_l1ns2m, 0);
    Fq_mul_l1ns2m_test(&Result1_l1ns2m, &A1_l1ns2m, &B1_l1ns2m, 1);
    Fq_mul_l1ns2m_test(&Result2_l1ns2m, &A2_l1ns2m, &B2_l1ns2m, 2);
    Fq_mul_l1ns2m_test(&Result3_l1ns2m, &A3_l1ns2m, &B3_l1ns2m, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_l1ms2m_unit_test();
//    Fq_mul_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
//    Fq_mul_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
//    Fq_mul_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
//    Fq_mul_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_l1ms2m_test(&Result_l1ms2m,  &A_l1ms2m,  &B_l1ms2m, 0);
    Fq_mul_l1ms2m_test(&Result1_l1ms2m, &A1_l1ms2m, &B1_l1ms2m, 1);
    Fq_mul_l1ms2m_test(&Result2_l1ms2m, &A2_l1ms2m, &B2_l1ms2m, 2);
    Fq_mul_l1ms2m_test(&Result3_l1ms2m, &A3_l1ms2m, &B3_l1ms2m, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_s1ml2m_unit_test();
//    Fq_mul_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
//    Fq_mul_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
//    Fq_mul_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
//    Fq_mul_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_s1ml2m_test(&Result_s1ml2m,   &A_s1ml2m,   &B_s1ml2m, 0);
    Fq_mul_s1ml2m_test(&Result1_s1ml2m,  &A1_s1ml2m,  &B1_s1ml2m, 1);
    Fq_mul_s1ml2m_test(&Result2_s1ml2m,  &A2_s1ml2m,  &B2_s1ml2m, 2);
    Fq_mul_s1ml2m_test(&Result3_s1ml2m,  &A3_s1ml2m,  &B3_s1ml2m, 3);
#endif

#ifdef TEST_FQ_C_FUNCTIONS
    Fq_mul_s1ml2n_unit_test();
//    Fq_mul_s1ml2n_test(&Result_s1ml2n,   &A_s1ml2n,   &B_s1ml2n, 0);
//    Fq_mul_s1ml2n_test(&Result1_s1ml2n,  &A1_s1ml2n,  &B1_s1ml2n, 1);
//    Fq_mul_s1ml2n_test(&Result2_s1ml2n,  &A2_s1ml2n,  &B2_s1ml2n, 2);
//    Fq_mul_s1ml2n_test(&Result3_s1ml2n,  &A3_s1ml2n,  &B3_s1ml2n, 3);
#endif
#ifdef TEST_FQ_ASM_FUNCTIONS
    Fq_mul_s1ml2n_test(&Result_s1ml2n,   &A_s1ml2n,   &B_s1ml2n, 0);
    Fq_mul_s1ml2n_test(&Result1_s1ml2n,  &A1_s1ml2n,  &B1_s1ml2n, 1);
    Fq_mul_s1ml2n_test(&Result2_s1ml2n,  &A2_s1ml2n,  &B2_s1ml2n, 2);
    Fq_mul_s1ml2n_test(&Result3_s1ml2n,  &A3_s1ml2n,  &B3_s1ml2n, 3);
#endif

return 0;
}
