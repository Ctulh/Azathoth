//
// Created by egor on 2/7/22.
//
#include "Renderer/Renderer.hpp"
#include "Logger/Logger.hpp"

namespace renderer {

    void Renderer::run() const {
        logger::log_info("[RENDERER] run");
    }

    void Renderer::stop() const {
        logger::log_info("[RENDERER] stop");
    }
}