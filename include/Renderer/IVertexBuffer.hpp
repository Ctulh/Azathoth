//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_IVERTEXBUFFER_HPP
#define AZATHOTH_IVERTEXBUFFER_HPP

#include <cstdint>

#include "BufferLayout.hpp"

namespace renderer {

    class IVertexBuffer {
    public:
        virtual ~IVertexBuffer() = default;
    public:
        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual void setLayout(BufferLayout const&) = 0;
        virtual BufferLayout const& getLayout() const = 0;

        static IVertexBuffer* create(float*, uint32_t);
    };

}

#endif //AZATHOTH_IVERTEXBUFFER_HPP
