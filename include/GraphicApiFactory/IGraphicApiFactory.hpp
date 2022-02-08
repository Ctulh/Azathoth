//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IGRAPHICAPIFACTORY_HPP
#define AZATHOTH_IGRAPHICAPIFACTORY_HPP
#include "Window/IWindow.hpp"

namespace graphicApiFactory {

    template<typename WindowType>
    class IGraphicApiFactory {
    public:
        virtual std::shared_ptr<window::IWindow<WindowType>> createWindow() const = 0;
    public:
        virtual ~IGraphicApiFactory() = default;
    };

}

#endif //AZATHOTH_IGRAPHICAPIFACTORY_HPP
