#include "FileLoader.h"

#include <fstream>

namespace file
{

std::string loadTextFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);
    const std::string content{std::istreambuf_iterator<char>(ifs),
                              std::istreambuf_iterator<char>()};
    return content;
}

} // namespace file
