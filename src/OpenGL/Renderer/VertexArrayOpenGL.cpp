//
// Created by egor on 2/11/22.
//
#include "Renderer/VertexArrayOpenGL.hpp"
#include "Renderer/VertexArray.hpp"
#include "Tools/AzathothAssert.hpp"

#include <glad/glad.h>


namespace renderer {

    static GLenum ShaderDataTypeToOpenGLBaseType(renderer::ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:   return GL_FLOAT;
            case ShaderDataType::Float2:  return GL_FLOAT;
            case ShaderDataType::Float3:  return GL_FLOAT;
            case ShaderDataType::Float4:  return GL_FLOAT;
            case ShaderDataType::Mat3:    return GL_FLOAT;
            case ShaderDataType::Mat4:    return GL_FLOAT;
            case ShaderDataType::Int:     return GL_INT;
            case ShaderDataType::Int2:    return GL_INT;
            case ShaderDataType::Int3:    return GL_INT;
            case ShaderDataType::Int4:    return GL_INT;
            case ShaderDataType::Bool:    return GL_BOOL;
        }
        AZATHOTH_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }


    VertexArrayOpenGL::VertexArrayOpenGL() {
        glCreateVertexArrays(1, &m_rendererId);
    }

    void VertexArrayOpenGL::bind() const {
        glBindVertexArray(m_rendererId);
    }

    void VertexArrayOpenGL::unBind() const {
        glBindVertexArray(0);
    }

    void VertexArrayOpenGL::addVertexBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer) {
        AZATHOTH_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout");

        glBindVertexArray(m_rendererId);
        vertexBuffer->bind();

        uint32_t index = 0;
        for(auto const& element: vertexBuffer->getLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    element.getComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    vertexBuffer->getLayout().getStride(),
                    (const void*)element.offset);
            index++;
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArrayOpenGL::setIndexBuffer(std::shared_ptr<IIndexBuffer> indexBuffer) {
        glBindVertexArray(m_rendererId);
        indexBuffer->bind();

        m_indexBuffer = indexBuffer;
    }

    std::vector<std::shared_ptr<IVertexBuffer>> const& VertexArrayOpenGL::getVertexBuffers() const {
        return m_vertexBuffers;
    }

    std::shared_ptr<IIndexBuffer> const& VertexArrayOpenGL::getIndexBuffer() const {
        return m_indexBuffer;
    }

    VertexArrayOpenGL::~VertexArrayOpenGL() {
        glDeleteVertexArrays(1, &m_rendererId);
    }

    VertexArray *VertexArray::create() {
        return new VertexArrayOpenGL;
    }

}
