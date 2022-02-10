//
// Created by egor on 2/9/22.
//

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "GLFW/glfw3.h"

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
        while(m_isRunning.test(std::memory_order_acquire)) {
            glfwPollEvents();


            dynamic_cast<gui::ImGuiLayerGLFW*>((*m_layerStack)["GUI"])->begin();
            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onImGuiRender();
            }
            dynamic_cast<gui::ImGuiLayerGLFW*>((*m_layerStack)["GUI"])->end();

            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onUpdate();
            }

            m_window->draw();
            glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
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
