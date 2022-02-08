set(LIB_NAME Azathoth.Gui)

set(IMGUI_LIB ImGui)
find_package(OpenGL REQUIRED)

set(SOURCE)
set(HEADER ${PROJECT_SOURCE_DIR}/include/Gui/IGui.hpp
        ${PROJECT_SOURCE_DIR}/include/Gui/ImGuiOpenGL.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} PRIVATE ${IMGUI_LIB} GL)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/imgui/
                                              ${PROJECT_SOURCE_DIR}/third_party/imgui/backends)