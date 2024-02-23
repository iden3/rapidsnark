#include "random_generator.hpp"
#include "logging.hpp"
#include <future>

namespace Groth16 {

template <typename Engine>
std::unique_ptr<Prover<Engine>> makeProver(
    u_int32_t nVars, 
    u_int32_t nPublic, 
    u_int32_t domainSize, 
    u_int64_t nCoeffs, 
    void *vk_alpha1,
    void *vk_beta_1,
    void *vk_beta_2,
    void *vk_delta_1,
    void *vk_delta_2,
    void *coefs, 
    void *pointsA, 
    void *pointsB1, 
    void *pointsB2, 
    void *pointsC, 
    void *pointsH
) {
    Prover<Engine> *p = new Prover<Engine>(
        Engine::engine, 
        nVars, 
        nPublic, 
        domainSize, 
        nCoeffs, 
        *(typename Engine::G1PointAffine *)vk_alpha1,
        *(typename Engine::G1PointAffine *)vk_beta_1,
        *(typename Engine::G2PointAffine *)vk_beta_2,
        *(typename Engine::G1PointAffine *)vk_delta_1,
        *(typename Engine::G2PointAffine *)vk_delta_2,
        (Coef<Engine> *)((uint64_t)coefs + 4), 
        (typename Engine::G1PointAffine *)pointsA,
        (typename Engine::G1PointAffine *)pointsB1,
        (typename Engine::G2PointAffine *)pointsB2,
        (typename Engine::G1PointAffine *)pointsC,
        (typename Engine::G1PointAffine *)pointsH
    );
    return std::unique_ptr< Prover<Engine> >(p);
}

template <typename Engine>
std::unique_ptr<Proof<Engine>> Prover<Engine>::prove(typename Engine::FrElement *wtns) {

#ifdef USE_OPENMP
    LOG_TRACE("Start Multiexp A");
    uint32_t sW = sizeof(wtns[0]);
    typename Engine::G1Point pi_a;
    E.g1.multiMulByScalar(pi_a, pointsA, (uint8_t *)wtns, sW, nVars);
    std::ostringstream ss2;
    ss2 << "pi_a: " << E.g1.toString(pi_a);
    LOG_DEBUG(ss2);

    LOG_TRACE("Start Multiexp B1");
    typename Engine::G1Point pib1;
    E.g1.multiMulByScalar(pib1, pointsB1, (uint8_t *)wtns, sW, nVars);
    std::ostringstream ss3;
    ss3 << "pib1: " << E.g1.toString(pib1);
    LOG_DEBUG(ss3);

    LOG_TRACE("Start Multiexp B2");
    typename Engine::G2Point pi_b;
    E.g2.multiMulByScalar(pi_b, pointsB2, (uint8_t *)wtns, sW, nVars);
    std::ostringstream ss4;
    ss4 << "pi_b: " << E.g2.toString(pi_b);
    LOG_DEBUG(ss4);

    LOG_TRACE("Start Multiexp C");
    typename Engine::G1Point pi_c;
    E.g1.multiMulByScalar(pi_c, pointsC, (uint8_t *)((uint64_t)wtns + (nPublic +1)*sW), sW, nVars-nPublic-1);
    std::ostringstream ss5;
    ss5 << "pi_c: " << E.g1.toString(pi_c);
    LOG_DEBUG(ss5);
#else
    LOG_TRACE("Start Multiexp A");
    uint32_t sW = sizeof(wtns[0]);
    typename Engine::G1Point pi_a;
    auto pA_future = std::async([&]() {
        E.g1.multiMulByScalar(pi_a, pointsA, (uint8_t *)wtns, sW, nVars);
    });

    LOG_TRACE("Start Multiexp B1");
    typename Engine::G1Point pib1;
    auto pB1_future = std::async([&]() {
        E.g1.multiMulByScalar(pib1, pointsB1, (uint8_t *)wtns, sW, nVars);
    });

    LOG_TRACE("Start Multiexp B2");
    typename Engine::G2Point pi_b;
    auto pB2_future = std::async([&]() {
        E.g2.multiMulByScalar(pi_b, pointsB2, (uint8_t *)wtns, sW, nVars);
    });

    LOG_TRACE("Start Multiexp C");
    typename Engine::G1Point pi_c;
    auto pC_future = std::async([&]() {
        E.g1.multiMulByScalar(pi_c, pointsC, (uint8_t *)((uint64_t)wtns + (nPublic +1)*sW), sW, nVars-nPublic-1);
    });
#endif

    LOG_TRACE("Start Initializing a b c A");
    auto a = new typename Engine::FrElement[domainSize];
    auto b = new typename Engine::FrElement[domainSize];
    auto c = new typename Engine::FrElement[domainSize];

    #pragma omp parallel for
    for (u_int32_t i=0; i<domainSize; i++) {
        E.fr.copy(a[i], E.fr.zero());
        E.fr.copy(b[i], E.fr.zero());
    }

    LOG_TRACE("Processing coefs");
#ifdef _OPENMP
    #define NLOCKS 1024
    omp_lock_t locks[NLOCKS];
    for (int i=0; i<NLOCKS; i++) omp_init_lock(&locks[i]);
    #pragma omp parallel for 
#endif
    for (u_int64_t i=0; i<nCoefs; i++) {
        typename Engine::FrElement *ab = (coefs[i].m == 0) ? a : b;
        typename Engine::FrElement aux;

        E.fr.mul(
            aux,
            wtns[coefs[i].s],
            coefs[i].coef
        );
#ifdef _OPENMP
        omp_set_lock(&locks[coefs[i].c % NLOCKS]);
#endif
        E.fr.add(
            ab[coefs[i].c],
            ab[coefs[i].c],
            aux
        );
#ifdef _OPENMP
        omp_unset_lock(&locks[coefs[i].c % NLOCKS]);
#endif
    }
#ifdef _OPENMP
    for (int i=0; i<NLOCKS; i++) omp_destroy_lock(&locks[i]);
#endif

    LOG_TRACE("Calculating c");
    #pragma omp parallel for
    for (u_int32_t i=0; i<domainSize; i++) {
        E.fr.mul(
            c[i],
            a[i],
            b[i]
        );
    }

    LOG_TRACE("Initializing fft");
    u_int32_t domainPower = fft->log2(domainSize);

    LOG_TRACE("Start iFFT A");
    fft->ifft(a, domainSize);
    LOG_TRACE("a After ifft:");
    LOG_DEBUG(E.fr.toString(a[0]).c_str());
    LOG_DEBUG(E.fr.toString(a[1]).c_str());
    LOG_TRACE("Start Shift A");
    #pragma omp parallel for
    for (u_int64_t i=0; i<domainSize; i++) {
        E.fr.mul(a[i], a[i], fft->root(domainPower+1, i));
    }
    LOG_TRACE("a After shift:");
    LOG_DEBUG(E.fr.toString(a[0]).c_str());
    LOG_DEBUG(E.fr.toString(a[1]).c_str());
    LOG_TRACE("Start FFT A");
    fft->fft(a, domainSize);
    LOG_TRACE("a After fft:");
    LOG_DEBUG(E.fr.toString(a[0]).c_str());
    LOG_DEBUG(E.fr.toString(a[1]).c_str());
    LOG_TRACE("Start iFFT B");
    fft->ifft(b, domainSize);
    LOG_TRACE("b After ifft:");
    LOG_DEBUG(E.fr.toString(b[0]).c_str());
    LOG_DEBUG(E.fr.toString(b[1]).c_str());
    LOG_TRACE("Start Shift B");
    #pragma omp parallel for
    for (u_int64_t i=0; i<domainSize; i++) {
        E.fr.mul(b[i], b[i], fft->root(domainPower+1, i));
    }
    LOG_TRACE("b After shift:");
    LOG_DEBUG(E.fr.toString(b[0]).c_str());
    LOG_DEBUG(E.fr.toString(b[1]).c_str());
    LOG_TRACE("Start FFT B");
    fft->fft(b, domainSize);
    LOG_TRACE("b After fft:");
    LOG_DEBUG(E.fr.toString(b[0]).c_str());
    LOG_DEBUG(E.fr.toString(b[1]).c_str());

    LOG_TRACE("Start iFFT C");
    fft->ifft(c, domainSize);
    LOG_TRACE("c After ifft:");
    LOG_DEBUG(E.fr.toString(c[0]).c_str());
    LOG_DEBUG(E.fr.toString(c[1]).c_str());
    LOG_TRACE("Start Shift C");
    #pragma omp parallel for
    for (u_int64_t i=0; i<domainSize; i++) {
        E.fr.mul(c[i], c[i], fft->root(domainPower+1, i));
    }
    LOG_TRACE("c After shift:");
    LOG_DEBUG(E.fr.toString(c[0]).c_str());
    LOG_DEBUG(E.fr.toString(c[1]).c_str());
    LOG_TRACE("Start FFT C");
    fft->fft(c, domainSize);
    LOG_TRACE("c After fft:");
    LOG_DEBUG(E.fr.toString(c[0]).c_str());
    LOG_DEBUG(E.fr.toString(c[1]).c_str());

    LOG_TRACE("Start ABC");
    #pragma omp parallel for
    for (u_int64_t i=0; i<domainSize; i++) {
        E.fr.mul(a[i], a[i], b[i]);
        E.fr.sub(a[i], a[i], c[i]);
        E.fr.fromMontgomery(a[i], a[i]);
    }
    LOG_TRACE("abc:");
    LOG_DEBUG(E.fr.toString(a[0]).c_str());
    LOG_DEBUG(E.fr.toString(a[1]).c_str());

    delete [] b;
    delete [] c;

    LOG_TRACE("Start Multiexp H");
    typename Engine::G1Point pih;
    E.g1.multiMulByScalar(pih, pointsH, (uint8_t *)a, sizeof(a[0]), domainSize);
    std::ostringstream ss1;
    ss1 << "pih: " << E.g1.toString(pih);
    LOG_DEBUG(ss1);

    delete [] a;

    typename Engine::FrElement r;
    typename Engine::FrElement s;
    typename Engine::FrElement rs;

    E.fr.copy(r, E.fr.zero());
    E.fr.copy(s, E.fr.zero());

    randombytes_buf((void *)&(r.v[0]), sizeof(r)-1);
    randombytes_buf((void *)&(s.v[0]), sizeof(s)-1);

#ifndef USE_OPENMP
    pA_future.get();
    pB1_future.get();
    pB2_future.get();
    pC_future.get();
#endif

    typename Engine::G1Point p1;
    typename Engine::G2Point p2;

    E.g1.add(pi_a, pi_a, vk_alpha1);
    E.g1.mulByScalar(p1, vk_delta1, (uint8_t *)&r, sizeof(r));
    E.g1.add(pi_a, pi_a, p1);

    E.g2.add(pi_b, pi_b, vk_beta2);
    E.g2.mulByScalar(p2, vk_delta2, (uint8_t *)&s, sizeof(s));
    E.g2.add(pi_b, pi_b, p2);

    E.g1.add(pib1, pib1, vk_beta1);
    E.g1.mulByScalar(p1, vk_delta1, (uint8_t *)&s, sizeof(s));
    E.g1.add(pib1, pib1, p1);

    E.g1.add(pi_c, pi_c, pih);

    E.g1.mulByScalar(p1, pi_a, (uint8_t *)&s, sizeof(s));
    E.g1.add(pi_c, pi_c, p1);

    E.g1.mulByScalar(p1, pib1, (uint8_t *)&r, sizeof(r));
    E.g1.add(pi_c, pi_c, p1);

    E.fr.mul(rs, r, s);
    E.fr.toMontgomery(rs, rs);

    E.g1.mulByScalar(p1, vk_delta1, (uint8_t *)&rs, sizeof(rs));
    E.g1.sub(pi_c, pi_c, p1);

    Proof<Engine> *p = new Proof<Engine>(Engine::engine);
    E.g1.copy(p->A, pi_a);
    E.g2.copy(p->B, pi_b);
    E.g1.copy(p->C, pi_c);

    return std::unique_ptr<Proof<Engine>>(p);
}

template <typename Engine>
std::string Proof<Engine>::toJsonStr() {

    std::ostringstream ss;
    ss << "{ \"pi_a\":[\"" << E.f1.toString(A.x) << "\",\"" << E.f1.toString(A.y) << "\",\"1\"], ";
    ss << " \"pi_b\": [[\"" << E.f1.toString(B.x.a) << "\",\"" << E.f1.toString(B.x.b) << "\"],[\"" << E.f1.toString(B.y.a) << "\",\"" << E.f1.toString(B.y.b) << "\"], [\"1\",\"0\"]], ";
    ss << " \"pi_c\": [\"" << E.f1.toString(C.x) << "\",\"" << E.f1.toString(C.y) << "\",\"1\"], ";
    ss << " \"protocol\":\"groth16\" }";
        
    return ss.str();
}

template <typename Engine>
json Proof<Engine>::toJson() {

    json p;

    p["pi_a"] = {};
    p["pi_a"].push_back(E.f1.toString(A.x) );
    p["pi_a"].push_back(E.f1.toString(A.y) );
    p["pi_a"].push_back("1" );


    json x2;
    x2.push_back(E.f1.toString(B.x.a));
    x2.push_back(E.f1.toString(B.x.b));
    json y2;
    y2.push_back(E.f1.toString(B.y.a));
    y2.push_back(E.f1.toString(B.y.b));
    json z2;
    z2.push_back("1");
    z2.push_back("0");
    p["pi_b"] = {};
    p["pi_b"].push_back(x2);
    p["pi_b"].push_back(y2);
    p["pi_b"].push_back(z2);

    p["pi_c"] = {};
    p["pi_c"].push_back(E.f1.toString(C.x) );
    p["pi_c"].push_back(E.f1.toString(C.y) );
    p["pi_c"].push_back("1" );

    p["protocol"] = "groth16";
            
    return p;
}

template <typename Engine>
static void
G1PointAffineFromJson(Engine &E, typename Engine::G1PointAffine &point, const json &value)
{
    E.f1.fromString(point.x, value[0]);
    E.f1.fromString(point.y, value[1]);
}

template <typename Engine>
static void
G2PointAffineFromJson(Engine &E, typename Engine::G2PointAffine &point, const json &value)
{
    E.f1.fromString(point.x.a, value[0][0]);
    E.f1.fromString(point.x.b, value[0][1]);
    E.f1.fromString(point.y.a, value[1][0]);
    E.f1.fromString(point.y.b, value[1][1]);
}

template <typename Engine>
void Proof<Engine>::fromJson(const json& proof)
{
    G1PointAffineFromJson(E, A, proof["pi_a"]);
    G2PointAffineFromJson(E, B, proof["pi_b"]);
    G1PointAffineFromJson(E, C, proof["pi_c"]);
}

template <typename Engine>
void VerificationKey<Engine>::fromJson(const json& key)
{
    G1PointAffineFromJson(E, Alpha, key["vk_alpha_1"]);
    G2PointAffineFromJson(E, Beta,  key["vk_beta_2"]);
    G2PointAffineFromJson(E, Gamma, key["vk_gamma_2"]);
    G2PointAffineFromJson(E, Delta, key["vk_delta_2"]);

    auto j_ic = key["IC"];

    IC.reserve(j_ic.size());

    for (const auto& el : j_ic.items()) {
        typename Engine::G1PointAffine point;

        G1PointAffineFromJson(E, point, el.value());
        IC.push_back(point);
    }
}

template <typename Engine>
Verifier<Engine>::Verifier()
    : E(Engine::engine)
{
    E.f2.fromString(xiToPMinus1Over3,
                    "21575463638280843010398324269430826099269044274347216827212613867836435027261,"
                    "10307601595873709700152284273816112264069230130616436755625194854815875713954");

    E.f2.fromString(xiToPMinus1Over2,
                    "2821565182194536844548159561693502659359617185244120367078079554186484126554,"
                    "3505843767911556378687030309984248845540243509899259641013678093033130930403");

    E.f1.fromString(xiToPSquaredMinus1Over3,
                    "21888242871839275220042445260109153167277707414472061641714758635765020556616");
}

template <typename Engine>
bool Verifier<Engine>::verify(Proof<Engine> &proof, InputsVector &inputs,
                             VerificationKey<Engine> &key)
{
    if (inputs.size() + 1 != key.IC.size()) {
        throw std::invalid_argument("len(inputs)+1 != len(vk.IC)");
    }

    typename Engine::G1Point vkX = E.g1.zero();

    for (int i = 0; i < inputs.size(); i++) {
        typename Engine::FrElement input;

        E.fr.fromMontgomery(input, inputs[i]);

        typename Engine::G1Point p1;
        E.g1.mulByScalar(p1, key.IC[i+1], (uint8_t *)&input, sizeof(input));
        E.g1.add(vkX, vkX, p1);
    }

    E.g1.add(vkX, vkX, key.IC[0]);

    typename Engine::G1Point pA;
    E.g1.copy(pA, proof.A);

    typename Engine::G1Point negAlpha;
    E.g1.neg(negAlpha, key.Alpha);

    typename Engine::G1Point negvkX;
    E.g1.neg(negvkX, vkX);

    typename Engine::G1Point negC;
    E.g1.neg(negC, proof.C);

    typename Engine::G2Point pB;
    E.g2.copy(pB, proof.B);

    typename Engine::G2Point pBeta;
    E.g2.copy(pBeta, key.Beta);

    typename Engine::G2Point pGamma;
    E.g2.copy(pGamma, key.Gamma);

    typename Engine::G2Point pDelta;
    E.g2.copy(pDelta, key.Delta);

    G1PointArray g1 = {pA, negAlpha, negvkX, negC};
    G2PointArray g2 = {pB, pBeta, pGamma, pDelta};

    return pairingCheck(g1, g2);
}

template <typename Engine>
void Verifier<Engine>::lineFunctionAdd(
    typename Engine::G2Point& r,
    typename Engine::G2PointAffine& p,
    typename Engine::G1PointAffine& q,
    typename Engine::F2Element& r2,
    typename Engine::F2Element& a,
    typename Engine::F2Element& b,
    typename Engine::F2Element& c,
    typename Engine::G2Point& rOut)
{
    typename Engine::F2Element B, D, H, I, E1, J, L1, V, t, t2;

    E.f2.mul(B, p.x, r.zzz);
    E.f2.add(D, p.y, r.zz);
    E.f2.square(D, D);
    E.f2.sub(D, D, r2);
    E.f2.sub(D, D, r.zzz);
    E.f2.mul(D, D, r.zzz);

    E.f2.sub(H, B, r.x);
    E.f2.square(I, H);
    E.f2.add(E1, I, I);
    E.f2.add(E1, E1, E1);
    E.f2.mul(J, H, E1);
    E.f2.sub(L1, D, r.y);
    E.f2.sub(L1, L1, r.y);
    E.f2.mul(V, r.x, E1);

    E.f2.square(rOut.x, L1);
    E.f2.sub(rOut.x, rOut.x, J);
    E.f2.sub(rOut.x, rOut.x, V);
    E.f2.sub(rOut.x, rOut.x, V);

    E.f2.add(rOut.zz, r.zz, H);
    E.f2.square(rOut.zz, rOut.zz);
    E.f2.sub(rOut.zz, rOut.zz, r.zzz);
    E.f2.sub(rOut.zz, rOut.zz, I);

    E.f2.sub(t, V, rOut.x);
    E.f2.mul(t, t, L1);
    E.f2.mul(t2, r.y, J);
    E.f2.add(t2, t2, t2);
    E.f2.sub(rOut.y, t, t2);
    E.f2.square(rOut.zzz, rOut.zz);

    E.f2.add(t, p.y, rOut.zz);
    E.f2.square(t, t);
    E.f2.sub(t, t, r2);
    E.f2.sub(t, t, rOut.zzz);

    E.f2.mul(t2, L1, p.x);
    E.f2.add(t2, t2, t2);

    E.f2.sub(a, t2, t);

    E.f2.mulScalar(c, rOut.zz, q.y);
    E.f2.add(c, c, c);

    E.f2.copy(b, E.f2.zero());
    E.f2.sub(b, b, L1);
    E.f2.mulScalar(b, b, q.x);
    E.f2.add(b, b, b);
}

template <typename Engine>
void Verifier<Engine>::lineFunctionDouble(
    typename Engine::G2Point& r,
    typename Engine::G1PointAffine& q,
    typename Engine::F2Element& a,
    typename Engine::F2Element& b,
    typename Engine::F2Element& c,
    typename Engine::G2Point& rOut)
{
    typename Engine::F2Element A, B, C_, D, E1, G, t;

    E.f2.square(A, r.x);
    E.f2.square(B, r.y);
    E.f2.square(C_, B);
    E.f2.add(D, r.x, B);
    E.f2.square(D, D);
    E.f2.sub(D, D, A);
    E.f2.sub(D, D, C_);
    E.f2.add(D, D, D);

    E.f2.add(E1, A, A);
    E.f2.add(E1, E1, A);
    E.f2.square(G, E1);
    E.f2.sub(rOut.x, G, D);
    E.f2.sub(rOut.x, rOut.x, D);

    E.f2.add(rOut.zz, r.y, r.zz);
    E.f2.square(rOut.zz, rOut.zz);
    E.f2.sub(rOut.zz, rOut.zz, B);
    E.f2.sub(rOut.zz, rOut.zz, r.zzz);

    E.f2.sub(rOut.y, D, rOut.x);
    E.f2.mul(rOut.y, rOut.y, E1);

    E.f2.add(t, C_, C_);
    E.f2.add(t, t, t);
    E.f2.add(t, t, t);
    E.f2.sub(rOut.y, rOut.y, t);
    E.f2.square(rOut.zzz, rOut.zz);

    E.f2.mul(t, E1, r.zzz);
    E.f2.add(t, t, t);
    E.f2.copy(b, E.f2.zero());
    E.f2.sub(b, b, t);
    E.f2.mulScalar(b, b, q.x);

    E.f2.add(a, r.x, E1);
    E.f2.square(a, a);
    E.f2.sub(a, a, A);
    E.f2.sub(a, a, G);
    E.f2.add(t, B, B);
    E.f2.add(t, t, t);
    E.f2.sub(a, a, t);

    E.f2.mul(c, rOut.zz, r.zzz);
    E.f2.add(c, c, c);
    E.f2.mulScalar(c, c, q.y);
}

template <typename Engine>
void Verifier<Engine>::mulLine(
    typename Engine::F12Element& ret,
    typename Engine::F2Element& a,
    typename Engine::F2Element& b,
    typename Engine::F2Element& c)
{
    typename Engine::F6Element a2, t3, t2;
    typename Engine::F2Element t;

    E.f2.copy(a2.x, E.f2.zero());
    E.f2.copy(a2.y, a);
    E.f2.copy(a2.z, b);

    E.f6.mul(a2, a2, ret.x);
    E.f6.mulScalar(t3, ret.y, c);

    E.f2.add(t, b, c);
    E.f2.copy(t2.x, E.f2.zero());
    E.f2.copy(t2.y, a);
    E.f2.copy(t2.z, t);
    E.f6.add(ret.x, ret.x, ret.y);

    E.f6.copy(ret.y, t3);

    E.f6.mul(ret.x, ret.x, t2);
    E.f6.sub(ret.x, ret.x, a2);
    E.f6.sub(ret.x, ret.x, ret.y);
    E.f6.mulTau(a2, a2);
    E.f6.add(ret.y, ret.y, a2);
}

template <typename Engine>
typename Engine::F12Element
Verifier<Engine>::miller(typename Engine::G2Point& q, typename Engine::G1Point& p)
{

    const int  sixuPlus2NAF[] =  {0, 0, 0, 1, 0, 1, 0, -1, 0, 0, 1, -1, 0, 0, 1, 0,
                                  0, 1, 1, 0, -1, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1, 1,
                                  1, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 1,
                                  1, 0, 0, -1, 0, 0, 0, 1, 1, 0, -1, 0, 0, 1, 0, 1, 1};

    typename Engine::F12Element ret = E.f12.one();

    typename Engine::G2PointAffine aAffine, minusA;
    typename Engine::G1PointAffine bAffine;
    typename Engine::G2Point r, newR;
    typename Engine::F2Element r2, a, b, c;

    E.g2.copy(aAffine, q);
    E.g1.copy(bAffine, p);
    E.g2.neg(minusA, aAffine);
    E.g2.copy(r, aAffine);

    E.f2.square(r2, aAffine.y);

    const size_t count = sizeof(sixuPlus2NAF)/sizeof(sixuPlus2NAF[0]) - 1;

    for (int i = count; i > 0; i--) {

        lineFunctionDouble(r, bAffine, a, b, c, newR);

        if (i != count) {
            E.f12.square(ret, ret);
        }

        mulLine(ret, a, b, c);
        E.g2.copy(r, newR);

        switch (sixuPlus2NAF[i-1]) {
        case 1:
            lineFunctionAdd(r, aAffine, bAffine, r2, a, b, c, newR);
            break;
        case -1:
            lineFunctionAdd(r, minusA, bAffine, r2, a, b, c, newR);
            break;

        default:
            continue;
        }

        mulLine(ret, a, b, c);
        E.g2.copy(r, newR);
    }

    typename Engine::G2Point q1;

    E.f2.conjugate(q1.x, aAffine.x);
    E.f2.mul(q1.x, q1.x, xiToPMinus1Over3);
    E.f2.conjugate(q1.y, aAffine.y);
    E.f2.mul(q1.y, q1.y, xiToPMinus1Over2);
    E.f2.copy(q1.zz, E.f2.one());
    E.f2.copy(q1.zzz, E.f2.one());

    typename Engine::G2Point minusQ2;

    E.f2.mulScalar(minusQ2.x, aAffine.x, xiToPSquaredMinus1Over3);
    E.f2.copy(minusQ2.y, aAffine.y);
    E.f2.copy(minusQ2.zz, E.f2.one());
    E.f2.copy(minusQ2.zzz, E.f2.one());

    E.f2.square(r2, q1.y);

    typename Engine::G2PointAffine q1Affine;
    E.g2.copy(q1Affine, q1);

    lineFunctionAdd(r, q1Affine, bAffine, r2, a, b, c, newR);
    mulLine(ret, a, b, c);
    E.g2.copy(r, newR);

    typename Engine::G2PointAffine minusQ2Affine;
    E.g2.copy(minusQ2Affine, minusQ2);

    E.f2.square(r2, minusQ2.y);
    lineFunctionAdd(r, minusQ2Affine, bAffine, r2, a, b, c, newR);
    mulLine(ret, a, b, c);
    E.g2.copy(r, newR);

    return ret;
}

template <typename Engine>
typename Engine::F12Element
Verifier<Engine>::finalExponentiation(typename Engine::F12Element& in)
{
    typename Engine::F12Element t1, inv, t2, fp, fp2, fp3, fu, fu2, fu3, y3, fu2p, fu3p;
    typename Engine::F12Element y2, y0, y1, y4, y5, y6, t0;

    uint64_t u = 4965661367192848881;

    E.f6.neg(t1.x, in.x);
    E.f6.copy(t1.y, in.y);

    E.f12.inv(inv, in);
    E.f12.mul(t1, t1, inv);

    E.f12.FrobeniusP2(t2, t1);
    E.f12.mul(t1, t1, t2);

    E.f12.Frobenius(fp, t1);
    E.f12.FrobeniusP2(fp2, t1);
    E.f12.Frobenius(fp3, fp2);

    E.f12.exp(fu,  t1, (uint8_t*)&u, sizeof(u));
    E.f12.exp(fu2, fu, (uint8_t*)&u, sizeof(u));
    E.f12.exp(fu3, fu2, (uint8_t*)&u, sizeof(u));

    E.f12.Frobenius(y3, fu);
    E.f12.Frobenius(fu2p, fu2);
    E.f12.Frobenius(fu3p, fu3);
    E.f12.FrobeniusP2(y2, fu2);

    E.f12.mul(y0, fp, fp2);
    E.f12.mul(y0, y0, fp3);

    E.f12.conjugate(y1, t1);
    E.f12.conjugate(y5, fu2);
    E.f12.conjugate(y3, y3);
    E.f12.mul(y4, fu, fu2p);
    E.f12.conjugate(y4, y4);

    E.f12.mul(y6, fu3, fu3p);
    E.f12.conjugate(y6, y6);

    E.f12.square(t0, y6);
    E.f12.mul(t0, t0, y4);
    E.f12.mul(t0, t0, y5);
    E.f12.mul(t1, y3, y5);
    E.f12.mul(t1, t1, t0);
    E.f12.mul(t0, t0, y2);

    E.f12.square(t1, t1);
    E.f12.mul(t1, t1, t0);
    E.f12.square(t1, t1);
    E.f12.mul(t0, t1, y1);
    E.f12.mul(t1, t1, y0);
    E.f12.square(t0, t0);
    E.f12.mul(t0, t0, t1);

    return t0;
}

template <typename Engine>
bool Verifier<Engine>::pairingCheck(G1PointArray& a, G2PointArray& b)
{
    typename Engine::F12Element acc = E.f12.one();

    for (int i = 0; i < a.size(); i++) {

        if (E.g1.isZero(a[i]) || E.g2.isZero(b[i])) {
            continue;
        }

        auto millerRes = miller(b[i], a[i]);
        E.f12.mul(acc, acc, millerRes);
    }

    auto ret = finalExponentiation(acc);

    return E.f12.isOne(ret);
}

} // namespace
