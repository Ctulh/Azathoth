//
// Created by egor on 2/11/22.
//
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"

namespace renderer {

    void Renderer::beginScene(std::shared_ptr<IShader>& shader, float const* const view, float const* const projection) {
        shader->setUniformMatrix4f("View", view);
        shader->setUniformMatrix4f("Projection", projection);
    }

    void Renderer::beginScene(std::shared_ptr<IShader>& shader, float const* const projectionView) {
        shader->setUniformMatrix4f("ProjectionView", projectionView);
    }

    void Renderer::endScene() {

    }

    void Renderer::Submit(std::shared_ptr<VertexArray> vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}
