//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_RENDERER_HPP
#define AZATHOTH_RENDERER_HPP

#include <memory>

#include "Renderer.hpp"
#include "IShader.hpp"
#include "VertexArray.hpp"

namespace renderer {

    class Renderer {
    public:
        static void beginScene(std::shared_ptr<IShader>&, float const* const cameraMatrix);
        static void endScene();
        static void Submit(std::shared_ptr<VertexArray>);
    };

}

#endif //AZATHOTH_RENDERER_HPP
