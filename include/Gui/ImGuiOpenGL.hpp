//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_IMGUIOPENGL_HPP
#define AZATHOTH_IMGUIOPENGL_HPP

#include <atomic>
#include "IGui.hpp"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace gui {

    template <typename WindowType>
    class ImGuiOpenGL: public IGui<WindowType> {
    public:
        ImGuiOpenGL() = default;
    public:
        bool isInited() override;
        void init(std::shared_ptr<WindowType> window) override;
        void draw(std::shared_ptr<WindowType> window) override;
    private:
        std::atomic_flag m_isInited = false;
    };

    template <typename WindowType>
    bool ImGuiOpenGL<WindowType>::isInited() {
        return m_isInited.test(std::memory_order_acquire);
    }

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::init(std::shared_ptr<WindowType> window) {
       if(not m_isInited.test_and_set(std::memory_order_acquire)) {
           glfwInit();
           IMGUI_CHECKVERSION();
           ImGui::CreateContext();
           ImGuiIO &io = ImGui::GetIO();
           // Setup Platform/Renderer bindings
           const char* glsl_version = "#version 130";
           ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
           ImGui_ImplOpenGL3_Init(glsl_version);
           ImGui::StyleColorsDark();


           //ImGui_ImplGlfw_NewFrame();
       }
    }

    template <typename WindowType>
    void ImGuiOpenGL<WindowType>::draw(std::shared_ptr<WindowType> window) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.get());
        glfwPollEvents();

    }
}

#endif //AZATHOTH_IMGUIOPENGL_HPP
