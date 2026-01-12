#include "wtns_utils.hpp"

namespace WtnsUtils {

    Header::Header()
        : n8(0),
          nVars(0)
    {
    }

    Header::~Header() = default;

    std::unique_ptr<Header> loadHeader(BinFileUtils::BinFile *f) {
        std::unique_ptr<Header> h(new Header());

        f->startReadSection(1);

        h->n8 = f->readU32LE();
        {
            const uint8_t* p = reinterpret_cast<const uint8_t*>(f->read(h->n8));
            h->prime.assign(p, p + h->n8);
        }

        h->nVars = f->readU32LE();

        f->endReadSection();

        return h;
    }

} // namespace WtnsUtils
