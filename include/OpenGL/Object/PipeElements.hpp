//
// Created by egor on 2/14/22.
//

#ifndef AZATHOTH_PIPEELEMENTS_HPP
#define AZATHOTH_PIPEELEMENTS_HPP

#include "Object/ObjectElements.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace object {

    class PipeElements: public ObjectElements {
    public:
        PipeElements();
    public:
        void bind(std::shared_ptr<renderer::IShader>) override;
        void addObject(std::shared_ptr<GameObject>) override;
        void onUpdate(float) override;
    private:
        std::shared_ptr<GameObject> createPipe();
        void createPipeColumn(float);
        void moveColumn(float);
        void moveToBegin();
    private:
        struct object {
            std::shared_ptr<glm::mat4> m_model;
            std::shared_ptr<GameObject> m_object;
        };
    private:
        std::vector<std::shared_ptr<object>> m_Objects;
    };

}

#endif //AZATHOTH_PIPEELEMENTS_HPP
