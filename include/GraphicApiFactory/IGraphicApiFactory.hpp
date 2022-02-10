//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IGRAPHICAPIFACTORY_HPP
#define AZATHOTH_IGRAPHICAPIFACTORY_HPP
#include "Window/IWindow.hpp"
#include "Layers/Layer.hpp"
#include "Gui/ImGuiLayerGLFW.hpp"
#include "Input/Input.h"

namespace graphicApiFactory {

    class IGraphicApiFactory {
    public:
        [[nodiscard]] virtual std::unique_ptr<window::IWindow> createWindow() const = 0;
        [[nodiscard]] virtual gui::ImGuiLayerGLFW* createGui() const = 0;
    public:
        virtual ~IGraphicApiFactory() = default;
    };

}

#endif //AZATHOTH_IGRAPHICAPIFACTORY_HPP
