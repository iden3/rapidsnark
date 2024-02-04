#ifndef GROTH16_HPP
#define GROTH16_HPP

#include <string>
#include <array>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "fft.hpp"

namespace Groth16 {

    template <typename Engine>
    class Proof {
        Engine &E;
    public:
        typename Engine::G1PointAffine A;
        typename Engine::G2PointAffine B;
        typename Engine::G1PointAffine C;

        Proof(Engine &_E) : E(_E) { }
        std::string toJsonStr();
        json toJson();
        void fromJson(const json& proof);
    };

    template <typename Engine>
    class VerificationKey {
        Engine &E;
    public:
        typename Engine::G1PointAffine Alpha;
        typename Engine::G2PointAffine Beta;
        typename Engine::G2PointAffine Gamma;
        typename Engine::G2PointAffine Delta;
        std::vector<typename Engine::G1PointAffine> IC;

        VerificationKey(Engine &_E) : E(_E) { }
        void fromJson(const json& proof);
    };

 #pragma pack(push, 1)
    template <typename Engine>
    struct Coef {
        u_int32_t m;
        u_int32_t c;
        u_int32_t s;
        typename Engine::FrElement coef;
    };
#pragma pack(pop)

    template <typename Engine>
    class Prover {

        Engine &E;
        u_int32_t nVars;
        u_int32_t nPublic;
        u_int32_t domainSize;
        u_int64_t nCoefs;
        typename Engine::G1PointAffine &vk_alpha1;
        typename Engine::G1PointAffine &vk_beta1;
        typename Engine::G2PointAffine &vk_beta2;
        typename Engine::G1PointAffine &vk_delta1;
        typename Engine::G2PointAffine &vk_delta2;
        Coef<Engine> *coefs;
        typename Engine::G1PointAffine *pointsA;
        typename Engine::G1PointAffine *pointsB1;
        typename Engine::G2PointAffine *pointsB2;
        typename Engine::G1PointAffine *pointsC;
        typename Engine::G1PointAffine *pointsH;

        FFT<typename Engine::Fr> *fft;
    public:
        Prover(
            Engine &_E, 
            u_int32_t _nVars, 
            u_int32_t _nPublic, 
            u_int32_t _domainSize, 
            u_int64_t _nCoefs, 
            typename Engine::G1PointAffine &_vk_alpha1,
            typename Engine::G1PointAffine &_vk_beta1,
            typename Engine::G2PointAffine &_vk_beta2,
            typename Engine::G1PointAffine &_vk_delta1,
            typename Engine::G2PointAffine &_vk_delta2,
            Coef<Engine> *_coefs, 
            typename Engine::G1PointAffine *_pointsA,
            typename Engine::G1PointAffine *_pointsB1,
            typename Engine::G2PointAffine *_pointsB2,
            typename Engine::G1PointAffine *_pointsC,
            typename Engine::G1PointAffine *_pointsH
        ) : 
            E(_E), 
            nVars(_nVars),
            nPublic(_nPublic),
            domainSize(_domainSize),
            nCoefs(_nCoefs),
            vk_alpha1(_vk_alpha1),
            vk_beta1(_vk_beta1),
            vk_beta2(_vk_beta2),
            vk_delta1(_vk_delta1),
            vk_delta2(_vk_delta2),
            coefs(_coefs),
            pointsA(_pointsA),
            pointsB1(_pointsB1),
            pointsB2(_pointsB2),
            pointsC(_pointsC),
            pointsH(_pointsH)
        { 
            fft = new FFT<typename Engine::Fr>(domainSize*2);
        }

        ~Prover() {
            delete fft;
        }

        std::unique_ptr<Proof<Engine>> prove(typename Engine::FrElement *wtns);
    };

    template <typename Engine>
    std::unique_ptr<Prover<Engine>> makeProver(
        u_int32_t nVars, 
        u_int32_t nPublic, 
        u_int32_t domainSize, 
        u_int64_t nCoefs, 
        void *vk_alpha1,
        void *vk_beta1,
        void *vk_beta2,
        void *vk_delta1,
        void *vk_delta2,
        void *coefs,
        void *pointsA,
        void *pointsB1,
        void *pointsB2,
        void *pointsC,
        void *pointsH
    );

    template <typename Engine>
    class Verifier {

        typedef std::vector<typename Engine::Fr::Element> InputsVector;
        typedef std::array<typename Engine::G1Point, 4> G1PointArray;
        typedef std::array<typename Engine::G2Point, 4> G2PointArray;

        Engine &E;

    public:
        Verifier();

        bool verify(
            Proof<Engine> &proof,
            InputsVector &inputs,
            VerificationKey<Engine> &key);

    private:
        bool pairingCheck(G1PointArray& g1, G2PointArray& g2);

        typename Engine::F12Element miller(typename Engine::G2Point& b, typename Engine::G1Point& a);

        typename Engine::F12Element finalExponentiation(typename Engine::F12Element& in);

        void lineFunctionDouble(
            typename Engine::G2Point& r,
            typename Engine::G1PointAffine& q,
            typename Engine::F2Element& a,
            typename Engine::F2Element& b,
            typename Engine::F2Element& c,
            typename Engine::G2Point& rOut);

        void lineFunctionAdd(
            typename Engine::G2Point& r,
            typename Engine::G2PointAffine& p,
            typename Engine::G1PointAffine& q,
            typename Engine::F2Element& r2,
            typename Engine::F2Element& a,
            typename Engine::F2Element& b,
            typename Engine::F2Element& c,
            typename Engine::G2Point& rOut);

        void mulLine(
            typename Engine::F12Element& ret,
            typename Engine::F2Element& a,
            typename Engine::F2Element& b,
            typename Engine::F2Element& c);

    private:
        typename Engine::F2Element xiToPMinus1Over3;
        typename Engine::F2Element xiToPMinus1Over2;
        typename Engine::F1Element xiToPSquaredMinus1Over3;
    };
}


#include "groth16.cpp"

#endif
