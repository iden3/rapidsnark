#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <cstddef>
#include <string>

namespace BinFileUtils {

class FileLoader
{
public:
    FileLoader();
    FileLoader(const std::string& fileName);
    ~FileLoader();

    void load(const std::string& fileName);

    void*  dataBuffer() { return addr; }
    size_t dataSize() const { return size; }

    std::string dataAsString() { return std::string((char*)addr, size); }

private:
    void*   addr;
    size_t  size;
    int     fd;
};

}

#endif // FILELOADER_HPP
