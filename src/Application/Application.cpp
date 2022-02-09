//
// Created by egor on 2/9/22.
//

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"

namespace application {

    bool Application::onWindowClose(events::WindowCloseEvent &event) {
        shutDown();
        return true;
    }

    void Application::pushLayer(layers::Layer* layer) {
        m_layerStack->pushLayer(layer);
    }

    void Application::pushOverlay(layers::Layer* layer) {
        m_layerStack->pushOverlay(layer);
    }

    Application::Application(IGraphicApiFactory const& factory):
            m_window(factory.createWindow()),
            m_gui(factory.createGui()){
        m_window->setWidth(1600);
        m_window->setHeight(900);
        m_window->setTitle("Test\n");

        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
        m_layerStack = std::make_shared<layers::LayerStack>();
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
        m_gui->setWindow(m_window->getWindow());
        //m_window2->getWindow();
        logger::log_info("[RENDERER] Renderer is running");

        while(m_isRunning.test(std::memory_order_acquire)) {
            m_gui->draw();
            m_window->draw();

            for (layers::Layer* layer: (*m_layerStack.get())) {
                layer->onUpdate();
            }
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
        m_gui.reset();
        m_window.reset();
        logger::log_info("[RENDERER] Renderer is stopped");
    }

}
