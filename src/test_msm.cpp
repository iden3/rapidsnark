// Correctness and benchmark harness for the ffiasm MSM used by the prover.
//
// Correctness: compares multiMulByScalarMSM against the older, independent
// ParallelMultiexp implementation (multiMulByScalar) on scalar distributions
// that mimic circom witnesses (mostly 0/1 and small values) plus boundary
// cases around the 64-bit partition threshold.
//
// Usage: test_msm [bench]

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

#include "alt_bn128.hpp"

using namespace AltBn128;

namespace {

std::mt19937_64 rng(0xC0FFEEULL);

typedef AltBn128::FrElement Scalar; // RawFr::Element, 4 little-endian 64-bit limbs

void setZero(Scalar &s) { s.v[0] = s.v[1] = s.v[2] = s.v[3] = 0; }

void setU64(Scalar &s, uint64_t v) { setZero(s); s.v[0] = v; }

void setRand254(Scalar &s)
{
    s.v[0] = rng();
    s.v[1] = rng();
    s.v[2] = rng();
    s.v[3] = rng() & 0x1fffffffffffffffULL; // < 2^253 < r
}

void setFromDecimal(Scalar &s, const char *dec)
{
    Fr.fromString(s, dec);
    Fr.fromMontgomery(s, s);
}

// Distinct affine points: pool[i] = (i+1)*G, tiled over the output array.
template <typename CurveT, typename PointAffineT>
void fillBases(CurveT &C, PointAffineT *bases, int n, int poolSize)
{
    std::vector<PointAffineT> pool(poolSize);

    C.copy(pool[0], C.oneAffine());
    for (int i = 1; i < poolSize; i++) {
        typename CurveT::Point t;
        C.add(t, pool[i-1], C.oneAffine());
        C.copy(pool[i], t);
    }
    for (int i = 0; i < n; i++) {
        bases[i] = pool[i % poolSize];
    }
}

enum Dist { DIST_RAND254, DIST_WITNESS, DIST_IDEN3, DIST_BINARY, DIST_U64, DIST_ZEROS, DIST_ONES };

const char *distName(Dist d)
{
    switch (d) {
    case DIST_RAND254: return "rand254";
    case DIST_WITNESS: return "witness";
    case DIST_IDEN3:   return "iden3";
    case DIST_BINARY:  return "binary";
    case DIST_U64:     return "u64";
    case DIST_ZEROS:   return "zeros";
    case DIST_ONES:    return "ones";
    }
    return "?";
}

void fillScalars(Scalar *scalars, int n, Dist d)
{
    for (int i = 0; i < n; i++) {
        switch (d) {
        case DIST_RAND254:
            setRand254(scalars[i]);
            break;
        case DIST_WITNESS: {
            // bit-decomposition-heavy circuit: mostly 0/1, a tail of full-width
            uint64_t p = rng() % 100;
            if      (p < 30) setZero(scalars[i]);
            else if (p < 60) setU64(scalars[i], 1);
            else if (p < 75) setU64(scalars[i], rng() & 0xffff);
            else if (p < 85) setU64(scalars[i], rng());
            else             setRand254(scalars[i]);
            break;
        }
        case DIST_IDEN3: {
            // measured on the credentialAtomicQuery* witnesses: hash-heavy,
            // so most wires are uniform field elements
            uint64_t p = rng() % 100;
            if      (p < 15) setZero(scalars[i]);
            else if (p < 20) setU64(scalars[i], 1);
            else if (p < 21) setU64(scalars[i], rng());
            else             setRand254(scalars[i]);
            break;
        }
        case DIST_BINARY:
            setU64(scalars[i], rng() & 1);
            break;
        case DIST_U64:
            setU64(scalars[i], rng());
            break;
        case DIST_ZEROS:
            setZero(scalars[i]);
            break;
        case DIST_ONES:
            setU64(scalars[i], 1);
            break;
        }
    }
}

int failures = 0;

void checkG1(const char *name, G1PointAffine *bases, Scalar *scalars, int n)
{
    G1Point res, ref;

    G1.multiMulByScalarMSM(res, bases, (uint8_t *)scalars, sizeof(Scalar), n);
    G1.multiMulByScalar(ref, bases, (uint8_t *)scalars, sizeof(Scalar), n);

    if (!G1.eq(res, ref)) {
        printf("FAIL G1 %-16s n=%d\n", name, n);
        failures++;
    } else {
        printf("ok   G1 %-16s n=%d\n", name, n);
    }
}

void checkG2(const char *name, G2PointAffine *bases, Scalar *scalars, int n)
{
    G2Point res, ref;

    G2.multiMulByScalarMSM(res, bases, (uint8_t *)scalars, sizeof(Scalar), n);
    G2.multiMulByScalar(ref, bases, (uint8_t *)scalars, sizeof(Scalar), n);

    if (!G2.eq(res, ref)) {
        printf("FAIL G2 %-16s n=%d\n", name, n);
        failures++;
    } else {
        printf("ok   G2 %-16s n=%d\n", name, n);
    }
}

void correctness()
{
    const int n = 8192;
    std::vector<G1PointAffine> bases(n);
    std::vector<Scalar> scalars(n);

    fillBases(G1, bases.data(), n, 1024);

    const Dist dists[] = { DIST_RAND254, DIST_WITNESS, DIST_IDEN3, DIST_BINARY,
                           DIST_U64, DIST_ZEROS, DIST_ONES };

    for (Dist d : dists) {
        fillScalars(scalars.data(), n, d);
        checkG1(distName(d), bases.data(), scalars.data(), n);
    }

    // Boundary values around the small/big partition threshold and the
    // top of the field, several of each so no class has a single element.
    {
        const char *rMinus1 = "21888242871839275222246405745257275088548364400416034343698204186575808495616";
        const char *rMinus2 = "21888242871839275222246405745257275088548364400416034343698204186575808495615";
        int i = 0;

        setU64(scalars[i++], 0);
        setU64(scalars[i++], 1);
        setU64(scalars[i++], 2);
        setU64(scalars[i++], 3);
        setU64(scalars[i++], 0x7fffffffffffffffULL);      // 2^63-1
        setU64(scalars[i++], 0x8000000000000000ULL);      // 2^63
        setU64(scalars[i++], 0xffffffffffffffffULL);      // 2^64-1 (max small)
        setZero(scalars[i]); scalars[i].v[1] = 1; i++;    // 2^64 (min big)
        setZero(scalars[i]); scalars[i].v[1] = 1; scalars[i].v[0] = 1; i++; // 2^64+1
        setZero(scalars[i]); scalars[i].v[3] = 0x2000000000000000ULL; i++;  // 2^253
        setFromDecimal(scalars[i++], rMinus1);
        setFromDecimal(scalars[i++], rMinus2);
        setU64(scalars[i++], 0xffffffffffffffffULL);
        setU64(scalars[i++], 1);
        setU64(scalars[i++], 0);
        setU64(scalars[i++], 0xffff);

        checkG1("boundary", bases.data(), scalars.data(), i);

        // very small n
        checkG1("n2", bases.data(), scalars.data(), 2);
        checkG1("n3", bases.data(), scalars.data(), 3);
    }

    // ~10% infinity bases (real zkeys contain them in pointsA/B)
    {
        std::vector<G1PointAffine> basesInf(bases);

        for (int i = 0; i < n; i += 10) {
            G1.copy(basesInf[i], G1.zeroAffine());
        }
        fillScalars(scalars.data(), n, DIST_IDEN3);
        checkG1("infinity", basesInf.data(), scalars.data(), n);
        fillScalars(scalars.data(), n, DIST_RAND254);
        checkG1("infinity254", basesInf.data(), scalars.data(), n);
    }

    // tiny base pool: many equal points land in the same bucket, forcing
    // the doubling/cancellation paths of the batch-affine accumulator
    {
        std::vector<G1PointAffine> basesDup(n);

        fillBases(G1, basesDup.data(), n, 4);
        fillScalars(scalars.data(), n, DIST_RAND254);
        checkG1("dup4-rand", basesDup.data(), scalars.data(), n);
        fillScalars(scalars.data(), n, DIST_U64);
        checkG1("dup4-u64", basesDup.data(), scalars.data(), n);
    }

    // n=1 against plain scalar mul
    {
        G1Point res, ref;
        setRand254(scalars[0]);
        G1.multiMulByScalarMSM(res, bases.data(), (uint8_t *)scalars.data(), sizeof(Scalar), 1);
        G1.mulByScalar(ref, bases[0], (uint8_t *)scalars.data(), sizeof(Scalar));
        if (!G1.eq(res, ref)) { printf("FAIL G1 n1\n"); failures++; }
        else printf("ok   G1 n1\n");
    }

    // n=0
    {
        G1Point res;
        G1.multiMulByScalarMSM(res, bases.data(), (uint8_t *)scalars.data(), sizeof(Scalar), 0);
        if (!G1.isZero(res)) { printf("FAIL G1 n0\n"); failures++; }
        else printf("ok   G1 n0\n");
    }

    // G2
    {
        const int n2 = 4096;
        std::vector<G2PointAffine> bases2(n2);
        std::vector<Scalar> scalars2(n2);

        fillBases(G2, bases2.data(), n2, 512);

        for (Dist d : dists) {
            fillScalars(scalars2.data(), n2, d);
            checkG2(distName(d), bases2.data(), scalars2.data(), n2);
        }
    }
}

// Simulates the prover's witness phase: A, B1 (G1, shared scalars),
// B2 (G2, shared scalars), C (G1, scalar suffix) batched into one task
// region, checked against independent single-MSM runs.
void batchCorrectness()
{
    const int n = 8192;
    const int nPublic = 100;

    std::vector<G1PointAffine> basesA(n), basesB1(n), basesC(n - nPublic - 1);
    std::vector<G2PointAffine> basesB2(n);
    std::vector<Scalar> scalars(n);

    fillBases(G1, basesA.data(), n, 512);
    fillBases(G1, basesB1.data(), n, 300);
    fillBases(G1, basesC.data(), n - nPublic - 1, 700);
    fillBases(G2, basesB2.data(), n, 256);
    fillScalars(scalars.data(), n, DIST_IDEN3);

    ThreadPool &pool = ThreadPool::defaultPool();
    const uint64_t nThreads = pool.getThreadCount();
    const uint64_t share = nThreads >= 4 ? nThreads/4 : 1;

    MSM<Curve<RawFq>, RawFq> msmA(G1), msmB1(G1), msmC(G1);
    MSM<Curve<F2Field<RawFq>>, F2Field<RawFq>> msmB2(G2);

    msmA.prepare(basesA.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n, share);
    msmB1.prepare(basesB1.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n, share);
    msmB2.prepare(basesB2.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n, share);
    msmC.prepare(basesC.data(), (uint8_t *)(scalars.data() + nPublic + 1), sizeof(Scalar), n - nPublic - 1, share);

    const uint64_t g1Bytes = std::max(msmA.arenaBytesPerThread(),
                             std::max(msmB1.arenaBytesPerThread(), msmC.arenaBytesPerThread()));
    const uint64_t g2Bytes = msmB2.arenaBytesPerThread();

    std::vector<uint8_t> g1Arena(nThreads * g1Bytes);
    std::vector<uint8_t> g2Arena(nThreads * g2Bytes);

    std::vector<std::function<void(uint64_t)>> tasks;
    msmB2.collectTasks(tasks, g2Arena.data(), g2Bytes);
    msmA.collectTasks(tasks, g1Arena.data(), g1Bytes);
    msmB1.collectTasks(tasks, g1Arena.data(), g1Bytes);
    msmC.collectTasks(tasks, g1Arena.data(), g1Bytes);

    pool.parallelFor(0, tasks.size(), [&] (int begin, int end, int numThread) {
        for (int t = begin; t < end; t++) {
            tasks[t]((uint64_t)numThread);
        }
    });

    G1Point rA, rB1, rC, refA, refB1, refC;
    G2Point rB2, refB2;

    msmA.finish(rA);
    msmB1.finish(rB1);
    msmB2.finish(rB2);
    msmC.finish(rC);

    G1.multiMulByScalarMSM(refA, basesA.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n);
    G1.multiMulByScalarMSM(refB1, basesB1.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n);
    G2.multiMulByScalarMSM(refB2, basesB2.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n);
    G1.multiMulByScalarMSM(refC, basesC.data(), (uint8_t *)(scalars.data() + nPublic + 1), sizeof(Scalar), n - nPublic - 1);

    bool ok = G1.eq(rA, refA) && G1.eq(rB1, refB1) && G2.eq(rB2, refB2) && G1.eq(rC, refC);

    if (!ok) {
        printf("FAIL batch A/B1/B2/C\n");
        failures++;
    } else {
        printf("ok   batch A/B1/B2/C\n");
    }
}

double medianMs(std::vector<double> &v)
{
    std::sort(v.begin(), v.end());
    return v[v.size()/2];
}

void bench()
{
    const int n = 1 << 20;
    const int reps = 5;

    std::vector<G1PointAffine> bases(n);
    std::vector<Scalar> scalars(n);

    fillBases(G1, bases.data(), n, 4096);

    printf("\nG1 MSM, n=%d (median of %d)\n", n, reps);

    const Dist dists[] = { DIST_RAND254, DIST_WITNESS, DIST_IDEN3, DIST_BINARY, DIST_U64 };

    for (Dist d : dists) {
        fillScalars(scalars.data(), n, d);

        G1Point res;
        G1.multiMulByScalarMSM(res, bases.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n); // warmup

        std::vector<double> times;
        for (int r = 0; r < reps; r++) {
            auto t0 = std::chrono::steady_clock::now();
            G1.multiMulByScalarMSM(res, bases.data(), (uint8_t *)scalars.data(), sizeof(Scalar), n);
            auto t1 = std::chrono::steady_clock::now();
            times.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count());
        }
        printf("  %-8s %8.2f ms\n", distName(d), medianMs(times));
    }

