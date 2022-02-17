//
// Created by egor on 2/9/22.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Application/Application.hpp"
#include "Logger/Logger.hpp"
#include "Tools/AzathothAssert.hpp"
#include "Renderer/BufferLayout.hpp"
#include "Renderer/VertexBufferOpenGL.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Tools/FunctionBinder.hpp"
#include "Renderer/IndexBufferOpenGL.hpp"
#include "Camera/CameraManipulatorOpenGL.hpp"
#include "Camera/CameraOpenGL.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/Input.h"
#include "Gui/ImGuiLayerGLFW.hpp"
#include "Renderer/BasicMesh.hpp"

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
        m_lightPos = std::make_shared<glm::vec3>(0.0f);
        m_layerStack->pushOverlay(factory.createCameraManipulator(m_camera));
        m_window->setEventCallback(BIND_EVENT_FN(Application, onEvent));
        m_model = std::make_shared<glm::mat4>(1.0f);
        m_lightModel =std::make_shared<glm::mat4>(1.0f);
        m_vertexArray.reset(renderer::VertexArray::create());

        float verticies[ ] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, -1.0f,
                0.5f, 0.5f, -1.0f
        };

        m_vertexBuffer.reset(renderer::IVertexBuffer::create(verticies, sizeof(verticies)));

        uint32_t indices[12] = {0,1,2, 2, 3, 0, 1, 4, 2, 2, 4, 5};
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
        m_shaderDefault = factory.createShader("shaderColored.vert", "shaderColored.frag");
    }

    static float fi = 0.0f;
    static glm::mat4 matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));
    void Application::onUpdate() {
     //  *m_lightPos = glm::rotate(*m_lightPos, glm::radians(fi), glm::vec3(0.0f,1.0f,0.0f));
        fi += 0.2;
        *m_lightModel = glm::rotate(matrix, glm::radians(fi), glm::vec3(0.0f,1.0f,0.0f));
        *m_lightModel = glm::translate(*m_lightModel, glm::vec3(3,0,0));
        //m_lightModel->operator[](0).x = m_lightPos->x;
        //m_lightModel->operator[](0).y = m_lightPos->y;
        m_lightPos->x = m_lightModel->operator[](3).x;
        m_lightPos->y = m_lightModel->operator[](3).y;
        m_lightPos->z = m_lightModel->operator[](3).z;

        for(auto it = m_layerStack->end(); it!= m_layerStack->begin();) {
            (*--it)->onUpdate();
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


        float lightColor [] ={1,1,1};
        float materialAmbient [] = {0.1,0.1,0.1};
        float materialSpecular [] = {0.1,0.1,0.1};
        float materialDiffuse [] = {0.1,0.1,0.1};
        float lightAmbient [] = {0.1,0.1,0.1};
        float lightDiffuse [] = {0.5,0.5,0.5};
        float lightSpecular [] = {0.1,0.1,0.1};


        glm::mat3 mat1 = glm::mat4(1.0f);
        float shininess = 0.1;
        float strength = 0.1;
        float specularStrength = 0.1;

        glEnable(GL_DEPTH_TEST);

        std::shared_ptr<Mesh> model = std::make_shared<Mesh>("/home/egor/Downloads/sphere.obj");
        std::shared_ptr<Mesh> light = std::make_shared<Mesh>("/home/egor/Downloads/sphere.obj");
        std::shared_ptr<Texture> texture = std::make_shared<Texture>("/home/egor/Downloads/Basic-OpenGL-with-GLFW-Assimp-master/Assets/BrickColor.png");
        std::shared_ptr<Texture> textureNormal = std::make_shared<Texture>("/home/egor/Downloads/container2_specular.png");
        texture->Bind(1);
        textureNormal->Bind(2);

        glm::mat4 mat = glm::mat4(1.0f);

        auto imGUI =new gui::ImGuiLayerGLFW;

        imGUI->addSlider("light X: ", &(m_lightPos->x));
        imGUI->addSlider("light Y: ", &(m_lightPos->y));
        imGUI->addSlider("light Z: ", &(m_lightPos->z));

        imGUI->addSlider("lightColor X: ", &(lightColor[0]));
        imGUI->addSlider("lightColor Y: ", &(lightColor[1]));
        imGUI->addSlider("lightColor Z: ", &(lightColor[2]));


        imGUI->addColorEdit("LightAmbient", lightAmbient);
        imGUI->addColorEdit("LightlDiffuse", lightDiffuse);
        imGUI->addColorEdit("LightSpecular", lightSpecular);

        imGUI->addSlider("MaterialShininess: ", &shininess);
        imGUI->addSlider("strength: ", &strength);



        float other[] = {0.3,0.3,0.3};

        //float color [] = {0.0,0.0,0.0};

        m_layerStack->pushOverlay((layers::Layer*)(imGUI));

        auto gui = dynamic_cast<gui::ImGuiLayerGLFW*>((*m_layerStack)["GUI"]);
        while(m_isRunning.test(std::memory_order_acquire)) {
            renderer::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
            renderer::RenderCommand::clear();

            m_shader->bind();
            //renderer::Renderer::beginScene(m_shader, m_camera->getViewProjectionPointer());
            m_shader->setUniformMatrix4f("view", m_camera->getViewPointer());
            m_shader->setUniformMatrix4f("projection", m_camera->getProjectionPointer());
            m_shader->setUniformMatrix4f("model", &(mat)[0][0]);
            m_shader->setUniformVec3f("lightPos", &((*m_lightPos)[0]));

           // m_shader->setUniformVec3f("viewPos", other);

            m_shader->setUniform1i("material.diffuse", 1);
            m_shader->setUniform1i("material.specular", 2);
            m_shader->setUniform1f("material.shininess", shininess);

            m_shader->setUniformVec3f("light.ambient", lightAmbient);
            m_shader->setUniformVec3f("light.diffuse", lightDiffuse);
            m_shader->setUniformVec3f("light.specular", lightSpecular);

            model->Draw();


            m_shaderDefault->bind();
            m_shaderDefault->setUniformMatrix4f("cameraView", m_camera->getViewProjectionPointer());
            m_shaderDefault->setUniformMatrix4f("model", &(*m_lightModel)[0][0]);
            light->Draw();

            renderer::Renderer::endScene();


            gui->begin();
            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onImGuiRender();
            }
            gui->end();

            for (layers::Layer* layer: (*m_layerStack)) {
                layer->onUpdate();
            }
            onUpdate();
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
