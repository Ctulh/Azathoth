//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include "IApplication.hpp"
#include "Window/IWindow.hpp"
#include "Gui/IGui.hpp"
#include "Layers/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include <memory>
#include <atomic>

namespace application {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    using window::IWindow;
    using gui::IGui;

    template <typename GraphicApiFactory>
    class Application: public IApplication {
    public:
        Application();
    public:
        void run() override;
        void shutDown() override;
        void onEvent(events::Event&) override;
        void pushLayer(layers::Layer*) override;
        void pushOverlay(layers::Layer*) override;
    private:
        std::shared_ptr<IWindow<typename GraphicApiFactory::windowInstantiationType>> m_window;
        std::shared_ptr<IGui<typename GraphicApiFactory::windowInstantiationType>> m_gui;
        std::shared_ptr<layers::LayerStack> m_layerStack;
        std::atomic_flag m_isRunning = false;
    private:
        bool onWindowClose(events::WindowCloseEvent& event);
    };

    template <typename GraphicApiFactory>
    bool Application<GraphicApiFactory>::onWindowClose(events::WindowCloseEvent &event) {
        shutDown();
        return true;
    }

    template <typename GraphicApiFactory>
    void Application<GraphicApiFactory>::pushLayer(layers::Layer* layer) {
        m_layerStack->pushLayer(layer);
    }

    template <typename GraphicApiFactory>
    void Application<GraphicApiFactory>::pushOverlay(layers::Layer* layer) {
        m_layerStack->pushOverlay(layer);
    }

    template <typename GraphicApiFactory>
    Application<GraphicApiFactory>::Application():
                        m_window(GraphicApiFactory().createWindow()),
                        m_gui(GraphicApiFactory().createGui()){
        m_window->setWidth(1600);
        m_window->setHeight(900);
        m_window->setTitle("Test\n");

        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
        m_layerStack = std::make_shared<layers::LayerStack>();
    }

    template <typename GraphicApiFactory>
    void Application<GraphicApiFactory>::onEvent(events::Event& event) {

        events::EventDispatcher dispatcher(event);
       dispatcher.dispatch<events::WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onEvent(event);
            if (event.isHandled()) {
                break;
            }
        }
    }

    template <typename GraphicApiFactory>
    void Application<GraphicApiFactory>::run() {
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

    template<typename GraphicApiFactory>
    void Application<GraphicApiFactory>::shutDown() {
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

#endif //AZATHOTH_APPLICATION_HPP
