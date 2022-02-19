//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_APPLICATION_HPP
#define AZATHOTH_APPLICATION_HPP

#include <memory>
#include <atomic>
#include <glm/glm.hpp>
#include <map>


#include "GraphicApiFactory/IGraphicApiFactory.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Renderer/IVertexBuffer.hpp"
#include "Object/ObjectElements.hpp"
#include "Renderer/IIndexBuffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "Layers/LayerStack.hpp"
#include "Window/IWindow.hpp"
#include "Object/Object.hpp"
#include "IApplication.hpp"
#include "Camera/Camera.hpp"
#include "Texture/Texture.h"


namespace application {

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
        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };
    private:
        std::shared_ptr<IVertexBuffer> m_vertexBuffer;
        std::shared_ptr<IIndexBuffer> m_indexBuffer;
        std::unique_ptr<IWindow> m_window;
        std::unique_ptr<LayerStack> m_layerStack;
        std::shared_ptr<IShader> m_shader;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<VertexArray> m_bgVertexArray;
        std::shared_ptr<glm::mat4> m_bgModel;
        std::atomic_flag m_isRunning = false;
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<glm::mat4> m_model;
        std::shared_ptr<glm::mat4> m_drawModel;

        std::shared_ptr<Texture> m_flappyTexture;
        std::shared_ptr<object::ObjectElements> m_pipes;
        std::shared_ptr<Texture> m_bgTexture;
        std::shared_ptr<glm::mat4> m_rotationModel;
        float totalTranslation = 0;
        float m_lastTimeStep = 0; //todo class
        float acceleration = 0;
        float inertia = 0;
        float height = 0;
        bool m_isBegin = true;
        bool m_isDead = false;
        int m_maxPoints = 0;
        int m_currentPoints = 0;
        std::shared_ptr<void> m_text;
        std::map<char, Character> Characters;
    private:
        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
        bool isDead();
        void onUpdate(float);
        bool cursorVisible(events::KeyPressedEvent& keyPressedEvent);
        bool onWindowClose(events::WindowCloseEvent& event);
        static Application* m_instance;
    };

}

#endif //AZATHOTH_APPLICATION_HPP
