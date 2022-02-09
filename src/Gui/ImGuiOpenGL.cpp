//
// Created by egor on 2/9/22.
//

#include "Gui/ImGuiOpenGL.hpp"

#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace gui {

    bool ImGuiOpenGL::isInited() {
        return m_isInited;
    }

    void ImGuiOpenGL::setWindow(std::shared_ptr<void> window) {
        AZATHOTH_ASSERT(window.get(), "Window is null");
        m_window = std::shared_ptr<GLFWwindow>(static_cast<GLFWwindow*>(window.get()), [](auto window){}); //TODO вохможно раннее уничтожение
        if(not m_isInited) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            const char* glsl_version = "#version 130";
            ImGui_ImplGlfw_InitForOpenGL(m_window.get(), true);
            ImGui_ImplOpenGL3_Init(glsl_version);
            ImGui::StyleColorsDark();
            logger::log_info("[IMGUI OPENGL] Inited");
            m_isInited = true;
        }
    }

    void ImGuiOpenGL::draw() {
        AZATHOTH_ASSERT(m_window.get(), "Window is null");

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //
    }

    ImGuiOpenGL::~ImGuiOpenGL() {
        logger::log_info("[IMGUI OPENGL] Destructed");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}