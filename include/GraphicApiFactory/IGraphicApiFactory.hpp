//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IGRAPHICAPIFACTORY_HPP
#define AZATHOTH_IGRAPHICAPIFACTORY_HPP
#include "Window/IWindow.hpp"
#include "Gui/IGui.hpp"

namespace graphicApiFactory {

    class IGraphicApiFactory {
    public:
        virtual std::shared_ptr<window::IWindow> createWindow() const = 0;
        virtual std::shared_ptr<gui::IGui> createGui() const = 0;
    public:
        virtual ~IGraphicApiFactory() = default;
    };

}

#endif //AZATHOTH_IGRAPHICAPIFACTORY_HPP
