#ifndef GROTH16_HPP
#define GROTH16_HPP

#include <string>
#include <array>
#include <map>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "fft.hpp"

namespace Groth16 {

    // The FFT roots table and the bit-reversed coset table depend on nothing but
    // the scalar field and the domain size -- not the circuit, the points, or the
    // witness. Two provers for entirely different circuits that share a domain
    // size can therefore share both, which matters because they are 64 MB each
    // at 2^21 and a service typically holds one prover per circuit it serves.
    //
    // Safe to share while proofs run concurrently: the transforms read
    // roots/powTwoInv only through root(), rootInv() and nInv(), and write
    // solely to the caller's array, so FFT holds no per-proof state.
    template <typename Engine>
    class DomainTables {
        Engine &E;

        // Only the constructor and destructor touch these. Everyone else goes
        // through the accessors below, which cannot hand back anything
        // writable -- so the compiler, not convention, keeps a shared table
        // immutable for the provers borrowing it.
        FFT<typename Engine::Fr> *fft_;
        typename Engine::FrElement *cosetBR_;
    public:
        const u_int32_t domainSize;

        // FFT is handed out non-const because its transform methods are not
        // const-qualified (their Field member's arithmetic isn't), but it
        // exposes no way to write the tables: root()/rootInv()/nInv() return
        // const references and every other method writes only to the caller's
        // array.
        FFT<typename Engine::Fr> &fft() const { return *fft_; }

        const typename Engine::FrElement *cosetBR() const { return cosetBR_; }

        DomainTables(Engine &_E, u_int32_t _domainSize)
            : E(_E), fft_(nullptr), cosetBR_(nullptr), domainSize(_domainSize)
        {
            // The transforms only ever run at domainSize; the finer omega_2n
            // needed for the coset shift is derived directly instead of
            // paying for a roots table twice the transform size.
            fft_ = new FFT<typename Engine::Fr>(domainSize);

            // Coset shift ω_2n^BR(i) with the iFFT's 1/n folded in, indexed
            // in bit-reversed order for the permutation-free h pipeline.
            // Built once; reused by every proof of every prover sharing this
            // domain size.
            cosetBR_ = new typename Engine::FrElement[domainSize];

            u_int32_t domainPow = fft_->log2(domainSize);

            typename Engine::FrElement w2n;
            fft_->higherRootOfUnity(w2n, 1);

            const typename Engine::FrElement nInv = fft_->nInv(domainPow);

            // One pass, no scratch array. Walking the exponent j upward lets
            // each power chain from the previous one, and folding 1/n into the
            // per-thread seed leaves a single multiply per element. The value is
            // stored at BR(j) rather than j: BR is an involution, so sequential
            // j fills exactly the bit-reversed table the h pipeline reads, and
            // it is a bijection, so threads owning disjoint j ranges write
            // disjoint slots.
            //
            // The previous form scanned the powers into a domainSize scratch
            // array and permuted in a second pass -- two multiplies per element,
            // and a second full-size table alive beside cosetBR (64 MB each at
            // 2^21).
            ThreadPool::defaultPool().parallelFor(0, domainSize, [&] (int begin, int end, int numThread) {
                if (begin >= end) return;

                u_int64_t k = begin;
                typename Engine::FrElement v;

                E.fr.exp(v, w2n, (uint8_t *)&k, sizeof(k));
                E.fr.mul(v, v, nInv);

                for (u_int64_t j = begin; j < (u_int64_t)end; j++) {
                    E.fr.copy(cosetBR_[BR(j, domainPow)], v);
                    E.fr.mul(v, v, w2n);
                }
            });
        }

        ~DomainTables() {
            delete fft_;
            delete [] cosetBR_;
        }

        DomainTables(const DomainTables &) = delete;
        DomainTables &operator=(const DomainTables &) = delete;
    };

    // Hand out the tables for a domain size, building them only if nobody holds
    // them yet. The registry keeps weak references, so the tables are freed as
    // soon as the last prover using them goes away -- a lone prover behaves
    // exactly as before, allocating on construction and freeing on destruction.
    //
    // The statics live in a template function, so every Engine gets its own
    // registry and the domain size alone is a complete key.
    //
    // Construction runs under the lock: two provers of the same size must not
    // both build, and holding it across the build keeps that simple, at the cost
    // of briefly serialising construction of different sizes too. That is paid
    // once per domain size per process, against a build of tens of milliseconds.
    template <typename Engine>
    std::shared_ptr<const DomainTables<Engine>> acquireDomainTables(Engine &E,
                                                              u_int32_t domainSize)
    {
        static std::mutex mutex;
        static std::map<u_int32_t, std::weak_ptr<const DomainTables<Engine>>> registry;

        std::lock_guard<std::mutex> guard(mutex);

        auto it = registry.find(domainSize);

        if (it != registry.end()) {
            if (std::shared_ptr<const DomainTables<Engine>> live = it->second.lock()) {
                return live;
            }
            registry.erase(it);
        }

        std::shared_ptr<const DomainTables<Engine>> made =
            std::make_shared<DomainTables<Engine>>(E, domainSize);

        registry[domainSize] = made;

        return made;
    }

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

        // Shared with any other prover of the same domain size. The raw
        // pointers below are borrowed from it and kept for the hot path; the
        // const handle and const element type make writing a shared table a
        // compile error rather than a convention.
        std::shared_ptr<const DomainTables<Engine>> domainTables;

        FFT<typename Engine::Fr> *fft;
        const typename Engine::FrElement *cosetBR;
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
            domainTables = acquireDomainTables(E, domainSize);

            fft     = &domainTables->fft();
            cosetBR = domainTables->cosetBR();
        }

        ~Prover() {
            // domainTables frees the tables once no prover is holding them.
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
