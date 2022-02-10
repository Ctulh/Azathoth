set(LIB_NAME Azathoth.OpenGL.WindowLib)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )

#find_package(OpenGL REQUIRED)
set(LOGGER_LIB Azathoth.LoggerLib)
set(DEBUG_LIB Azathoth.OpenGL.DebugToolsLib)
set(RENDERER_LIB Azathoth.OpenGL.RendererLib)

set(HEADER ${PROJECT_SOURCE_DIR}/include/OpenGL/Window/WindowGLFW.hpp)

set(SOURCE WindowGLFW.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})


set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/glfw/include)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/DebugTools/OpenGLTools)
target_link_libraries(${LIB_NAME} PRIVATE  ${DEBUG_LIB} ${RENDERER_LIB})
