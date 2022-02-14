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

using application::Application;

class ExampleLayer: public layers::Layer {
public:
    ExampleLayer(): Layer("Example") {}

    void onUpdate() override {
       /// logger::log_info("ExampleLayer: onUpdate");

        if(input::Input::isKeyPressed(KEY_TAB)) {
            logger::log_info("ExampleLayer: Tab Pressed");
        }

    }

    void onEvent(events::Event& event) override {
       // logger::log_info("ExampleLayer: {}", event.toString());
    };

    ~ExampleLayer() {
        logger::log_info("[EXAMPLE LAYER] Destructed");
    }
};

    using graphicApiFactory::FactoryGLFW;



int main() {
    FactoryGLFW factory;

    Application application(factory);
    application.pushLayer(new ExampleLayer());
    std::thread t(&Application::run, std::ref(application));
    //std::this_thread::sleep_for(std::chrono::seconds (10));
    //renderer.shutDown();
    t.join();
}