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
        void init(std::shared_ptr<WindowType> window) override;
        void draw() override;
    private:
        std::atomic_flag m_isInited = false;
        std::shared_ptr<WindowType> m_window;
    };

    template <typename WindowType>
    bool ImGuiOpenGL<WindowType>::isInited() {
        return m_isInited.test(std::memory_order_acquire);
    }

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::init(std::shared_ptr<WindowType> window) {
        AZATHOTH_ASSERT(window.get(), "Window is null");

        if(not m_isInited.test_and_set(std::memory_order_acquire)) {
           IMGUI_CHECKVERSION();
           ImGui::CreateContext();
           ImGuiIO &io = ImGui::GetIO();
           const char* glsl_version = "#version 130";
           ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
           ImGui_ImplOpenGL3_Init(glsl_version);
           ImGui::StyleColorsDark();
           m_window = window;
           logger::log_info("[IMGUI OPENGL] Inited");
       }
    }

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::draw() {
        //AZATHOTH_ASSERT(window.get(), "Window is null");
        glfwPollEvents();
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

        glfwSwapBuffers(m_window.get());
        //
    }

    template <typename WindowType>
    ImGuiOpenGL<WindowType>::~ImGuiOpenGL() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_window.get());
        glfwTerminate();
    }
}

#endif //AZATHOTH_IMGUIOPENGL_HPP
