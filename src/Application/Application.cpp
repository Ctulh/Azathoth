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
        layer->onAttach();
    }

    void Application::pushOverlay(layers::Layer* layer) {
        m_layerStack->pushOverlay(layer);
        layer->onAttach();
    }

    Application::Application(IGraphicApiFactory const& factory):
            m_window(factory.createWindow()) {
        m_instance = this;
        m_gui = new gui::ImGuiOpenGL;
        m_window->setWidth(1600);
        m_window->setHeight(900);
        m_window->setTitle("Test\n");

        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
        m_layerStack = std::make_shared<layers::LayerStack>();
        pushOverlay(m_gui);
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
        //m_gui->setWindow(m_window->getNativeWindow());
        //m_window2->getWindow();
        logger::log_info("[RENDERER] Renderer is running");
        glfwMakeContextCurrent((GLFWwindow*)(m_window.get()->getNativeWindow().get()));
        while(m_isRunning.test(std::memory_order_acquire)) {
          //  m_gui->draw();
            glfwPollEvents();


            m_gui->begin();
            for (layers::Layer* layer: (*m_layerStack.get())) {
                layer->onImGuiRender();
            }
            m_gui->end();

            for (layers::Layer* layer: (*m_layerStack.get())) {
                layer->onUpdate();
            }

            m_window->draw();
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
