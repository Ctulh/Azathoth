//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_IAPPLICATION_HPP
#define AZATHOTH_IAPPLICATION_HPP
#include "Events/Event.hpp"
#include "Layers/Layer.hpp"

namespace application {

    class IApplication {
    public:
        virtual void run() = 0;
        virtual void shutDown() = 0;
        virtual void onEvent(events::Event&) = 0;
        virtual void pushLayer(layers::Layer*) = 0;
        virtual void pushOverlay(layers::Layer*) = 0;
    public:
        virtual ~IApplication() = default;
    };
}

#endif //AZATHOTH_IAPPLICATION_HPP
