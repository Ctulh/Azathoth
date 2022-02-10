//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUILAYERGLFW_HPP
#define AZATHOTH_IMGUILAYERGLFW_HPP

#include <atomic>

#include "Layers/Layer.hpp"


namespace gui {

class ImGuiLayerGLFW: public layers::Layer {
    public:
        ImGuiLayerGLFW();
        ~ImGuiLayerGLFW();
    public:
        void onAttach() const override;
        void onDetach() const override;
        void onImGuiRender() const override;

        void begin() const;
        void end() const;
    };

}

#endif //AZATHOTH_IMGUILAYERGLFW_HPP
