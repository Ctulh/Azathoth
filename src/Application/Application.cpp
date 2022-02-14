//
// Created by egor on 2/9/22.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include <glm/gtc/matrix_transform.hpp>

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"
#include "Tools/AzathothAssert.hpp"
#include "Renderer/BufferLayout.hpp"
#include "Renderer/VertexBufferOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/VertexArrayOpenGL.hpp"
#include "Tools/FunctionBinder.hpp"
#include "Renderer/IndexBufferOpenGL.hpp"
#include "Camera/CameraManipulatorOpenGL.hpp"
#include "Camera/CameraOpenGL.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/Input.h"
#include "Object/GameObjectOpenGL.hpp"
#include "Object/PipeElements.hpp"


namespace application {
using renderer::ShaderDataType;

    window::IWindow& Application::getWindow() {
        return *m_window;
    }

    Application* Application::getInstance() {
        AZATHOTH_ASSERT(m_instance, "null instance");
        return m_instance;
    }

    bool Application::onWindowClose(events::WindowCloseEvent &event) {
        shutDown();
        return true;
    }

    void Application::pushLayer(layers::Layer* layer) {
        m_layerStack->pushLayer(layer);
    }

    void Application::pushOverlay(layers::Layer* overlay) {
        m_layerStack->pushOverlay(overlay);
    }

