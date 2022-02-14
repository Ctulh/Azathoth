//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_WINDOWGLFW_HPP
#define AZATHOTH_WINDOWGLFW_HPP

#include "Window/IWindow.hpp"
#include "GLFW/glfw3.h"
#include "OpenGL/Tools/OpenGLTools.hpp"
#include "Logger/Logger.hpp"
#include "Events/Event.hpp"
#include "Renderer/IGraphicsContext.hpp"
#include <iostream>


namespace window {

    class OpenglWindow: public IWindow {
    public:
        using windowType = GLFWwindow;

    public:
        OpenglWindow();
        ~OpenglWindow();
    public:
        void setHeight(int height) override;
        void setWidth(int width) override;
        int getHeight() override;
        int getWidth() override;
        void setTitle(std::string const& title) override;
        std::shared_ptr<void> getNativeWindow() override;

        void onUpdate() const override;

        void setEventCallback(eventCallbackFunction const&) override;
    private:
        struct WindowData {
            WindowData(): title(std::make_unique<std::string>("test")), width(1920), height(1080) {}
            std::unique_ptr<std::string> title;
            int width, height;

            eventCallbackFunction eventCallback;
        };

        WindowData m_data;
        std::unique_ptr<renderer::IGraphicsContext> m_context;
        std::shared_ptr<windowType> m_window;
    };

}

#endif //AZATHOTH_WINDOWGLFW_HPP
