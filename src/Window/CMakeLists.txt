set(LIB_NAME Azathoth.WindowLib)

set(HEADER
        ${PROJECT_SOURCE_DIR}/include/Window/IWindow.hpp
        ${PROJECT_SOURCE_DIR}/include/Window/OpenGLWindow.hpp)

set(SOURCE)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})


target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third_party/glfw-3.3.6/include/)
target_link_libraries(${LIB_NAME} PRIVATE glfw)
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
