//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_RENDERER_HPP
#define AZATHOTH_RENDERER_HPP

#include "IRenderer.hpp"

namespace renderer {

    class Renderer: public IRenderer {
    public:
        void run() const override;
        void stop() const override;
    };

}

#endif //AZATHOTH_RENDERER_HPP
