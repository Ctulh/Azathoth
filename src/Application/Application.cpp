//
// Created by egor on 2/9/22.
//

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace application {

    window::IWindow& Application::getWindow() {
        return *m_window;
    }

    Application* Application::getInstance() {
        AZATHOTH_ASSERT(m_instance, "null instance");
        return m_instance;
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
            m_window(factory.createWindow()) {
        m_instance = this;
        m_layerStack = std::make_unique<layers::LayerStack>();
        m_layerStack->pushOverlay(factory.createGui());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER ,m_vertexBuffer);

        float verticies[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

        unsigned int indicies[] = {0,1,2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

        std::string vertexSource = R"(
                #version 330 core

                layout(location = 0) in vec3 a_position;
                out vec3 v_Position;

                void main() {
                    v_Position = a_position;
                    gl_Position = vec4(a_position, 1.0);
                }
        )";
        std::string fragmentSource = R"(
                #version 330 core

                layout(location = 0) out vec4 color;
                in vec3 v_Position;

                void main() {
                   color = vec4(v_Position * 0.5 + 0.5, 1.0);
                }
        )";

        m_shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }

    void Application::onUpdate() {
        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onUpdate();
        }
    }

    void Application::onEvent(events::Event& event) {

        events::EventDispatcher dispatcher(event);
        dispatcher.dispatch<events::WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
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
        while(m_isRunning.test(std::memory_order_acquire)) {
            glfwPollEvents();

            m_shader->bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            gui->begin();
            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onImGuiRender();
            }
            gui->end();

            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onUpdate();
            }

            m_window->draw();
            glClearColor(0.1f, 0.1f, 0.1f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);
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
