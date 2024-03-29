//
// Created by egor on 2/9/22.
//

#include "OpenGL/Input/WindowInpuGLFW.hpp"
#include "GLFW/glfw3.h"
#include "Application/Application.hpp"

namespace input {

    bool WindowInpuGLFW::isKeyPressedImpl(int keyCode) {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowInpuGLFW::isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    float WindowInpuGLFW::getMouseXImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return static_cast<float>(mouseX);
    }

    float WindowInpuGLFW::getMouseYImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return static_cast<float>(mouseY);
    }

    std::pair<float, float> WindowInpuGLFW::getMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return {static_cast<float>(mouseX), static_cast<float>(mouseY)};
    }

    std::shared_ptr<Input> Input::m_instance = nullptr;
}

