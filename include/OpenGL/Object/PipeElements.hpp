//
// Created by egor on 2/14/22.
//

#ifndef AZATHOTH_PIPEELEMENTS_HPP
#define AZATHOTH_PIPEELEMENTS_HPP

#include "Object/ObjectElements.hpp"

#include <vector>
#include <glm/glm.hpp>
#include "Texture/Texture.h"
#include "Renderer/BasicMesh.hpp"

namespace object {

    class PipeElements: public ObjectElements {
    public:
        PipeElements();
    public:
        void bind(std::shared_ptr<renderer::IShader>) override;
        void addObject(std::shared_ptr<GameObject>) override;
        void onUpdate(float) override;
        bool checkColission(float,float, float) override;
        bool isPipeFlown(float x) override;
        void restart() override;
        void next() override;
    private:
        std::shared_ptr<GameObject> createPipe();
        void createPipeColumn(float);
        void moveColumn(float);
        void moveToBegin();
    private:
        struct object {
            std::shared_ptr<glm::mat4> m_model;
            std::shared_ptr<Mesh> m_mesh;
            uint32_t index;
            bool pipeFlown;
        };
    private:
        std::vector<std::shared_ptr<object>> m_Objects;
        std::shared_ptr<Texture> m_texture;
        std::vector<glm::vec4> m_borders;
        int currentPipe = 0;
    };

}

#endif //AZATHOTH_PIPEELEMENTS_HPP
