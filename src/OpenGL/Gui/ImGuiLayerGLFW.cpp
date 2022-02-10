//
// Created by egor on 2/9/22.
//

#include "OpenGL/Gui/ImGuiLayerGLFW.hpp"

#include "Logger/Logger.hpp"
#include "DebugTools/AzathothAssert.hpp"
#include "Application/Application.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

namespace gui {

    ImGuiLayerGLFW::ImGuiLayerGLFW(): layers::Layer("GUI") {}

    void ImGuiLayerGLFW::onAttach() const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

       ImGuiIO &io = ImGui::GetIO(); //(void)io;
       io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
       io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
       io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


       ImGuiStyle& style = ImGui::GetStyle();
       if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        auto application = application::Application::getInstance();
        GLFWwindow* window = static_cast<GLFWwindow*>(application->getWindow().getNativeWindow().get());
        AZATHOTH_ASSERT(window, "Window is null");

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::StyleColorsDark();


        logger::log_info("[IMGUI OPENGL] Attached");
    }

    void ImGuiLayerGLFW::onDetach() const {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        logger::log_info("[IMGUI OPENGL] Detached");
    }

    void ImGuiLayerGLFW::onImGuiRender() const {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayerGLFW::begin() const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayerGLFW::end() const {
        ImGuiIO &io = ImGui::GetIO();
        auto application = application::Application::getInstance();
        io.DisplaySize = ImVec2(application->getWindow().getWidth(), application->getWindow().getHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContext);
        }

      //  glClear(GL_COLOR_BUFFER_BIT);
    }

    ImGuiLayerGLFW::~ImGuiLayerGLFW() {

    }


}