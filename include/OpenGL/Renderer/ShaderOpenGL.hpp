//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_SHADEROPENGL_HPP
#define AZATHOTH_SHADEROPENGL_HPP

#include <string>
#include <unordered_map>

#include "Renderer/IShader.hpp"

namespace renderer {

    class ShaderOpenGL: public IShader {
    public:
        ShaderOpenGL(std::string const& vertexFileName, std::string const& shaderFileName);
        ~ShaderOpenGL();
    public:
        void bind() const override;
        void unBind() const override;
        void setUniformMatrix4f(std::string const&, const float *) override;
    private:
        uint32_t compileShader(unsigned int shaderType, std::string const&) const;
        int getUniformLocation(std::string const&);
        void createProgram(std::initializer_list<uint32_t>);
    private:
        uint32_t m_rendererId;
        std::unordered_map<std::string, int> m_uniformIndexes;
    };

}

#endif //AZATHOTH_SHADEROPENGL_HPP
