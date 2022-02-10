//
// Created by egor on 2/7/22.
//
#include "Window/WindowGLFW.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Renderer/GraphicsContextOpenGL.hpp"

namespace window {

    void OpenglWindow::setEventCallback(eventCallbackFunction const& callback) {
        m_data.eventCallback = callback;
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

    std::shared_ptr<void> OpenglWindow::getNativeWindow() {
        return {static_cast<void*>(m_window.get()), [](auto window){}};
    }

    void OpenglWindow::draw() {
        m_context->swapBuffers();
    }

    int OpenglWindow::getHeight() {
        return m_data.height;
    }

    int OpenglWindow::getWidth() {
        return m_data.width;
    }

    OpenglWindow::~OpenglWindow() {
        logger::log_info("[OPENGL WINDOW] Destructed");
        glfwDestroyWindow(m_window.get());
    }

    OpenglWindow::OpenglWindow() {
        if(not glfwInit()) {
            glfwSetErrorCallback(OpenGLTools::ErrorCallback);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        if(not m_window) {
            m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_data.width, m_data.height, m_data.title->c_str(), NULL, NULL),
                                                   [](auto window){
                                                       logger::log_info("[OPENGL WINDOW POINTER] Destructed");});

            m_context = std::make_unique<renderer::GraphicsContextOpenGL>(m_window);
            m_context->init();

            glfwSetWindowUserPointer(m_window.get(), &m_data);

            if(m_window == NULL) {
                logger::log_error("[OPENGL WINDOW] Window creation fails {} {} {}", m_data.width, m_data.height, m_data.title->c_str());
            }
            else {
                logger::log_info("[OPENGL WINDOW] Window lazy created successful {} {} {}", m_data.width, m_data.height, m_data.title->c_str());
            }

            glfwSetWindowCloseCallback(m_window.get(), [](windowType* window) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                events::WindowCloseEvent event;
                data.eventCallback(event);
            });

            glfwSetKeyCallback(m_window.get(), [](windowType* window, int key, int scanCode, int action, int mods) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                switch(action) {
                    case GLFW_PRESS: {
                        events::KeyPressedEvent event(key, 0);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        events::KeyReleasedEvent event(key);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT: {
                        events::KeyPressedEvent event(key, 1);
                        data.eventCallback(event);
                        break;
                    }
                }
            });

            glfwSetMouseButtonCallback(m_window.get(), [](windowType* window, int button, int action, int mods) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                switch (action) {
                    case GLFW_PRESS: {
                        events::MouseButtonPressedEvent event(button);
                        data.eventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        events::MouseButtonReleasedEvent event(button);
                        data.eventCallback(event);
                        break;
                    }
                }
            });

            glfwSetScrollCallback(m_window.get(), [](windowType* window, double xOffset, double yOffset) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                events::MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
                data.eventCallback(event);
            });

            glfwSetCursorPosCallback(m_window.get(), [](windowType* window, double xPos, double yPos) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                events::MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
                data.eventCallback(event);
            });
        }
    }
}
