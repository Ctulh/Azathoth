//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUIOPENGL_HPP
#define AZATHOTH_IMGUIOPENGL_HPP

#include <atomic>

#include "Layers/Layer.hpp"


namespace gui {

class ImGuiOpenGL: public layers::Layer {
    public:
        ImGuiOpenGL();
        ~ImGuiOpenGL();
    public:
        void onAttach() const override;
        void onDetach() const override;
        void onImGuiRender() const override;

        void begin();
        void end();
    };

}

#endif //AZATHOTH_IMGUIOPENGL_HPP
