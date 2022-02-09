//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_KEYEVENT_HPP
#define AZATHOTH_KEYEVENT_HPP

#include <sstream>
#include "Event.hpp"

namespace events {

    class KeyEvent: public Event {
    public:
        inline int getKeyCode() const {
            return m_keyCode;
        }

        EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::EventCategoryKeyboard) |
                             static_cast<int>(EventCategory::EventCategoryInput));
    protected:
        KeyEvent(int keyCode): m_keyCode(keyCode) {}
        int m_keyCode;
    };

    class KeyPressedEvent: public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount): KeyEvent(keyCode), m_repeatCount(repeatCount) {}
        inline int getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(:KeyPressed)
    private:
        int m_repeatCount;
    };

    class KeyReleasedEvent: public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode): KeyEvent(keyCode) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent :" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(:KeyReleased)
    };

}

#endif //AZATHOTH_KEYEVENT_HPP