    Application::Application(IGraphicApiFactory const& factory):
            m_window(factory.createWindow()),
            m_camera(std::make_shared<camera::CameraOpenGL>()) {
        m_instance = this;
        m_layerStack = std::make_unique<layers::LayerStack>();
        m_layerStack->pushOverlay(factory.createGui());
     // m_layerStack->pushOverlay(factory.createCameraManipulator(m_camera));
        m_window->setEventCallback(BIND_EVENT_FN(Application, onEvent));
        m_model = std::make_shared<glm::mat4>(1.0f);
        m_drawModel = std::make_shared<glm::mat4>(1.0f);
        m_vertexArray.reset(renderer::VertexArray::create());
        m_bgVertexArray.reset(renderer::VertexArray::create());
        m_camera->setFov(60);
        m_bgModel = std::make_shared<glm::mat4>(1.0f);
        *m_bgModel = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f,5.0f,5.0f));
        m_bgTexture = std::make_shared<Texture>("/home/egor/Downloads/1.png");


        m_bgTexture->Bind(1);
       m_pipes = std::make_shared<object::PipeElements>();

       float backGroundVerticies[] = {
               -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
               -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
               1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
               1.0f, 1.0f, -1.0, 1.0f, 0.0f,
               //-,-
               //-,+
              // +,-
               //+,+
       };

       auto backGroundVB = std::make_shared<renderer::VertexBufferOpenGL>(backGroundVerticies, sizeof(backGroundVerticies));
        {
            renderer::BufferLayout layout = {
                    {renderer::ShaderDataType::Float3, "a_Position"},
                    {renderer::ShaderDataType::Float2, "texCoord"}
            };

            backGroundVB->setLayout(layout);
        }
        m_bgVertexArray->addVertexBuffer(backGroundVB);
        uint32_t backgroundIndices[6] = {0,1,2, 2, 1, 3};
        auto backgroundIB = std::make_shared<renderer::IndexBufferOpenGL>(backgroundIndices, sizeof(backgroundIndices)/ sizeof(uint32_t));
        m_bgVertexArray->setIndexBuffer(backgroundIB);

        float verticies[ ] = {
                -0.25f, -0.25f, 0.0f,
                0.25f, -0.25f, 0.0f,
                0.25f, 0.25f, 0.0f,
                -0.25f, 0.25f, 0.0f
        };

        m_vertexBuffer.reset(renderer::IVertexBuffer::create(verticies, sizeof(verticies)));

        uint32_t indices[12] = {0,1,2, 2, 3, 0};
        {
            renderer::BufferLayout layout = {
                    {renderer::ShaderDataType::Float3, "a_Position"}
            };

            m_vertexBuffer->setLayout(layout);
        }

        m_vertexArray->addVertexBuffer(m_vertexBuffer);

        m_indexBuffer.reset(IIndexBuffer::create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_vertexArray->setIndexBuffer(m_indexBuffer);

        m_shader = factory.createShader("shader.vert", "shader.frag");
    }

    void Application::onUpdate(float timeStep) {
        m_pipes->onUpdate(timeStep);
        float fallSpeed = 0.007f;
        acceleration = acceleration - fallSpeed + inertia;

        height += fabs(acceleration) * acceleration;

        if(inertia > 0) {
            inertia -= fallSpeed;
        }
        //logger::log_info("acceleration {}, inertia {}", acceleration, inertia);
       *m_drawModel = glm::translate(*m_model, glm::vec3(0.0f, height, 0.0f));

        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onUpdate(timeStep);
        }
    }

    void Application::onEvent(events::Event& event) {
        events::EventDispatcher dispatcher(event);
        dispatcher.dispatch<events::WindowCloseEvent>(BIND_EVENT_FN(Application, onWindowClose));
        dispatcher.dispatch<events::KeyPressedEvent>(BIND_EVENT_FN(Application, cursorVisible));
        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onEvent(event);
            if (event.isHandled()) {
                break;
            }
        }
    }

    bool Application::cursorVisible(events::KeyPressedEvent &keyPressedEvent) {
        static bool isCursorVisible = false;
        if(keyPressedEvent.getKeyCode() == KEY_ESCAPE) {
            if(isCursorVisible) {
                input::Input::hideCursor();
            }
            else {
                input::Input::showCursor();
            }
            isCursorVisible = !isCursorVisible;
            return true;
        }
        else if(keyPressedEvent.getKeyCode() == KEY_SPACE) {
            float jump = 0.06;
            inertia += jump;
            acceleration = 0;
            logger::log_info("[APPLICATION] Space Pressed");
            return true;
        }
        return false;
    }

    void Application::run() {
        if(m_isRunning.test_and_set(std::memory_order_acquire)) {
            logger::log_info("[RENDERER] Renderer in already running");
            return;
        }
        if(not m_window) {
            logger::log_error("[RENDERER] Window is NUll");
            return;
        }
        logger::log_info("[RENDERER] Renderer is running");
        glfwMakeContextCurrent((GLFWwindow*)(m_window->getNativeWindow().get()));
        auto gui = dynamic_cast<gui::ImGuiLayerGLFW*>((*m_layerStack)["GUI"]);

        float color[] = {0.52f, 0.8f, 0.92f};
        float birdColor[] = {0.2, 0.4, 0.0};

        glEnable(GL_DEPTH_TEST);
        while(m_isRunning.test(std::memory_order_acquire)) {
            renderer::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
            renderer::RenderCommand::clear();

            float time = (float)glfwGetTime();
            float timestep = time - m_lastTimeStep;
            m_lastTimeStep = time;

            //logger::log_info("[MAIN LOOP] {}ms", timestep * 1000.0f);

            renderer::Renderer::beginScene(m_shader, m_camera->getViewProjectionPointer());
            m_shader->setUniformMatrix4f("Model", &(*m_drawModel)[0][0]);
            m_shader->setUniformVec3f("Color", birdColor);
            m_shader->bind();
            renderer::Renderer::Submit(m_vertexArray);
            m_shader->setUniformMatrix4f("Model", &(*m_bgModel)[0][0]);
            m_shader->setUniform1i("u_Texture", 1);
            m_shader->setUniformVec3f("Color", color);
            m_shader->bind();
            renderer::Renderer::Submit(m_bgVertexArray);
            m_pipes->bind(m_shader);
            renderer::Renderer::endScene();



            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onUpdate(timestep);
            }

            this->onUpdate(timestep);
            m_window->onUpdate();
        }
    }

    void Application::shutDown() {
        if(not m_isRunning.test()) {
            logger::log_info("[RENDERER] Renderer is already shutDowned");
            return;
        }

        while(m_isRunning.test(std::memory_order_acquire)) {
            m_isRunning.clear(std::memory_order_release);
        }
       // m_gui.reset();
       // m_window.reset();
        logger::log_info("[RENDERER] Renderer is stopped");
    }

    Application* Application::m_instance = nullptr;

}
//0.52f, 0.8f, 0.92f,