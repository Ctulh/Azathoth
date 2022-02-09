//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUIOPENGL_HPP
#define AZATHOTH_IMGUIOPENGL_HPP

#include <atomic>

#include "IGui.hpp"
#include "Logger/Logger.hpp"
#include "DebugTools/CommonTools/AzathothAssert.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace gui {

    template <typename WindowType>
    class ImGuiOpenGL: public IGui<WindowType> {
    public:
        ImGuiOpenGL() = default;
        ~ImGuiOpenGL();
    public:
        bool isInited() override;
        void setWindow(std::shared_ptr<WindowType> window) override;
        void draw() override;
    private:
        bool m_isInited = false;
        std::shared_ptr<WindowType> m_window;
    };

    template <typename WindowType>
    bool ImGuiOpenGL<WindowType>::isInited() {
        return m_isInited;
    }

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::setWindow(std::shared_ptr<WindowType> window) {
        AZATHOTH_ASSERT(window.get(), "Window is null");
        m_window = window;
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

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::draw() {
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

    template <typename WindowType>
    ImGuiOpenGL<WindowType>::~ImGuiOpenGL() {
        if(m_window.get()) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(m_window.get());
            glfwTerminate();
        }
    }
}

#endif //AZATHOTH_IMGUIOPENGL_HPP
