//
// Created by egor on 2/14/22.
//

#include "Object/PipeElements.hpp"

#include "Object/GameObjectOpenGL.hpp"
#include "Renderer/VertexArrayOpenGL.hpp"
#include "Renderer/IndexBufferOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/VertexBufferOpenGL.hpp"

#include "Logger/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace object {

    PipeElements::PipeElements() {
        for(int i=0;i<5;i++) {
            createPipeColumn(3.5f * i);
        }
    }

    void PipeElements::createPipeColumn(float distanceFromBegin) {
        {
            std::shared_ptr<object> pipeObject = std::make_shared<object>();
            pipeObject->m_model = std::make_shared<glm::mat4>(1.0f);
            pipeObject->m_object = createPipe();
            auto &model = *(pipeObject->m_model);
            model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
            model = glm::translate(model, glm::vec3(distanceFromBegin + 9, -2.0f, 0.0f));
            m_Objects.push_back(pipeObject);
        } {
            std::shared_ptr<object> pipeObject = std::make_shared<object>();
            pipeObject->m_model = std::make_shared<glm::mat4>(1.0f);
            pipeObject->m_object = createPipe();
            auto &model = *(pipeObject->m_model);
            model = glm::scale(model, glm::vec3(0.5f,1.0f,1.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));
            model = glm::translate(model, glm::vec3(-(distanceFromBegin + 9),-2.0f,0.0f));
            m_Objects.push_back(pipeObject);
        }
    }

    void PipeElements::moveColumn(float) {
        bool isTopPipe = false;
        for(auto& el: m_Objects) {
            (*el->m_model) = glm::translate((*el->m_model), glm::vec3(isTopPipe ? 0.01: -0.01,0.0f,0.0f));
            isTopPipe = !isTopPipe;
        }
        if((*m_Objects[0]->m_model)[3].x <= -3.5) {
            logger::log_info("[MOVED]");
            moveToBegin();
        }
    }

    std::shared_ptr<GameObject> PipeElements::createPipe() {
        float pipeVertices[] =
                {
                        -0.5f,-1.0f,0.0f,
                        0.5f,-1.0f,0.0f,
                        -0.5,1.0f,0.0f,
                        0.5f,1.0f,0.0f,
                        0.65f, 1.0f, 0.0f,
                        0.65f, 1.25f, 0.0f,
                        -0.65f, 1.25f, 0.0f,
                        -0.65f, 1.0f, 0.0f
                };

        auto pipeVertexArray = std::make_shared<renderer::VertexArrayOpenGL>();
        auto pipeVertexBuffer = std::make_shared<renderer::VertexBufferOpenGL>(pipeVertices, sizeof(pipeVertices));
        {
            renderer::BufferLayout layout = {
                    {renderer::ShaderDataType::Float3, "a_Position"}
            };

            pipeVertexBuffer->setLayout(layout);
        }
        pipeVertexArray->addVertexBuffer(pipeVertexBuffer);
        uint32_t pipeIndices[12] = {0,1,2, 2, 3, 1, 4, 5, 7, 7, 5, 6};
        auto pipeIndexBuffer = std::make_shared<renderer::IndexBufferOpenGL>(pipeIndices, sizeof(pipeIndices)/sizeof(uint32_t));
        pipeVertexArray->setIndexBuffer(pipeIndexBuffer);
        return std::make_shared<GameObjectOpenGL>(pipeVertexArray);
    }

    void PipeElements::bind(std::shared_ptr<renderer::IShader> shader) {
        static float color[] = {0.2, 0.4, 0.0};
        for(auto& el: m_Objects) {
            shader->setUniformMatrix4f("Model", &(*el->m_model)[0][0]);
            shader->setUniformVec3f("Color", color);
            shader->bind();
            renderer::Renderer::Submit(el->m_object->getVertexArray());
        }
    }

    void PipeElements::moveToBegin() {
        (*m_Objects[0]->m_model)[3].x = 3.5;
        (*m_Objects[1]->m_model)[3].x = 3.5;

        std::rotate(m_Objects.begin(), m_Objects.begin() + 2, m_Objects.end());

    }

    void PipeElements::addObject(std::shared_ptr<GameObject>) {

    }

    void PipeElements::onUpdate(float fl) {
        moveColumn(fl);
    }



}