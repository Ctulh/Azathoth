//
// Created by egor on 2/14/22.
//
#include "Object/GameObjectOpenGL.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace object {

   GameObjectOpenGL::GameObjectOpenGL(std::shared_ptr<VertexArray> vertexArray):
                                      m_vertexArray(vertexArray),
                                      m_model(std::make_shared<glm::mat4>(1.0f)) {
            *m_model = glm::scale(*m_model, glm::vec3(0.5f,1.0f,1.0f));
            *m_model = glm::translate(*m_model, glm::vec3(3.0f,-1.3f, 0.0f));
   }

    void GameObjectOpenGL::onUpdate(float) {

    }

    void GameObjectOpenGL::move(glm::vec3 const& vec3) {
        *m_model = glm::translate(*m_model, vec3);
    }

    bool GameObjectOpenGL::checkCollision(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>) {

    }

    std::shared_ptr<renderer::VertexArray> GameObjectOpenGL::getVertexArray() {
       return m_vertexArray;
    }

    void GameObjectOpenGL::bind(std::shared_ptr<renderer::IShader> shader) {
        shader->setUniformMatrix4f("Model", &(*m_model)[0][0]);
   }

}
