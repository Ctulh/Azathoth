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

namespace camera {

    CameraManipulatorOpenGL::CameraManipulatorOpenGL(std::shared_ptr<Camera>& camera):
                            Layer("CameraManipulator"),
                            m_camera(camera) {}

    void CameraManipulatorOpenGL::onEvent(Event& event) {
        events::EventDispatcher dispatcher(event);
        dispatcher.dispatch<events::MouseMovedEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onMouseMoved));
        dispatcher.dispatch<events::KeyPressedEvent>(BIND_EVENT_FN(CameraManipulatorOpenGL, onKeyPressed));
    }

    bool CameraManipulatorOpenGL::onKeyPressed(KeyPressedEvent& keyPressedEvent) {
        if(not input::Input::isKeyPressed(KEY_LEFT_ALT)) {
            if(input::Input::isKeyPressed(KEY_LEFT)) {
                m_camera->moveTo({-0.1f, 0.0f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_RIGHT)) {
                m_camera->moveTo({0.1f, 0.0f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_UP)) {
                m_camera->moveTo({0.0f, 0.1f, 0.0f});
                return true;
            } else if(input::Input::isKeyPressed(KEY_DOWN)) {
                m_camera->moveTo({0.0f, -0.1f, 0.0f});
                return true;
            }
        }
        return false;
    }

    bool CameraManipulatorOpenGL::onMouseMoved(MouseMovedEvent& mouseMovedEvent) {
        return false;
    }

}
