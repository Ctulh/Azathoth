//
// Created by egor on 2/11/22.
//
#include "Renderer/RendererAPI.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/RendererApiOpenGL.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace renderer {

    void RendererApiOpenGL::setClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RendererApiOpenGL::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererApiOpenGL::drawIndexed(std::shared_ptr<VertexArray> vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

    RendererApi* RenderCommand::s_RendererApi = new RendererApiOpenGL;
}
