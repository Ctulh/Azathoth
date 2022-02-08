//
// Created by egor on 2/7/22.
//
#include "Window/OpenGLWindow.hpp"
#include "Logger/Logger.hpp"

namespace window {

    void OpenglWindow::init() {
        if(not glfwInit()) {
            glfwSetErrorCallback(OpenGLTools::ErrorCallback);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        if(not m_window) {
            m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_width, m_height, m_title->c_str(), NULL, NULL),
                                                   [](auto window){glfwDestroyWindow(window);});
            glfwMakeContextCurrent(m_window.get());
            if(m_window == NULL) {
                logger::log_error("[OPENGL WINDOW] Window creation fails");
            }
            else {
                logger::log_info("[OPENGL WINDOW] Window created successful");
            }
        } else {
            logger::log_warning("[OPENGL WINDOW] Re-initialization attempt");
        }
    }

    void OpenglWindow::setHeight(int height)  {
        m_height = height;
    }

    void OpenglWindow::setWidth(int width) {
        m_width = width;
    }

    void OpenglWindow::setTitle(std::string const& title) {
        m_title = std::make_shared<std::string>(title.c_str());
    }

    std::shared_ptr<GLFWwindow> OpenglWindow::getWindow() {
        return m_window;
    }

}
