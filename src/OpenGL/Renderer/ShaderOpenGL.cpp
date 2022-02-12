//
// Created by egor on 2/10/22.
//
#include "Renderer/ShaderOpenGL.hpp"
#include "Logger/Logger.hpp"
#include "Tools/AzathothAssert.hpp"
#include "Tools/File.hpp"

#include "glad/glad.h"
#include <vector>

namespace renderer {

    ShaderOpenGL::ShaderOpenGL(std::string const& vertexFileName, std::string const& fragmentFileName) {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexFileName);
        logger::log_info("[SHADER] Compiled vertex shader");
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFileName);
        logger::log_info("[SHADER] Compiled fragment shader");

        createProgram({vertexShader, fragmentShader});
    }

    ShaderOpenGL::~ShaderOpenGL() {
       glDeleteProgram(m_rendererId);
    }

    void ShaderOpenGL::bind() const {
        glUseProgram(m_rendererId);
    }

    void ShaderOpenGL::unBind() const {
        glUseProgram(0);
    }

    void ShaderOpenGL::setUniformMatrix4f(std::string const& uniformName, const float* matrix4f) {
        glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, matrix4f);
    }

    uint32_t ShaderOpenGL::compileShader(unsigned int shaderType, std::string const& shaderPath) const {
        GLuint shaderId = glCreateShader(shaderType);

        auto shaderData = tools::File(shaderPath).read();
        const GLchar *source = shaderData.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);

        glCompileShader(shaderId);

        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(shaderId);

            logger::log_error("[SHADER] {}", infoLog.data());
            AZATHOTH_ASSERT(isCompiled, " Shader compile failed, shader: " + shaderType);
            return 0;
        }
        return shaderId;
    }

    void ShaderOpenGL::createProgram(std::initializer_list<uint32_t> shaders) {
        m_rendererId = glCreateProgram();

        for(auto const& shaderId: shaders) {
            glAttachShader(m_rendererId, shaderId);
        }

        glLinkProgram(m_rendererId);


        GLint isLinked = 0;
        glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(m_rendererId);

            for(auto const& shaderId: shaders) {
                glDeleteShader(shaderId);
            }

            logger::log_error("[SHADER] {}", infoLog.data());
            AZATHOTH_ASSERT(isCompiled, "Shader link failed");
            return;
        }

        for(auto const& shaderId: shaders) {
            glDetachShader(m_rendererId, shaderId);
        }
    }

    int ShaderOpenGL::getUniformLocation(std::string const& uniformName) {
        if(m_uniformIndexes.contains(uniformName)) {
            return m_uniformIndexes.at(uniformName);
        }
        GLint location = glGetUniformLocation(m_rendererId, uniformName.c_str());
        m_uniformIndexes[uniformName] = location;
        AZATHOTH_ASSERT(location, "Cant find uniform with name: " + uniformName);
        return location;
    }

}