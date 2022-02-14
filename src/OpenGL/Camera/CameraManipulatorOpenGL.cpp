//
// Created by egor on 2/13/22.
//
#include "Camera/CameraManipulatorOpenGL.hpp"
#include "Events/Event.hpp"
#include "Events/MouseEvent.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/Input.h"
#include "Tools/FunctionBinder.hpp"
#include "Logger/Logger.hpp"
#include <glm/gtx/quaternion.hpp>

namespace camera {

    CameraManipulatorOpenGL::CameraManipulatorOpenGL(std::shared_ptr<Camera>& camera):
                            Layer("CameraManipulator"),
                            m_camera(camera) {
        auto pos = input::Input::getMousePosition();
        prevX = pos.first;
        prevY = pos.second;
    }

    void CameraManipulatorOpenGL::onUpdate(float) {
        if(input::Input::isKeyPressed(KEY_LEFT_SHIFT)) {
            m_camera->moveTo({0.0f, -0.1f, 0.0f});
        }
    }

    void CameraManipulatorOpenGL::onEvent(Event& event) {
        events::EventDispatcher dispatcher(event);
        dispatcher.dispatch<events::MouseMovedEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onMouseMoved));
        dispatcher.dispatch<events::KeyPressedEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onKeyPressed));
        dispatcher.dispatch<events::MouseScrolledEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onMouseScrolled));
        dispatcher.dispatch<events::MouseMovedEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onMouseMoved));
    }

    bool CameraManipulatorOpenGL::onKeyPressed(KeyPressedEvent& keyPressedEvent) {
        if(not input::Input::isKeyPressed(KEY_LEFT_ALT)) {
            if(keyPressedEvent.getKeyCode() == KEY_D) {
                m_camera->moveTo({0.1f, 0.0f, 0.0f});
                return true;
            } else if(keyPressedEvent.getKeyCode() == KEY_A) {
                m_camera->moveTo({-0.1f, 0.0f, 0.0f});
                return true;
            } else if(keyPressedEvent.getKeyCode() == KEY_W) {
                m_camera->moveTo({0.0f, 0.0f, -0.1f});
                return true;
            } else if(keyPressedEvent.getKeyCode() == KEY_S) {
                m_camera->moveTo({0.0f, 0.0f, 0.1});
                return true;
            } else if(keyPressedEvent.getKeyCode() == KEY_SPACE) {
                m_camera->moveTo({0.0f, 0.1f, 0.0f});
                return true;
            }
        }
        return false;
    }

    bool CameraManipulatorOpenGL::onMouseScrolled(MouseScrolledEvent& mouseScrolledEvent) {
        m_camera->changeFov(-(mouseScrolledEvent.getYOffset() * 1.5f));
        return true;
    }

    bool CameraManipulatorOpenGL::onMouseMoved(MouseMovedEvent& mouseMovedEvent) {
        auto [newX, newY] = mouseMovedEvent.getPos();
        float xOffset = newX - prevX;
        float yOffset = newY - prevY;

        prevX = newX;
        prevY = newY;

        m_camera->rotate(xOffset, -yOffset);

        return true;
    }

}
