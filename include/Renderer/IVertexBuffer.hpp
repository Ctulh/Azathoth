//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_IVERTEXBUFFER_HPP
#define AZATHOTH_IVERTEXBUFFER_HPP

#include <stdint.h>

namespace renderer {

    class IVertexBuffer {
    public:
        virtual ~IVertexBuffer() = default;
    public:
        virtual void bind() = 0;
        virtual void unBind() = 0;

       // static IVertexBuffer* create(float*, uint32_t);
    };

}

#endif //AZATHOTH_IVERTEXBUFFER_HPP
