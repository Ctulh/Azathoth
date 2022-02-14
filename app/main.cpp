//
// Created by egor on 2/7/22.
//
#define ASSERTIONS_ENABLED

#include "Logger/Logger.hpp"
#include "Application/Application.hpp"
#include "OpenGL/GraphicApiFactory/FactoryGLFW.hpp"
#include <thread>
#include "Tools/AzathothAssert.hpp"
#include "Layers/Layer.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/MouseCodes.hpp"
#include <glm/glm.hpp>
#include <Renderer/VertexBufferOpenGL.hpp>
#include <Renderer/IndexBufferOpenGL.hpp>
#include <Renderer/VertexArray.hpp>
#include <Renderer/ShaderOpenGL.hpp>

using application::Application;

    using graphicApiFactory::FactoryGLFW;



int main() {
    FactoryGLFW factory;

    Application application(factory);
    //application.pushLayer(new ExampleLayer());
    std::thread t(&Application::run, std::ref(application));
    //std::this_thread::sleep_for(std::chrono::seconds (10));
    //renderer.shutDown();
    t.join();
}