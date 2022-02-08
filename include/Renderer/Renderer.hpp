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
        void stop() override;
    private:
        std::atomic_flag m_isRunning = false;
        std::shared_ptr<IWindow<typename GraphicApiFactory::windowInstantiationType>> m_window;
        std::shared_ptr<IGui<typename GraphicApiFactory::windowInstantiationType>> m_gui;
    };

    template <typename GraphicApiFactory>
    Renderer<GraphicApiFactory>::Renderer():
                        m_window(GraphicApiFactory().createWindow()),
                        m_gui(GraphicApiFactory().createGui()) {
        m_window.get()->setWidth(1600);
        m_window.get()->setHeight(900);
        m_window.get()->setTitle("Test");
    }

    template <typename GraphicApiFactory>
    void Renderer<GraphicApiFactory>::run() {
        if(m_isRunning.test_and_set(std::memory_order_acquire)) {
            logger::log_info("[RENDERER] Renderer in already running");
            return;
        }

        logger::log_info("[RENDERER] Renderer is running");
        m_window->windowInit();
        m_gui->init(m_window->getWindow());

        while(m_isRunning.test(std::memory_order_acquire)) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            m_gui->draw();
        }
    }

    template<typename GraphicApiFactory>
    void Renderer<GraphicApiFactory>::stop() {
        if(not m_isRunning.test()) {
            logger::log_info("[RENDERER] Renderer is already stopped");
            return;
        }

        while(m_isRunning.test(std::memory_order_acquire)) {
            m_isRunning.clear(std::memory_order_release);
        }
        logger::log_info("[RENDERER] Renderer is stopped");
    }
}

#endif //AZATHOTH_RENDERER_HPP
