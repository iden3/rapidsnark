#include "wtns_utils.hpp"

namespace WtnsUtils {

Header::Header() {
    mpz_init(prime);
}

Header::~Header() {
    mpz_clear(prime);
}

std::unique_ptr<Header> loadHeader(BinFileUtils::BinFile *f) {
    std::unique_ptr<Header> h(new Header());

    f->startReadSection(1);

    h->n8 = f->readU32LE();
    mpz_import(h->prime, h->n8, -1, 1, -1, 0, f->read(h->n8));

    h->nVars = f->readU32LE();

    f->endReadSection();

    return h;
}

} // NAMESPACE
