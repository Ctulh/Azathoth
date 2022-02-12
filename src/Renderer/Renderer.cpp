//
// Created by egor on 2/11/22.
//
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"

namespace renderer {

    void Renderer::beginScene(std::shared_ptr<IShader>& shader, float const* const cameraMatrix) {
        shader->setUniformMatrix4f("CameraMatrix", cameraMatrix);
    }

    void Renderer::endScene() {

    }

    void Renderer::Submit(std::shared_ptr<VertexArray> vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}
