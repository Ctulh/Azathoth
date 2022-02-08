//
// Created by egor on 2/7/22.
//
#define ASSERTIONS_ENABLED

#include "Logger/Logger.hpp"
#include "Renderer/Renderer.hpp"
#include <GraphicApiFactory/OpenGLFactory.hpp>
#include <thread>
#include "DebugTools/CommonTools/AzathothAssert.hpp"

using renderer::Renderer;

int main() {
    Renderer<graphicApiFactory::OpenGLFactory> renderer;
    std::thread t(&Renderer<graphicApiFactory::OpenGLFactory>::run, std::ref(renderer));
    std::this_thread::sleep_for(std::chrono::seconds (10));
    renderer.stop();
    t.join();
}