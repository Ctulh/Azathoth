//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_OPENGLWINDOW_HPP
#define AZATHOTH_OPENGLWINDOW_HPP

#include "IWindow.hpp"
#include "GLFW/glfw3.h"
#include "ErrorCallback.hpp"
#include "Logger/Logger.hpp"
#include <iostream>

namespace window {

    class OpenglWindow: public IWindow<GLFWwindow> {
    public:
        using windowType = GLFWwindow;

        OpenglWindow() {}

        void windowInit() override {
            glfwSetErrorCallback(OpenGLTools::ErrorCallback);
            if(not glfwInit()) {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            }

            m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_width, m_height, m_title->c_str(), NULL, NULL),
                                                   [](auto window){glfwDestroyWindow(window);});
            if(m_window == NULL) {
                logger::log_error("[OPENGL WINDOW] Window creation fails");
            }
        }

        void setHeight(int height) override {
            m_height = height;
        }

        void setWidth(int width) override {
            m_width = width;
        }

        void setTitle(std::string const& title) override {
            m_title = std::make_shared<std::string>(title.c_str());
        }

        std::shared_ptr<GLFWwindow> getWindow() override {
            return m_window;
        }
    };

}

#endif //AZATHOTH_OPENGLWINDOW_HPP
