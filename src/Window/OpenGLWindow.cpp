//
// Created by egor on 2/7/22.
//
#include "Window/OpenGLWindow.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"

namespace window {

    void OpenglWindow::lazyInit() {
        if(not glfwInit()) {
            glfwSetErrorCallback(OpenGLTools::ErrorCallback);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        if(not m_window) {
            m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_data.width, m_data.height, m_data.title->c_str(), NULL, NULL),
                                                   [](auto window){glfwDestroyWindow(window);});
            glfwMakeContextCurrent(m_window.get());
            if(m_window == NULL) {
                logger::log_error("[OPENGL WINDOW] Window creation fails {} {} {}", m_data.width, m_data.height, m_data.title->c_str());
            }
            else {
                logger::log_info("[OPENGL WINDOW] Window lazy created successful {} {} {}", m_data.width, m_data.height, m_data.title->c_str());
            }
        }
    }

    void OpenglWindow::setHeight(int height)  {
        m_data.height = height;
    }

    void OpenglWindow::setWidth(int width) {
        m_data.width = width;
    }

    void OpenglWindow::setTitle(std::string const& title) {
        m_data.title = std::make_unique<std::string>(title.c_str());
    }

    std::shared_ptr<GLFWwindow> OpenglWindow::getWindow() {
        lazyInit();
        return m_window;
    }

    void OpenglWindow::draw() {
        glfwPollEvents();
        glfwSwapBuffers(m_window.get());
        glfwMakeContextCurrent(m_window.get());
    }

    OpenglWindow::~OpenglWindow() {
        glfwDestroyWindow(m_window.get());
    }

}
