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

    bool PipeElements::isPipeFlown(float x) {
        for(int i=0; i< m_Objects.size(); i++) {
            if(i%2==0) {
                glm::vec4 border6 = (*m_Objects[i]->m_model) * m_borders[6];
                if (!m_Objects[i]->pipeFlown && x > border6.x) {
                    m_Objects[i]->pipeFlown = true;
                    m_Objects[i + 1]->pipeFlown = true;
                    return true;
                }
            }
        }
        return false;
    }

    void PipeElements::next() {
        m_texture = std::make_shared<Texture>("/home/egor/Downloads/pipe.png");
        m_texture->Bind(101);
    }

    void PipeElements::restart() {
        m_Objects.clear();
        for(int i=0;i<4;i++) {
            createPipeColumn(3.5f * i);
        }
    }

    bool PipeElements::checkColission(float x, float y, float r) {
       int number = 0;
        for(auto& el: m_Objects) {
            glm::vec4 border1 = (*el->m_model) * m_borders[1];
            glm::vec4 border6 = (*el->m_model) * m_borders[6];

            float squareX = x - r;
            float squareY = y + r;
            float squareX1 = x + r;
            float squareY1 = y - r;
            if(number % 2 == 1) {
                bool first = squareY <= border1.y - 0.6;
                bool second = squareY1 > border6.y - 0.6;
                bool third = squareX1 < border6.x + 0.3;
                bool fourth = squareX > border1.x - 0.3;

                if (!(!first || !second || !third || !fourth)) {
                    return true;
                }
            }
            else {
                bool first = squareY <= border1.y ;
                bool second = squareY1 > border6.y;
                bool third = squareX1 < border6.x ;
                bool fourth = squareX > border1.x;

                if (!(first || second || third || fourth)) {
                    return true;
                }
            }
            number++;
        }
        return false;
    }

    PipeElements::PipeElements() {
        m_borders.emplace_back(-0.5f,-3.0f,0.0f, 1.0f);
        m_borders.emplace_back(0.5f,-3.0f,0.0f, 1.0f);
        m_borders.emplace_back(-0.5,1.0f,0.0f, 1.0f);
        m_borders.emplace_back(0.5f,1.0f,0.0f, 1.0f);
        m_borders.emplace_back(-0.65,1.0f,0.0f, 1.0f);
        m_borders.emplace_back(0.65,1.0f,0.0f, 1.0f);
        m_borders.emplace_back(-0.65,1.25f,0.0f, 1.0f);
        m_borders.emplace_back(0.65,1.25f,0.0, 1.0f);
        for(int i=0;i<4;i++) {
            createPipeColumn(3.5f * i);
        }

        m_texture = std::make_shared<Texture>("/home/egor/Downloads/pipe.png");
        m_texture->Bind(101);
    }

    void PipeElements::createPipeColumn(float distanceFromBegin) {
        int heightIndex = rand()%4;
        {
            std::shared_ptr<object> pipeObject = std::make_shared<object>();
            pipeObject->m_model = std::make_shared<glm::mat4>(1.0f);
            pipeObject->m_mesh = std::make_shared<Mesh>("/home/egor/Desktop/pipe.obj");
            auto &model = *(pipeObject->m_model);
          //  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,.0f));
            model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
            model = glm::translate(model, glm::vec3(distanceFromBegin + 9,((4-heightIndex+1) * -0.5f) - 0.3, 0.0f));

            pipeObject->index = 4-heightIndex;
            pipeObject->pipeFlown = false;
            m_Objects.push_back(pipeObject);
        } {
            std::shared_ptr<object> pipeObject = std::make_shared<object>();
            pipeObject->m_model = std::make_shared<glm::mat4>(1.0f);
            pipeObject->m_mesh = std::make_shared<Mesh>("/home/egor/Desktop/pipe.obj");
            auto &model = *(pipeObject->m_model);
            model = glm::scale(model, glm::vec3(0.5f,1.0f,1.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));
          //  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f,0.0f,0.0f));
            model = glm::translate(model, glm::vec3(-(distanceFromBegin + 9),((heightIndex+1) * -0.5f) -0.3 ,0.0f));
            pipeObject->index =  heightIndex;
            pipeObject->pipeFlown = false;
            m_Objects.push_back(pipeObject);
        }
        logger::log_info("[INDEX] {}", heightIndex);
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
                        -0.5f,-3.0f,0.0f, 0.275f,0.0f,
                        0.5f,-3.0f,0.0f, 0.725f,0.0f,
                        -0.5,1.0f,0.0f, 0.275f,0.725f,
                        0.5f,1.0f,0.0f, 0.725f,0.725f,
                        -0.65,1.0f,0.0f, 0.255f,0.25f,
                        0.65,1.0f,0.0f, 0.745f,0.25f,
                        -0.65,1.25f,0.0f, 0.255f, 0.07f,
                        0.65,1.25f,0.0f, 0.745f, 0.07f
                };



        auto pipeVertexArray = std::make_shared<renderer::VertexArrayOpenGL>();
        auto pipeVertexBuffer = std::make_shared<renderer::VertexBufferOpenGL>(pipeVertices, sizeof(pipeVertices));
        {
            renderer::BufferLayout layout = {
                    {renderer::ShaderDataType::Float3, "a_Position"},
                    {renderer::ShaderDataType::Float2, "texCoord"}
            };

            pipeVertexBuffer->setLayout(layout);
        }


        pipeVertexArray->addVertexBuffer(pipeVertexBuffer);
        uint32_t pipeIndices[] = {0,1,2, 2, 3, 1, 4, 5, 6, 6 ,5, 7};
        auto pipeIndexBuffer = std::make_shared<renderer::IndexBufferOpenGL>(pipeIndices, sizeof(pipeIndices)/sizeof(uint32_t));
        pipeVertexArray->setIndexBuffer(pipeIndexBuffer);
        return std::make_shared<GameObjectOpenGL>(pipeVertexArray);
    }

    void PipeElements::bind(std::shared_ptr<renderer::IShader> shader) {
        static float color[] = {1.0f,1.0f,1.0f};
        for(auto& el: m_Objects) {
            shader->setUniformMatrix4f("Model", &(*el->m_model)[0][0]);
            //shader->setUniformVec3f("Color", color);
            shader->setUniform1i("u_Texture", 101);
            shader->bind();
            el->m_mesh->Draw();
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