//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_IWINDOW_HPP
#define AZATHOTH_IWINDOW_HPP

#include <memory>
#include <string>
#include "Events/Event.hpp"

namespace window {

    class IWindow {
    public:
        using eventCallbackFunction = std::function<void(events::Event&)>;
    public:
        virtual std::shared_ptr<void> getWindow() = 0;
        virtual void setHeight(int) = 0;
        virtual void setWidth(int) = 0;
        virtual void setTitle(std::string const&) = 0;
        virtual void draw() = 0;
        virtual void setEventCallback(eventCallbackFunction const&) = 0;
    public:
        virtual ~IWindow() = default;
    };

}

#endif //AZATHOTH_IWINDOW_HPP
