//
// Created by egor on 2/13/22.
//

#ifndef AZATHOTH_CAMERAMANIPULATOROPENGL_HPP
#define AZATHOTH_CAMERAMANIPULATOROPENGL_HPP

#include "Layers/Layer.hpp"
#include "Camera/Camera.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"
#include <memory>

namespace camera {

    using layers::Layer;
    using events::MouseMovedEvent;
    using events::KeyPressedEvent;
    using events::MouseScrolledEvent;
    using events::Event;

    class CameraManipulatorOpenGL : public Layer {
    public:
        CameraManipulatorOpenGL(std::shared_ptr<Camera>&);
    public:
        void onUpdate(float) override;
        void onEvent(Event&) override;
    private:
        bool onMouseMoved(MouseMovedEvent&);
        bool onKeyPressed(KeyPressedEvent&);
        bool onMouseScrolled(MouseScrolledEvent&);
        int getSign(int);
    private:
        std::shared_ptr<Camera> m_camera;
        float prevX, prevY;
    };

}

#endif //AZATHOTH_CAMERAMANIPULATOROPENGL_HPP
