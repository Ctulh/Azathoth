//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_VERTEXARRAYOPENGL_HPP
#define AZATHOTH_VERTEXARRAYOPENGL_HPP

#include "Renderer/VertexArray.hpp"

namespace renderer {

    class VertexArrayOpenGL: public VertexArray {
    public:
        VertexArrayOpenGL();
        ~VertexArrayOpenGL();
    public:
        void bind() const override;
        void unBind() const override;

        void addVertexBuffer(std::shared_ptr<IVertexBuffer>) override;
        void setIndexBuffer(std::shared_ptr<IIndexBuffer>) override;

        std::vector<std::shared_ptr<IVertexBuffer>> const& getVertexBuffers() const override;
        std::shared_ptr<IIndexBuffer> const& getIndexBuffer() const override;

    private:
        std::vector<std::shared_ptr<IVertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IIndexBuffer> m_indexBuffer;
        uint32_t m_rendererId;
    };

}

#endif //AZATHOTH_VERTEXARRAYOPENGL_HPP
