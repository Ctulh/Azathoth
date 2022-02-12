//
// Created by egor on 2/12/22.
//

#ifndef AZATHOTH_FILE_HPP
#define AZATHOTH_FILE_HPP

#include <string>

namespace tools {

    class File {
    public:
        explicit File(std::string const& filePath): m_filePath(filePath) {}
        std::string read() const;
    private:
        std::string m_filePath;
    };

}

#endif //AZATHOTH_FILE_HPP
