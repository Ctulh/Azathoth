//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include <memory>
#include <atomic>

#include "GraphicApiFactory/IGraphicApiFactory.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/IIndexBuffer.hpp"
#include "Layers/LayerStack.hpp"
#include "Window/IWindow.hpp"
#include "IApplication.hpp"


namespace application {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    using graphicApiFactory::IGraphicApiFactory;
    using renderer::IVertexBuffer;
    using renderer::IIndexBuffer;
    using layers::LayerStack;
    using window::IWindow;
    using layers::Layer;
    using events::Event;
    using renderer::IShader;


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
        std::unique_ptr<IVertexBuffer> m_vertexBuffer;
        std::unique_ptr<IIndexBuffer> m_indexBuffer;
        std::unique_ptr<IWindow> m_window;
        std::unique_ptr<LayerStack> m_layerStack;
        std::unique_ptr<IShader> m_shader;
        std::atomic_flag m_isRunning = false;
        unsigned int m_vertexArray;
    private:
        void onUpdate();
        bool onWindowClose(events::WindowCloseEvent& event);
        static Application* m_instance;
    };

}

#endif //AZATHOTH_APPLICATION_HPP
