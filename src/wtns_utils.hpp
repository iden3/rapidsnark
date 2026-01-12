#ifndef WTNS_UTILS
#define WTNS_UTILS

#include <cstdint>
#include <memory>
#include <vector>

#include "binfile_utils.hpp"

namespace WtnsUtils {

    class Header {
    public:
        u_int32_t n8;
        std::vector<uint8_t> prime;

        u_int32_t nVars;

        Header();
        ~Header();
    };

    std::unique_ptr<Header> loadHeader(BinFileUtils::BinFile *f);

} // namespace WtnsUtils

#endif // WTNS_UTILS
