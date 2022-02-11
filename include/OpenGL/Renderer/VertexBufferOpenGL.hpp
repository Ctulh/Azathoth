//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_VERTEXBUFFEROPENGL_HPP
#define AZATHOTH_VERTEXBUFFEROPENGL_HPP

#include "Renderer/IVertexBuffer.hpp"

namespace renderer {

    class VertexBufferOpenGL: public IVertexBuffer {
    public:
        VertexBufferOpenGL(float*, uint32_t);
        ~VertexBufferOpenGL();
    public:
        void bind() const override;
        void unBind() const override;

        void setLayout(const BufferLayout &) override;
        const BufferLayout & getLayout() const override;
    private:
        uint32_t m_rendererId;
        BufferLayout m_layout;
    };

}

#endif //AZATHOTH_VERTEXBUFFEROPENGL_HPP
