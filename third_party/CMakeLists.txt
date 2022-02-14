add_subdirectory(glfw)
add_subdirectory(glad)

set(LIB_NAME ImGui)

set(IMGUI_PATH imgui)

set(HEADER ${IMGUI_PATH}/imgui.h
           ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
           ${IMGUI_PATH}/backends/imgui_impl_glfw.h
           ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.h)

set(SOURCE ${IMGUI_PATH}/imgui.cpp
           ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
           ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
           ${IMGUI_PATH}/imgui_draw.cpp
           ${IMGUI_PATH}/imgui_tables.cpp
           ${IMGUI_PATH}/imgui_widgets.cpp
           ${IMGUI_PATH}/imgui_demo.cpp
           )

add_library(${LIB_NAME} ${HEADER} ${SOURCE})
target_include_directories(${LIB_NAME} PUBLIC ${IMGUI_PATH}/ ${IMGUI_PATH}/backends glfw/include)
target_link_libraries(${LIB_NAME} PRIVATE glfw)

set(STB_LIB stb)

set(HEADER stb/stb_image.h)

set(SOURCE stb/deprecated/stb_image.c)

add_library(${STB_LIB} ${HEADER} ${SOURCE})