    // G2, smaller n
    {
        const int n2 = 1 << 17;
        std::vector<G2PointAffine> bases2(n2);
        std::vector<Scalar> scalars2(n2);

        fillBases(G2, bases2.data(), n2, 4096);

        printf("\nG2 MSM, n=%d (median of %d)\n", n2, reps);

        const Dist dists2[] = { DIST_RAND254, DIST_WITNESS, DIST_IDEN3 };

        for (Dist d : dists2) {
            fillScalars(scalars2.data(), n2, d);

            G2Point res;
            G2.multiMulByScalarMSM(res, bases2.data(), (uint8_t *)scalars2.data(), sizeof(Scalar), n2);

            std::vector<double> times;
            for (int r = 0; r < reps; r++) {
                auto t0 = std::chrono::steady_clock::now();
                G2.multiMulByScalarMSM(res, bases2.data(), (uint8_t *)scalars2.data(), sizeof(Scalar), n2);
                auto t1 = std::chrono::steady_clock::now();
                times.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count());
            }
            printf("  %-8s %8.2f ms\n", distName(d), medianMs(times));
        }
    }
}

} // namespace

int main(int argc, char **argv)
{
    correctness();
    batchCorrectness();

    if (failures) {
        printf("\n%d FAILURES\n", failures);
        return 1;
    }
    printf("\nall correctness tests passed\n");

    if (argc > 1 && strcmp(argv[1], "bench") == 0) {
        bench();
    }
    return 0;
}
