//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_SHADER_HPP
#define AZATHOTH_SHADER_HPP

#include <string>

namespace renderer {

    class Shader {
    public:
        Shader(std::string const& vertexShaderSrc, std::string const& fragmentShaderSrc);
        ~Shader();
    public:
        void bind() const;
        void unBind() const;
    private:
        uint32_t m_rendererId;
    };

}

#endif //AZATHOTH_SHADER_HPP
