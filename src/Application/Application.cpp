//
// Created by egor on 2/9/22.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"
#include "Tools/AzathothAssert.hpp"
#include "Renderer/BufferLayout.hpp"
#include "Renderer/VertexBufferOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Input/Input.h"
#include "Input/KeyCodes.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/IndexBufferOpenGL.hpp"
#include "Camera/CameraOpenGL.hpp"

namespace application {
using renderer::ShaderDataType;

    window::IWindow& Application::getWindow() {
        return *m_window;
    }

    Application* Application::getInstance() {
        AZATHOTH_ASSERT(m_instance, "null instance");
        return m_instance;
    }

    bool Application::onArrow(events::KeyEvent &event) {
        static float fov = 45.0f;
        if(not input::Input::isKeyPressed(KEY_LEFT_ALT)) {
            if(input::Input::isKeyPressed(KEY_LEFT)) {
                //*m_model = glm::translate(*m_model, glm::vec3(-0.1f, 0.0f, 0.0f));
                m_camera->moveTo({-0.1f, 0.0f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_RIGHT)) {
                m_camera->moveTo({0.1f, 0.0f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_UP)) {
                m_camera->moveTo({0.0f, 0.1f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_DOWN)) {
                m_camera->moveTo({0.0f, -0.1f, 0.0f});
                return true;
            }
        }
        else {
            if(input::Input::isKeyPressed(KEY_LEFT)) {
                *m_model = glm::rotate(*m_model, glm::radians(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));
                //m_camera->setFov();
                return true;
            } else if(input::Input::isKeyPressed(KEY_RIGHT)) {
                *m_model = glm::rotate(*m_model, glm::radians(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
                return true;
            } else if(input::Input::isKeyPressed(KEY_UP)) {
                fov -= 0.5f;
                m_camera->setFov(fov);
                //*m_model = glm::rotate(*m_model, glm::radians(1.0f), glm::vec3(0.1f, 0.0f, 0.0f));
                return true;
            } else if(input::Input::isKeyPressed(KEY_DOWN)) {
                fov += 0.5f;
                m_camera->setFov(fov);
                //*m_model = glm::rotate(*m_model, glm::radians(1.0f), glm::vec3(-0.1f, 0.0f, 0.0f));
                return true;
            }
        }
        return false;
    }

    bool Application::onWindowClose(events::WindowCloseEvent &event) {
        shutDown();
        return true;
    }

    void Application::pushLayer(layers::Layer* layer) {
        m_layerStack->pushLayer(layer);
    }

    void Application::pushOverlay(layers::Layer* overlay) {
        m_layerStack->pushOverlay(overlay);
    }

    Application::Application(IGraphicApiFactory const& factory):
            m_window(factory.createWindow()),
            m_camera(std::make_unique<camera::CameraOpenGL>()) {
        m_instance = this;
        m_layerStack = std::make_unique<layers::LayerStack>();
        m_layerStack->pushOverlay(factory.createGui());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
        m_model = std::make_shared<glm::mat4>(1.0f);
        m_vertexArray.reset(renderer::VertexArray::create());

        float verticies[ ] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, -1.0f,
                0.5f, 0.5f, -1.0f
        };

        m_vertexBuffer.reset(renderer::IVertexBuffer::create(verticies, sizeof(verticies)));
        //m_vertexBuffer->bind();
        uint32_t indices[12] = {0,1,2, 2, 3, 0, 1, 4, 2, 2, 4, 5};
        {
            renderer::BufferLayout layout = {
                    {renderer::ShaderDataType::Float3, "a_Position"}
            };

            m_vertexBuffer->setLayout(layout);
        }

        m_vertexArray->addVertexBuffer(m_vertexBuffer);

        m_indexBuffer.reset(IIndexBuffer::create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_vertexArray->setIndexBuffer(m_indexBuffer);

        m_shader = factory.createShader("shaderColored.vert", "shaderColored.frag");
    }

    void Application::onUpdate() {
        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onUpdate();
        }
    }

    void Application::onEvent(events::Event& event) {
        events::EventDispatcher dispatcher(event);
        dispatcher.dispatch<events::WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        dispatcher.dispatch<events::KeyPressedEvent>(BIND_EVENT_FN(onArrow));
        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onEvent(event);
            if (event.isHandled()) {
                break;
            }
        }
    }

    void Application::run() {
        if(m_isRunning.test_and_set(std::memory_order_acquire)) {
            logger::log_info("[RENDERER] Renderer in already running");
            return;
        }
        if(not m_window) {
            logger::log_error("[RENDERER] Window is NUll");
            return;
        }
        logger::log_info("[RENDERER] Renderer is running");
        glfwMakeContextCurrent((GLFWwindow*)(m_window->getNativeWindow().get()));
        auto gui = dynamic_cast<gui::ImGuiLayerGLFW*>((*m_layerStack)["GUI"]);

        glEnable(GL_DEPTH_TEST);
        while(m_isRunning.test(std::memory_order_acquire)) {
            renderer::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
            renderer::RenderCommand::clear();


            renderer::Renderer::beginScene(m_shader, m_camera->getPointer());
            m_shader->setUniformMatrix4f("Model", &(*m_model)[0][0]);
            m_shader->bind();
            renderer::Renderer::Submit(m_vertexArray);
            renderer::Renderer::endScene();


            gui->begin();
            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onImGuiRender();
            }
            gui->end();

            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onUpdate();
            }

            m_window->onUpdate();
        }
    }

    void Application::shutDown() {
        if(not m_isRunning.test()) {
            logger::log_info("[RENDERER] Renderer is already shutDowned");
            return;
        }

        while(m_isRunning.test(std::memory_order_acquire)) {
            m_isRunning.clear(std::memory_order_release);
        }
       // m_gui.reset();
       // m_window.reset();
        logger::log_info("[RENDERER] Renderer is stopped");
    }

    Application* Application::m_instance = nullptr;

}
