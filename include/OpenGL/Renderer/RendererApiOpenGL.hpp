//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_RENDERERAPIOPENGL_HPP
#define AZATHOTH_RENDERERAPIOPENGL_HPP

#include "Renderer/RendererAPI.hpp"

namespace renderer {

    class RendererApiOpenGL: public RendererApi {
    public:
        void setClearColor(glm::vec4 const& color) override;
        void clear() override;
        void drawIndexed(std::shared_ptr<VertexArray> vertexArray) override;
    };

}

#endif //AZATHOTH_RENDERERAPIOPENGL_HPP
