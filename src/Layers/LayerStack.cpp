//
// Created by egor on 2/9/22.
//
#include "Layers/LayerStack.hpp"
#include "Logger/Logger.hpp"

namespace layers {

    LayerStack::~LayerStack() {
        for(auto layer: m_layers)
            delete layer;
    }

    LayerStack::LayerStack() {};

    void LayerStack::pushLayer(Layer* layer) {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
        m_layerInsertIndex++;
        layer->onAttach();
    }

    void LayerStack::pushOverlay(Layer* overlay) {
        m_layers.emplace_back(overlay);
        overlay->onAttach();
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if(it != m_layers.end()) {
            m_layers.erase(it);
            m_layerInsertIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay) {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if(it != m_layers.end()) {
            m_layers.erase(it);
        }
    }

    Layer* LayerStack::operator[](std::string const& layerName) {
        auto it = std::find_if(m_layers.begin(), m_layers.end(), [&layerName](Layer* layer) {
            return layer->getName() == layerName;
        });
        if(it == m_layers.end()) {
            logger::log_info("[LAYER STACK] Can't find layer with name: " + layerName);
            return nullptr;
        }
        return *it;
    }
}
