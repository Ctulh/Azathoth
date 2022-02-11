//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_VERTEXARRAY_HPP
#define AZATHOTH_VERTEXARRAY_HPP

#include <memory>
#include <vector>

#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/IIndexBuffer.hpp"

namespace renderer {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual void addVertexBuffer(std::shared_ptr<IVertexBuffer>) = 0;
        virtual void setIndexBuffer(std::shared_ptr<IIndexBuffer>) = 0;

        virtual std::vector<std::shared_ptr<IVertexBuffer>> const& getVertexBuffers() const = 0;
        virtual std::shared_ptr<IIndexBuffer> const& getIndexBuffer() const = 0;

        static VertexArray* create();
    };

}

#endif //AZATHOTH_VERTEXARRAY_HPP
