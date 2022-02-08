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
        virtual void windowInit() = 0;
        virtual std::shared_ptr<WindowType> getWindow() = 0;
        virtual void setHeight(int) = 0;
        virtual void setWidth(int) = 0;
        virtual void setTitle(std::string const&) = 0;
    public:
        virtual ~IWindow() = default;
    protected:
        std::shared_ptr<WindowType> m_window;
        std::shared_ptr<std::string> m_title = std::make_shared<std::string>("Title");
        int m_height = 480;
        int m_width = 640;
    };

}

#endif //AZATHOTH_IWINDOW_HPP
