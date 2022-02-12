//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include <memory>
#include <atomic>
#include <glm/glm.hpp>

#include "GraphicApiFactory/IGraphicApiFactory.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/IIndexBuffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "Layers/LayerStack.hpp"
#include "Window/IWindow.hpp"
#include "IApplication.hpp"
#include "Camera/Camera.hpp"


namespace application {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    using graphicApiFactory::IGraphicApiFactory;
    using renderer::IVertexBuffer;
    using renderer::IIndexBuffer;
    using renderer::VertexArray;
    using layers::LayerStack;
    using window::IWindow;
    using camera::Camera;
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
        std::shared_ptr<IVertexBuffer> m_vertexBuffer;
        std::shared_ptr<IIndexBuffer> m_indexBuffer;
        std::unique_ptr<IWindow> m_window;
        std::unique_ptr<LayerStack> m_layerStack;
        std::shared_ptr<IShader> m_shader;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::atomic_flag m_isRunning = false;
        std::unique_ptr<Camera> m_camera;
        std::shared_ptr<glm::mat4> m_model;
    private:
        void onUpdate();
        bool onArrow(events::KeyEvent& event);
        bool onWindowClose(events::WindowCloseEvent& event);
        static Application* m_instance;
    };

}

#endif //AZATHOTH_APPLICATION_HPP
