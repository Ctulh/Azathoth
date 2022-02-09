//
// Created by egor on 2/7/22.
//
#define ASSERTIONS_ENABLED

#include "Logger/Logger.hpp"
#include "Application/Application.hpp"
#include <GraphicApiFactory/OpenGLFactory.hpp>
#include <thread>
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "Layers/Layer.hpp"

using application::Application;

class ExampleLayer: public layers::Layer {
public:
    ExampleLayer(): Layer("Example") {}

    void onUpdate() const override {
       // logger::log_info("ExampleLayer: onUpdate");
    }

    void onEvent(events::Event& event) const override {
        logger::log_info("ExampleLayer: {}", event.toString());
    };
};

    using graphicApiFactory::OpenGLFactory;

int main() {
    OpenGLFactory factory;

    Application application(factory);
    application.pushLayer(new ExampleLayer());
    std::thread t(&Application::run, std::ref(application));
    //std::this_thread::sleep_for(std::chrono::seconds (10));
    //renderer.shutDown();
    t.join();
}