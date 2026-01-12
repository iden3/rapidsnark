#include "zkey_utils.hpp"

#include <stdexcept>

namespace ZKeyUtils {

    Header::Header()
        : n8q(0),
          n8r(0),
          nVars(0),
          nPublic(0),
          domainSize(0),
          nCoefs(0),
          vk_alpha1(nullptr),
          vk_beta1(nullptr),
          vk_beta2(nullptr),
          vk_gamma2(nullptr),
          vk_delta1(nullptr),
          vk_delta2(nullptr)
    {
    }

    Header::~Header() = default;

    std::unique_ptr<Header> loadHeader(BinFileUtils::BinFile *f) {
        auto h = new Header();

        f->startReadSection(1);
        uint32_t protocol = f->readU32LE();
        if (protocol != 1) {
            throw std::invalid_argument( "zkey file is not groth16" );
        }
        f->endReadSection();

        f->startReadSection(2);

        h->n8q = f->readU32LE();
        {
            const uint8_t* p = reinterpret_cast<const uint8_t*>(f->read(h->n8q));
            h->qPrime.assign(p, p + h->n8q);
        }

        h->n8r = f->readU32LE();
        {
            const uint8_t* p = reinterpret_cast<const uint8_t*>(f->read(h->n8r));
            h->rPrime.assign(p, p + h->n8r);
        }

        h->nVars = f->readU32LE();
        h->nPublic = f->readU32LE();
        h->domainSize = f->readU32LE();

        h->vk_alpha1 = f->read(h->n8q*2);
        h->vk_beta1 = f->read(h->n8q*2);
        h->vk_beta2 = f->read(h->n8q*4);
        h->vk_gamma2 = f->read(h->n8q*4);
        h->vk_delta1 = f->read(h->n8q*2);
        h->vk_delta2 = f->read(h->n8q*4);
        f->endReadSection();

        h->nCoefs = f->getSectionSize(4) / (12 + h->n8r);

        return std::unique_ptr<Header>(h);
    }

} // namespace

