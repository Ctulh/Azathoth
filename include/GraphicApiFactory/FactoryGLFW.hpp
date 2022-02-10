//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_FACTORYGLFW_HPP
#define AZATHOTH_FACTORYGLFW_HPP

#include "IGraphicApiFactory.hpp"
#include "Window/WindowGLFW.hpp"
#include "Input/WindowInpuGLFW.hpp"
#include "Logger/Logger.hpp"
#include "Gui/ImGuiLayerGLFW.hpp"

namespace graphicApiFactory {

    using window::OpenglWindow;
    using window::IWindow;


    class FactoryGLFW: public IGraphicApiFactory {
    public:
        using windowInstantiationType = OpenglWindow::windowType;

        [[nodiscard]] std::unique_ptr<IWindow> createWindow() const override {
            logger::log_info("[OPENGL FACTORY] Created Window");
            //__INPUT INITIALIZATION
            auto input = std::make_shared<input::WindowInpuGLFW>();
            input::Input::setInstance(input);
            //_____________
            return std::make_unique<OpenglWindow>();
        }

        [[nodiscard]] gui::ImGuiLayerGLFW* createGui() const override {
            logger::log_info("[OPENGL FACTORY] Created GUI");
            return new gui::ImGuiLayerGLFW;
        }
    };

}

#endif //AZATHOTH_FACTORYGLFW_HPP
