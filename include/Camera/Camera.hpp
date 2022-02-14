//
// Created by egor on 2/12/22.
//

#ifndef AZATHOTH_CAMERA_HPP
#define AZATHOTH_CAMERA_HPP

#include <glm/glm.hpp>

namespace camera {

    class Camera {
    public:
        virtual void setPosition(glm::vec3 const&) = 0;
        virtual void setRatio(float) = 0;
        virtual void setFov(float) = 0;
        virtual void moveTo(glm::vec3 const&) = 0;
        virtual void rotate(float, float) = 0;
        virtual void changeFov(float) = 0;

        virtual float const* const getViewPointer() = 0;
        virtual float const* const getProjectionPointer() = 0;
        virtual float const* const getViewProjectionPointer() = 0;
    public:
        ~Camera() = default;
    };
}

#endif //AZATHOTH_CAMERA_HPP
