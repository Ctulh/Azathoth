//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_IWINDOW_HPP
#define AZATHOTH_IWINDOW_HPP

#include <memory>
#include <string>

namespace window {

    template <typename WindowType>
    class IWindow {
    public:
        virtual std::shared_ptr<WindowType> getWindow() = 0;
        virtual void setHeight(int) = 0;
        virtual void setWidth(int) = 0;
        virtual void setTitle(std::string const&) = 0;
        virtual void draw() = 0;
    public:
        virtual ~IWindow() = default;
    };

}

#endif //AZATHOTH_IWINDOW_HPP
