//
// Created by egor on 2/7/22.
//
#include "Renderer/Renderer.hpp"
#include "Logger/Logger.hpp"
//#include "Window/OpenGLWindow.hpp"

namespace renderer {

    void Renderer::run()  {
        if(m_isRunning.test_and_set(std::memory_order_acquire)) {
            logger::log_info("[RENDERER] Renderer in already running");
            return;
        }

        logger::log_info("[RENDERER] Renderer is running");
        while(m_isRunning.test(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void Renderer::stop() {
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