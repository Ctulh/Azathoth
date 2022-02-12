//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_FACTORYGLFW_HPP
#define AZATHOTH_FACTORYGLFW_HPP

#include "GraphicApiFactory/IGraphicApiFactory.hpp"
#include "OpenGL/Window/WindowGLFW.hpp"
#include "OpenGL/Input/WindowInpuGLFW.hpp"
#include "Logger/Logger.hpp"
#include "Renderer/ShaderOpenGL.hpp"
#include "OpenGL/Gui/ImGuiLayerGLFW.hpp"

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

        std::shared_ptr<renderer::IShader> createShader(const std::string &vert, const std::string &fragment) const override {
            logger::log_info("[OPENGL FACTORY] Created Shader");
            return std::make_shared<renderer::ShaderOpenGL>(vert, fragment);
        }
    };

}

#endif //AZATHOTH_FACTORYGLFW_HPP
