//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_RENDERER_HPP
#define AZATHOTH_RENDERER_HPP

#include "IRenderer.hpp"
//#include <Window/OpenGLWindow.hpp>
#include <atomic>

namespace renderer {

    class Renderer: public IRenderer {
    public:
        void run() override;
        void stop() override;
    private:
        std::atomic_flag m_isRunning = false;
       // std::shared_ptr<window::OpenglWindow> m_window;
    };

}

#endif //AZATHOTH_RENDERER_HPP
