//
// Created by egor on 2/12/22.
//
#include <fstream>

#include "Tools/config.h"
#include "Tools/File.hpp"
#include "Tools/AzathothAssert.hpp"

namespace tools {

    std::string File::read() const {
        std::string fileData;
        std::ifstream file(std::string(SHADERS_PATH) + "/"+ m_filePath);

        AZATHOTH_ASSERT(file.is_open(), "Error cant open file");
        file.seekg(0, std::fstream::end);
        int fileSize = file.tellg();
        AZATHOTH_ASSERT(fileSize, "Error while read file");
        fileData.reserve(fileSize);

        file.seekg(0, std::fstream::beg);

        std::string buffer;
        while(std::getline(file, buffer)) {
            fileData += buffer + '\n';
        }
        return fileData;
    }

}
