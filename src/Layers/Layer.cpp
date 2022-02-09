//
// Created by egor on 2/9/22.
//
#include "Layers/Layer.hpp"
#include "Logger/Logger.hpp"

namespace layers {
    Layer::Layer(const std::string &name) {
        m_debugName = name;
        logger::log_info("[LAYERS] Created new layer: " + m_debugName);
    }

    Layer::~Layer() {
        logger::log_info("[LAYERS] Destructed layer: " + m_debugName);
    }
}