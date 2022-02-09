//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUIOPENGL_HPP
#define AZATHOTH_IMGUIOPENGL_HPP

#include <atomic>

#include "IGui.hpp"
#include "GLFW/glfw3.h"

namespace gui {

    class ImGuiOpenGL: public IGui {
    public:
        ImGuiOpenGL() = default;
        ~ImGuiOpenGL();
    public:
        bool isInited() override;
        void setWindow(std::shared_ptr<void> window) override;
        void draw() override;
    private:
        bool m_isInited = false;
        std::shared_ptr<GLFWwindow> m_window;
    };

}

#endif //AZATHOTH_IMGUIOPENGL_HPP
