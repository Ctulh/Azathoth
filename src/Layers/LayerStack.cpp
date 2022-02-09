//
// Created by egor on 2/9/22.
//
#include "Layers/LayerStack.hpp"

namespace layers {

    LayerStack::~LayerStack() {
        for(auto layer: m_layers)
            delete layer;
    }

    LayerStack::LayerStack() {
        m_layerInsert = m_layers.begin();
    }

    void LayerStack::pushLayer(Layer* layer) {
        m_layerInsert = m_layers.emplace(m_layerInsert, layer);
    }

    void LayerStack::pushOverlay(Layer* overlay) {
        m_layers.emplace_back(overlay);
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if(it != m_layers.end()) {
            m_layers.erase(it);
            m_layerInsert--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay) {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if(it != m_layers.end()) {
            m_layers.erase(it);
        }
    }
}
