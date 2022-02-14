//
// Created by egor on 2/14/22.
//

#ifndef AZATHOTH_GAMEOBJECTOPENGL_HPP
#define AZATHOTH_GAMEOBJECTOPENGL_HPP

#include "Object/Object.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/IIndexBuffer.hpp"

namespace object {

    using renderer::VertexArray;
    using renderer::IVertexBuffer;
    using renderer::IIndexBuffer;

    class GameObjectOpenGL: public GameObject {
    public:
        GameObjectOpenGL(std::shared_ptr<VertexArray>);
    public:
        void onUpdate(float) override;
        void move(const glm::vec3 &) override;
        bool checkCollision(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>) override;
        std::shared_ptr<renderer::VertexArray> getVertexArray() override;
        void bind(std::shared_ptr<renderer::IShader>) override;
    private:
        std::shared_ptr<glm::mat4> m_model;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<IIndexBuffer> m_indexBuffer;
        std::shared_ptr<IVertexBuffer> m_vertexBuffer;
    };

}

#endif //AZATHOTH_GAMEOBJECTOPENGL_HPP
