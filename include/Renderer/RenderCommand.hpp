//
// Created by egor on 2/11/22.
//

#ifndef AZATHOTH_RENDERCOMMAND_HPP
#define AZATHOTH_RENDERCOMMAND_HPP

#include "RendererAPI.hpp"

namespace renderer {

    class RenderCommand {
    public:
        inline static void drawIndexed(std::shared_ptr<VertexArray> vertexArray) {
            s_RendererApi->drawIndexed(vertexArray);
        }

        inline static void setClearColor(glm::vec4 const& color) {
            s_RendererApi->setClearColor(color);
        }

        inline static void clear() {
            s_RendererApi->clear();
        }

    private:
        static RendererApi* s_RendererApi;
    };

}

#endif //AZATHOTH_RENDERCOMMAND_HPP
