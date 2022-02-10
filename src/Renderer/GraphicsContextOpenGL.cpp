//
// Created by egor on 2/10/22.
//
#include "Renderer/GraphicsContextOpenGL.hpp"
#include "DebugTools/OpenGLTools/OpenGLTools.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "glad/glad.h"

#include <GLFW/glfw3.h>

namespace renderer {

    GraphicsContextOpenGL::GraphicsContextOpenGL(std::shared_ptr<GLFWwindow> window): m_window(window) {
        AZATHOTH_ASSERT(m_window, "Window is NULL");
    }

    void GraphicsContextOpenGL::init() {
        glfwMakeContextCurrent(m_window.get());
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        AZATHOTH_ASSERT(status, "Glad Initialize failed");
    }

    void GraphicsContextOpenGL::swapBuffers() {
        glfwSwapBuffers(m_window.get());
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}