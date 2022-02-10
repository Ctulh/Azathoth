//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_IINDEXBUFFER_HPP
#define AZATHOTH_IINDEXBUFFER_HPP

#include <stdint.h>

namespace renderer {

    class IIndexBuffer {
    public:
        ~IIndexBuffer() = default;
    public:
        virtual void bind() = 0;
        virtual void unBind() = 0;

     //   static IIndexBuffer* create(uint32_t*, uint32_t);
    };

}

#endif //AZATHOTH_IINDEXBUFFER_HPP
