#include "FileWriter.h"

#include <fstream>

namespace file
{

bool writeTextFile(std::string filePath, const std::string& fileContent)
{
    std::ofstream file;
    file.open(filePath);
    if (!file) {
        return false;
    }
    file << fileContent;
    return true;
}

} // namespace file
