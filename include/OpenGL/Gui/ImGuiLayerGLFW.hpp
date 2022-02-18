//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUILAYERGLFW_HPP
#define AZATHOTH_IMGUILAYERGLFW_HPP

#include <atomic>

#include "Layers/Layer.hpp"
#include <map>

namespace gui {

class ImGuiLayerGLFW: public layers::Layer {
    public:
        ImGuiLayerGLFW();
        ~ImGuiLayerGLFW();
    public:
        void onAttach() const override;
        void onDetach() const override;
        void onImGuiRender() const override;
        void addSlider(std::string const&, float*);
        void addColorEdit(std::string const&, float*);
        void addCheckBox(std::string const&, bool*);

        void begin() const;
        void end() const;
    private:
    std::map<std::string, float*> m_sliders;
    std::map<std::string, float*> m_colorEdits;
    std::map<std::string, bool*> m_checkbox;
    };

}

#endif //AZATHOTH_IMGUILAYERGLFW_HPP
