//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IGRAPHICAPIFACTORY_HPP
#define AZATHOTH_IGRAPHICAPIFACTORY_HPP

#include "OpenGL/Gui/ImGuiLayerGLFW.hpp" //TODO fix this include. WTF?
#include "Window/IWindow.hpp"
#include "Renderer/IShader.hpp"
#include "Layers/Layer.hpp"

namespace graphicApiFactory {

    class IGraphicApiFactory {
    public:
        [[nodiscard]] virtual std::unique_ptr<window::IWindow> createWindow() const = 0;
        [[nodiscard]] virtual gui::ImGuiLayerGLFW* createGui() const = 0;
        [[nodiscard]] virtual std::shared_ptr<renderer::IShader> createShader(std::string const& vert, std::string const& fragment) const = 0;
    public:
        virtual ~IGraphicApiFactory() = default;
    };

}

#endif //AZATHOTH_IGRAPHICAPIFACTORY_HPP
