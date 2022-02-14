//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_WINDOWINPUGLFW_HPP
#define AZATHOTH_WINDOWINPUGLFW_HPP

#include "Input/Input.h"

namespace input {

    class WindowInpuGLFW: public Input {
    protected:
        std::pair<float, float> getMousePositionImpl() override;
        bool isMouseButtonPressedImpl(int button) override;
        bool isKeyPressedImpl(int keyCode) override;
        float getMouseXImpl() override;
        float getMouseYImpl() override;
        void hideCursorImpl() override;
        void showCursorImpl() override;
    };

}

#endif //AZATHOTH_WINDOWINPUGLFW_HPP
