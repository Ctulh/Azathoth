//
// Created by egor on 2/12/22.
//

#include "Camera/CameraOpenGL.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace camera {

    CameraOpenGL::CameraOpenGL():
                                    m_lastProjectionViewMatrix(std::make_unique<glm::mat4>()),
                                    m_lastProjectionMatrix(std::make_unique<glm::mat4>()),
                                    m_lastViewMatrix(std::make_unique<glm::mat4>()),
                                    m_projectionData(std::make_unique<Projection>()),
                                    m_viewData(std::make_unique<View>()) {}

    void CameraOpenGL::setPosition(glm::vec3 const& pos) {
        m_viewData->pos = pos;
        clearViewRelevance();
    }

    void CameraOpenGL::setFov(float fovAngle) {
        m_projectionData->fovAngle = fovAngle;
        clearProjectionRelevance();
    }

    void CameraOpenGL::setRatio(float ratio) {
        m_projectionData->ratio = ratio;
        clearProjectionRelevance();
    }

    void CameraOpenGL::moveTo(glm::vec3 const& translate) {
        m_viewData->pos += translate;
        clearViewRelevance();
    }

    const glm::mat4 &CameraOpenGL::getMat4() {
        calculateMatrix();
        return *m_lastProjectionViewMatrix;
    }

    void CameraOpenGL::calculateViewMatrix() {
        if(m_isViewValid.test_and_set()) {
            return;
        }
        *m_lastViewMatrix = glm::lookAt(
                m_viewData->pos,     // Камера находится в мировых координатах (4,3,3)
                m_viewData->lookAt,  // И направлена в начало координат
                m_viewData->headPos  // "Голова" находится сверху
        );
    }

    void CameraOpenGL::calculateProjectionMatrix() {
        if(m_isProjectionValid.test_and_set()) {
            return;
        }
       *m_lastProjectionMatrix = glm::perspective(glm::radians(m_projectionData->fovAngle),
                                                               m_projectionData->ratio,
                                                               m_projectionData->minDistance,
                                                               m_projectionData->maxDistance);
    }

    void CameraOpenGL::calculateMatrix() {
        if(m_isMatrixValid.test_and_set()) {
            return;
        }
        calculateViewMatrix();
        calculateProjectionMatrix();
        *m_lastProjectionViewMatrix = (*m_lastProjectionMatrix) * (*m_lastViewMatrix);
    }

    void CameraOpenGL::clearProjectionRelevance() {
        m_isProjectionValid.clear();
        m_isMatrixValid.clear();
    }

    void CameraOpenGL::clearViewRelevance() {
        m_isViewValid.clear();
        m_isMatrixValid.clear();
    }
}