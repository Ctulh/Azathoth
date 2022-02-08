//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_OPENGLWINDOW_HPP
#define AZATHOTH_OPENGLWINDOW_HPP

#include "IWindow.hpp"
#include "GLFW/glfw3.h"
#include "OpenGLTools.hpp"
#include "Logger/Logger.hpp"
#include <iostream>

namespace window {

    class OpenglWindow: public IWindow<GLFWwindow> {
    public:
        using windowType = GLFWwindow;
    public:
        OpenglWindow() = default;
    public:
        void windowInit() override;
        void setHeight(int height) override;
        void setWidth(int width) override;
        void setTitle(std::string const& title) override;
        std::shared_ptr<GLFWwindow> getWindow() override;
    };

}

#endif //AZATHOTH_OPENGLWINDOW_HPP
