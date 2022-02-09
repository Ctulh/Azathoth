//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_GLFWWINDOWINPUT_HPP
#define AZATHOTH_GLFWWINDOWINPUT_HPP

#include "Input.h"

namespace input {

    class GlfwWindowInput: public Input {
    protected:
        std::pair<float, float> getMousePositionImpl() override;
        bool isMouseButtonPressedImpl(int button) override;
        bool isKeyPressedImpl(int keyCode) override;
        float getMouseXImpl() override;
        float getMouseYImpl() override;
    };

}

#endif //AZATHOTH_GLFWWINDOWINPUT_HPP
