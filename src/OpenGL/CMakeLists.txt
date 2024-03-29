add_subdirectory(DebugTools)
add_subdirectory(Gui)
add_subdirectory(Input)
add_subdirectory(Window)
add_subdirectory(GraphicApiFactory)
add_subdirectory(Renderer)

set(LIB_NAME Azathoth.OpenGL.Lib)

set(TOOLS_LIB Azathoth.OpenGL.DebugToolsLib)
set(FACTORY_LIB Azathoth.OpenGL.GraphicApiFactoryLib)
set(GUI_LIB Azathoth.OpenGL.GuiLib)
set(INPUT_LIB Azathoth.OpenGL.InputLib)
set(RENDERER_LIB Azathoth.OpenGL.RendererLib)
set(WINDOW_LIB Azathoth.OpenGL.WindowLib)
set(IMGUI_LIB ImGui)
set(GLAD_LIB glad)

set(HEADER AzathothOpenGL.hpp)

add_library(${LIB_NAME} ${HEADER})

target_link_libraries(${LIB_NAME} PRIVATE ${TOOLS_LIB}
        ${FACTORY_LIB}
        ${GUI_LIB}
        ${INPUT_LIB}
        ${RENDERER_LIB}
        ${WINDOW_LIB}
        ${IMGUI_LIB}
        ${GLAD_LIB}
        glad)

target_include_directories(${LIB_NAME} PUBLIC . ${PROJECT_SOURCE_DIR}/include/OpenGL)


