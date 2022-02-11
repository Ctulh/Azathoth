//
// Created by egor on 2/11/22.
//
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"

namespace renderer {

    void Renderer::beginScene() {

    }

    void Renderer::endScene() {

    }

    void Renderer::Submit(std::shared_ptr<VertexArray> vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}
