//
// Created by egor on 2/9/22.
//

#ifndef AZATHOTH_LAYER_HPP
#define AZATHOTH_LAYER_HPP

#include <string>
#include "Events/Event.hpp"

namespace layers {

    class Layer {
    public:
        Layer(std::string const& name = "DefaultLayerName");
        virtual ~Layer();
    public:
        virtual void onAttach() const {};
        virtual void onDetach() const {};
        virtual void onUpdate() const {};
        virtual void onImGuiRender() const {};
        virtual void onEvent(events::Event&) const {};
       // virtual void begin() const {}
        //virtual void end() const {}

        inline std::string const& getName() const { return m_debugName; }
    protected:
        std::string m_debugName;
    };

}

#endif //AZATHOTH_LAYER_HPP
