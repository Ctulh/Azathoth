//
// Created by egor on 2/10/22.
//
#include "Renderer/Shader.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"

#include <glad/glad.h>
#include <vector>

namespace renderer {

    Shader::Shader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = vertexShaderSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(vertexShader);

            logger::log_error("[SHADER] {}", infoLog.data());
            AZATHOTH_ASSERT(isCompiled, "Vertex shader compile failed");
            return;
        }
        logger::log_info("[SHADER] Created vertex shader");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentShaderSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            logger::log_error("[SHADER] {}", infoLog.data());
            AZATHOTH_ASSERT(isCompiled, "Fragment shader compile failed");
            return;
        }
        logger::log_info("[SHADER] Created fragment shader");

        m_rendererId = glCreateProgram();

        glAttachShader(m_rendererId, vertexShader);
        glAttachShader(m_rendererId, fragmentShader);

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
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            logger::log_error("[SHADER] {}", infoLog.data());
            AZATHOTH_ASSERT(isCompiled, "Shader link failed");
            return;
        }

        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);
    }

    Shader::~Shader() {
       glDeleteProgram(m_rendererId);
    }

    void Shader::bind() const {
        glUseProgram(m_rendererId);
    }

    void Shader::unBind() const {
        glUseProgram(0);
    }

}