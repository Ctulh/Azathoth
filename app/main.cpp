//
// Created by egor on 2/7/22.
//
#include "Logger/Logger.hpp"
#include "Renderer/Renderer.hpp"
#include <thread>

using renderer::Renderer;

int main() {
    Renderer renderer;
    std::thread t(&Renderer::run, std::ref(renderer));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    renderer.stop();
    t.join();

}