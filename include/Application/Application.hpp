//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include "IApplication.hpp"
#include "Layers/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window/IWindow.hpp"
#include "GraphicApiFactory/IGraphicApiFactory.hpp"
#include "Input/Input.h"
#include "Gui/ImGuiLayerGLFW.hpp"
#include "Renderer/Shader.hpp"
#include <memory>
#include <atomic>

namespace application {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    using graphicApiFactory::IGraphicApiFactory;
    using layers::LayerStack;
    using window::IWindow;
    using layers::Layer;
    using events::Event;
    using input::Input;
    using renderer::Shader;


    class Application: public IApplication {
    public:
        Application(IGraphicApiFactory const&);
    public:
        static Application* getInstance();
        void run() override;
        void shutDown() override;
        void onEvent(Event&) override;
        void pushLayer(Layer*) override;
        void pushOverlay(Layer*) override;
        IWindow& getWindow();
    private:
        std::unique_ptr<IWindow> m_window;
        std::unique_ptr<LayerStack> m_layerStack;
        std::unique_ptr<Shader> m_shader;
        std::atomic_flag m_isRunning = false;
        unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
    private:
        void onUpdate();
        bool onWindowClose(events::WindowCloseEvent& event);
        static Application* m_instance;
    };

}

#endif //AZATHOTH_APPLICATION_HPP
