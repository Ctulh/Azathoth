//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_RENDERER_HPP
#define AZATHOTH_RENDERER_HPP

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <memory>

namespace renderer {

    class Renderer {
    public:
        static void beginScene();
        static void endScene();
        static void Submit(std::shared_ptr<VertexArray>);
    };

}

#endif //AZATHOTH_RENDERER_HPP
