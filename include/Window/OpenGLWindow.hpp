//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_OPENGLWINDOW_HPP
#define AZATHOTH_OPENGLWINDOW_HPP

#include "IWindow.hpp"
#include "GLFW/glfw3.h"
#include "OpenGLTools.hpp"
#include "Logger/Logger.hpp"
#include "Events/Event.hpp"
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
        void draw() override;
        void setEventCallback(eventCallbackFunction const&) override;
    private:
        struct WindowData {
            WindowData(): title(std::make_unique<std::string>("test")), width(1600), height(900) {}
            std::unique_ptr<std::string> title;
            int width, height;

            eventCallbackFunction eventCallback;
        };

        WindowData m_data;
        std::shared_ptr<windowType> m_window;
    };

}

#endif //AZATHOTH_OPENGLWINDOW_HPP
