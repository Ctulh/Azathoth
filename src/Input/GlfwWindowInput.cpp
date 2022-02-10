//
// Created by egor on 2/9/22.
//

#include "Input/GlfwWindowInput.hpp"
#include "GLFW/glfw3.h"
#include "Application/Application.hpp"

namespace input {

    bool GlfwWindowInput::isKeyPressedImpl(int keyCode) {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool GlfwWindowInput::isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    float GlfwWindowInput::getMouseXImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return static_cast<float>(mouseX);
    }

    float GlfwWindowInput::getMouseYImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return static_cast<float>(mouseY);
    }

    std::pair<float, float> GlfwWindowInput::getMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(application::Application::getInstance()->getWindow().getNativeWindow().get());
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        return {static_cast<float>(mouseX), static_cast<float>(mouseY)};
    }

    std::shared_ptr<Input> Input::m_instance = nullptr;
}

