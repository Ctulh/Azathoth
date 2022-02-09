//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_LAYERSTACK_HPP
#define AZATHOTH_LAYERSTACK_HPP

#include <vector>

#include "Layer.hpp"

namespace layers {

    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();
    public:
        void pushLayer(Layer*);
        void pushOverlay(Layer*);
        void popLayer(Layer*);
        void popOverlay(Layer*);

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_layers.end(); }
    private:
        std::vector<Layer*> m_layers;
        std::vector<Layer*>::iterator m_layerInsert;
    };

}

#endif //AZATHOTH_LAYERSTACK_HPP
