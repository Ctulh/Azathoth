//
// Created by egor on 2/11/22.
//
#include <glad/glad.h>

#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/VertexBufferOpenGL.hpp"

namespace renderer {

    VertexBufferOpenGL::VertexBufferOpenGL(float* vertices, uint32_t size) {
        glCreateBuffers(1, &m_rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBufferOpenGL::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    }

    void VertexBufferOpenGL::unBind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBufferOpenGL::setLayout(BufferLayout const& layout) {
        m_layout = layout;
    }

    BufferLayout const& VertexBufferOpenGL::getLayout() const {
        return m_layout;
    }

    VertexBufferOpenGL::~VertexBufferOpenGL() {
        glDeleteBuffers(1, &m_rendererId);
    }

    IVertexBuffer *IVertexBuffer::create(float* vertices, uint32_t size) {
        return new VertexBufferOpenGL(vertices, size);
    }
}
