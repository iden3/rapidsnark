#ifndef BINFILE_UTILS_H
#define BINFILE_UTILS_H
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "fileloader.hpp"

namespace BinFileUtils {
    
    class BinFile {

        FileLoader fileLoader;

        const void *addr;
        u_int64_t size;
        u_int64_t pos;

        class Section {
            void *start;
            u_int64_t size;

        public:

            friend BinFile;
            Section(void *_start, u_int64_t _size)  : start(_start), size(_size) {};
        };

        std::map<int,std::vector<Section>> sections;
        std::string type;
        u_int32_t version;

        Section *readingSection;

        void readFileData(std::string _type, uint32_t maxVersion);

    public:

        BinFile(const void *fileData, size_t fileSize, std::string _type, uint32_t maxVersion);
        BinFile(const std::string& fileName, const std::string& _type, uint32_t maxVersion);
        BinFile(const BinFile&) = delete;
        BinFile& operator=(const BinFile&) = delete;

        void startReadSection(u_int32_t sectionId, u_int32_t setionPos = 0);
        void endReadSection(bool check = true);

        void *getSectionData(u_int32_t sectionId, u_int32_t sectionPos = 0);
        u_int64_t getSectionSize(u_int32_t sectionId, u_int32_t sectionPos = 0);

        u_int32_t readU32LE();
        u_int64_t readU64LE();

        void *read(uint64_t l);
    };

    std::unique_ptr<BinFile> openExisting(const std::string& filename, const std::string& type, uint32_t maxVersion);
}

#endif // BINFILE_UTILS_H
