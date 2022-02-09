//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_RENDERER_HPP
#define AZATHOTH_RENDERER_HPP

#include "IRenderer.hpp"
#include "Window/IWindow.hpp"
#include "Gui/IGui.hpp"
#include <memory>
#include <atomic>

namespace renderer {

    using window::IWindow;
    using gui::IGui;

    template <typename GraphicApiFactory>
    class Renderer: public IRenderer {
    public:
        Renderer();
    public:
        void run() override;
        void shutDown() override;
        void onEvent(events::Event&) override;
    private:
        std::atomic_flag m_isRunning = false;
        std::shared_ptr<IWindow<typename GraphicApiFactory::windowInstantiationType>> m_window;
        std::shared_ptr<IWindow<typename GraphicApiFactory::windowInstantiationType>> m_window2;
        std::shared_ptr<IGui<typename GraphicApiFactory::windowInstantiationType>> m_gui;
    };

    template <typename GraphicApiFactory>
    Renderer<GraphicApiFactory>::Renderer():
                        m_window(GraphicApiFactory().createWindow()),
                        m_gui(GraphicApiFactory().createGui()),
                        m_window2(GraphicApiFactory().createWindow()){
        m_window->setWidth(1600);
        m_window->setHeight(900);
        m_window->setTitle("Test\n");

        m_window->setEventCallback(std::bind(&Renderer::onEvent, this, std::placeholders::_1));

        m_window2.get()->setWidth(600);
        m_window2.get()->setHeight(900);
        m_window2.get()->setTitle("Test2");
    }

    template <typename GraphicApiFactory>
    void Renderer<GraphicApiFactory>::onEvent(events::Event& event) {
        logger::log_info(event.toString());
        if(event.isInCategory(events::EventCategory::EventCategoryApplication)) {
            if (event.getEventType() == events::EventType::WindowClose) {
                shutDown();
            }
        }
    }

    template <typename GraphicApiFactory>
    void Renderer<GraphicApiFactory>::run() {
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
        }
    }

    template<typename GraphicApiFactory>
    void Renderer<GraphicApiFactory>::shutDown() {
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

#endif //AZATHOTH_RENDERER_HPP
