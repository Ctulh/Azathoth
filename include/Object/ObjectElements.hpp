//
// Created by egor on 2/14/22.
//

#ifndef AZATHOTH_OBJECTELEMENTS_HPP
#define AZATHOTH_OBJECTELEMENTS_HPP

#include <memory>

#include "Object.hpp"
#include "Renderer/IShader.hpp"

namespace object {

    class ObjectElements {
    public:
        virtual void addObject(std::shared_ptr<GameObject>) = 0;
        virtual void bind(std::shared_ptr<renderer::IShader>) = 0;
        virtual void onUpdate(float) = 0;
        virtual bool checkColission(float, float, float) = 0;
        virtual bool isPipeFlown(float x) = 0;
        virtual void restart() = 0;
        virtual void next() = 0;
    public:
        virtual ~ObjectElements() = default;
    };

}

#endif //AZATHOTH_OBJECTELEMENTS_HPP
