//
// Created by egor on 2/14/22.
//

#ifndef AZATHOTH_OBJECT_HPP
#define AZATHOTH_OBJECT_HPP

#include "Layers/Layer.hpp"
#include "Renderer/VertexArray.hpp"
#include <glm/glm.hpp>
#include "Renderer/IShader.hpp"
#include <memory>

namespace object {

    class GameObject {
    public:
        virtual void onUpdate(float) = 0;
        virtual void move(glm::vec3 const&) = 0;
        virtual bool checkCollision(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>) = 0;
        virtual std::shared_ptr<renderer::VertexArray> getVertexArray() = 0;
        virtual void bind(std::shared_ptr<renderer::IShader>) = 0;
    public:
        virtual ~GameObject() = default;
    };

}

#endif //AZATHOTH_OBJECT_HPP
