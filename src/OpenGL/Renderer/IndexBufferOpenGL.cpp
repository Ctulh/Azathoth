//
// Created by egor on 2/11/22.
//

#include "Renderer/IIndexBuffer.hpp"
#include "Renderer/IndexBufferOpenGL.hpp"
#include <glad/glad.h>

namespace renderer {

    IndexBufferOpenGL::IndexBufferOpenGL(uint32_t* indices, uint32_t count): m_count(count) {
        glCreateBuffers(1, &m_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12, indices, GL_STATIC_DRAW);
    }

    void IndexBufferOpenGL::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    }

    void IndexBufferOpenGL::unBind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBufferOpenGL::getCount() const {
        return m_count;
    }

    IndexBufferOpenGL::~IndexBufferOpenGL() {
        glDeleteBuffers(1, &m_rendererId);
    }

    IIndexBuffer *IIndexBuffer::create(uint32_t* indices, uint32_t count) {
        return new IndexBufferOpenGL(indices, count);
    }
}
