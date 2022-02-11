//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_RENDERERAPI_HPP
#define AZATHOTH_RENDERERAPI_HPP

#include "Renderer/VertexArray.hpp"
#include <memory>
#include <glm/glm.hpp>

namespace renderer {

    class RendererApi {
    public:
        virtual void setClearColor(glm::vec4 const& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(std::shared_ptr<VertexArray> vertexArray) = 0;
    };

}

#endif //AZATHOTH_RENDERERAPI_HPP
