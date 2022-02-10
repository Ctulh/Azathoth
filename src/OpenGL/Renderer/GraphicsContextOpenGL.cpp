//
// Created by egor on 2/10/22.
//
#include "OpenGL/Renderer/GraphicsContextOpenGL.hpp"
#include "OpenGL/DebugTools/OpenGLTools.hpp"
#include "DebugTools/AzathothAssert.hpp"
#include "Logger/Logger.hpp"
#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace renderer {

    GraphicsContextOpenGL::GraphicsContextOpenGL(std::shared_ptr<GLFWwindow> window): m_window(window) {
        AZATHOTH_ASSERT(m_window, "Window is NULL");
    }

    void GraphicsContextOpenGL::init() {
        glfwMakeContextCurrent(m_window.get());
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        AZATHOTH_ASSERT(status, "Glad Initialize failed");
        logger::log_info("[OPENGL WINDOW] Detect \"{} {}\" video card", (const char*)(glGetString(GL_VENDOR)),
                         (const char*)(glGetString(GL_RENDERER)));
    }

    void GraphicsContextOpenGL::swapBuffers() {
        glfwSwapBuffers(m_window.get());
    }
}