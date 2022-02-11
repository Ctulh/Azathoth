//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_SHADEROPENGL_HPP
#define AZATHOTH_SHADEROPENGL_HPP

#include <string>

#include "Renderer/IShader.hpp"

namespace renderer {

    class ShaderOpenGL: public IShader {
    public:
        ShaderOpenGL(std::string const& vertexShaderSrc, std::string const& fragmentShaderSrc);
        ~ShaderOpenGL();
    public:
        void bind() const override;
        void unBind() const override;
    private:
        uint32_t m_rendererId;
    };

}

#endif //AZATHOTH_SHADEROPENGL_HPP
