//
// Created by egor on 2/10/22.
//

#ifndef AZATHOTH_IGRAPHICSCONTEXT_HPP
#define AZATHOTH_IGRAPHICSCONTEXT_HPP

#include <memory>

namespace renderer {

    class IGraphicsContext {
    public:
        virtual ~IGraphicsContext() = default;
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

}

#endif //AZATHOTH_IGRAPHICSCONTEXT_HPP
