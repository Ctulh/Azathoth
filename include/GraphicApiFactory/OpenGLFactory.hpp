//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_OPENGLFACTORY_HPP
#define AZATHOTH_OPENGLFACTORY_HPP

#include "IGraphicApiFactory.hpp"
#include "Window/OpenGLWindow.hpp"
#include "Logger/Logger.hpp"
#include "Gui/ImGuiOpenGL.hpp"

namespace graphicApiFactory {

    using window::OpenglWindow;
    using window::IWindow;


    class OpenGLFactory: public IGraphicApiFactory {
    public:
        using windowInstantiationType = OpenglWindow::windowType;

        [[nodiscard]] std::shared_ptr<IWindow> createWindow() const override {
            logger::log_info("[OPENGL FACTORY] Created window");
            return std::make_shared<OpenglWindow>();
        }

        [[nodiscard]] std::shared_ptr<gui::IGui> createGui() const override {
            logger::log_info("[OPENGL FACTORY] Created GUI");
            return std::make_shared<gui::ImGuiOpenGL>();
        }
    };

}

#endif //AZATHOTH_OPENGLFACTORY_HPP
