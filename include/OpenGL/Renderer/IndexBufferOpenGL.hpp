//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_INDEXBUFFEROPENGL_HPP
#define AZATHOTH_INDEXBUFFEROPENGL_HPP

#include "Renderer/IIndexBuffer.hpp"

namespace renderer {

    class IndexBufferOpenGL: public IIndexBuffer {
    public:
        IndexBufferOpenGL(uint32_t*, uint32_t);
        ~IndexBufferOpenGL();
    public:
        void bind() const override;
        void unBind() const override;
        uint32_t getCount() const override;
    private:
        uint32_t m_rendererId;
        uint32_t m_count;
    };

}

#endif //AZATHOTH_INDEXBUFFEROPENGL_HPP
