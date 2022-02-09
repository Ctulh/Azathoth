//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_INPUT_H
#define AZATHOTH_INPUT_H

#include <utility>
#include <memory>
#include "Logger/Logger.hpp"

namespace input {

    class Input {
    public:
        static bool isMouseButtonPressed(int button) { return m_instance->isMouseButtonPressedImpl(button); }
        static std::pair<float, float> getMousePosition() { return m_instance->getMousePositionImpl(); }
        static bool isKeyPressed(int keyCode) { return m_instance->isKeyPressedImpl(keyCode); }
        static float getMouseX() { return m_instance->getMouseXImpl(); }
        static float getMouseY() { return m_instance->getMouseYImpl(); }
        static void setInstance(std::shared_ptr<Input> input) {
            m_instance = input;
            logger::log_info("[INPUT] Instance changed");
        }
    private:
        virtual std::pair<float, float> getMousePositionImpl() = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual bool isKeyPressedImpl(int keyCode) = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;
    protected:
        static std::shared_ptr<Input> m_instance;
    };

}

#endif //AZATHOTH_INPUT_H
