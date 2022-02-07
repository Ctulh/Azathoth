set(LIB_NAME Azathoth.WindowLib)

#find_package(OpenGL REQUIRED)
set(LOGGER_LIB Azathoth.LoggerLib)
set(DEBUG_LIB Azathoth.DebugTools.OpenGLToolsLib)

set(HEADER
        ${PROJECT_SOURCE_DIR}/include/Window/IWindow.hpp
        ${PROJECT_SOURCE_DIR}/include/Window/OpenGLWindow.hpp)

set(SOURCE OpenGLWindow.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})


set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/glfw-3.3.6/include/)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/DebugTools/OpenGLTools)
target_link_libraries(${LIB_NAME} PRIVATE glfw ${LOGGER_LIB} ${DEBUG_LIB})
