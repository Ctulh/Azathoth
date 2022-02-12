//
// Created by egor on 2/12/22.
//

#ifndef AZATHOTH_CAMERA_OPENGL_HPP
#define AZATHOTH_CAMERA_OPENGL_HPP

#include <memory>
#include <atomic>

#include "Camera/Camera.hpp"

namespace camera {

    class CameraOpenGL: public Camera {
    public:
        CameraOpenGL();
    public:
        void setPosition(glm::vec3 const&) override;
        void setRatio(float) override;
        void setFov(float) override;
        void moveTo(glm::vec3 const&) override;

        float const* const getPointer() override;
    private:
        struct Projection {
            Projection() {
                fovAngle = 45.0f;
                ratio = 16.0 / 9;
                minDistance = 0.1f;
                maxDistance = 100.0f;
            }
        public:
            float fovAngle;
            float ratio;
            float minDistance;
            float maxDistance;
        };
        struct View {
            View(): pos(0, 0, 3), lookAt(0, 0, 0), headPos(0, 1, 0) {}
        public:
            glm::vec3 pos;
            glm::vec3 lookAt;
            glm::vec3 headPos;
        };
    private:
        void calculateViewMatrix();
        void calculateProjectionMatrix();
        void calculateMatrix();
        void clearViewRelevance();
        void clearProjectionRelevance();
    private:
        std::unique_ptr<glm::mat4> m_lastViewMatrix;
        std::unique_ptr<glm::mat4> m_lastProjectionMatrix;
        std::unique_ptr<glm::mat4> m_lastProjectionViewMatrix;
        std::unique_ptr<Projection> m_projectionData;
        std::unique_ptr<View> m_viewData;
        std::atomic_flag m_isProjectionValid = ATOMIC_FLAG_INIT;
        std::atomic_flag m_isViewValid = ATOMIC_FLAG_INIT;
        std::atomic_flag m_isMatrixValid = ATOMIC_FLAG_INIT;
    };

}

#endif //AZATHOTH_CAMERA_OPENGL_HPP
