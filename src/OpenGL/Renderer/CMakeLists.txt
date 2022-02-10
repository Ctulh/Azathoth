set(LIB_NAME Azathoth.OpenGL.RendererLib)

set(SOURCE GraphicsContextOpenGL.cpp
        Shader.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Renderer/IGraphicsContext.hpp
        ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/GraphicsContextOpenGL.hpp
        ${PROJECT_SOURCE_DIR}/include/Renderer/Shader.hpp
        ${PROJECT_SOURCE_DIR}/include/Renderer/IVertexBuffer.hpp
        ${PROJECT_SOURCE_DIR}/include/Renderer/IIndexBuffer.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/third_party/glfw/include
                                              ${PROJECT_BINARY_DIR}/third_paty/glad/include)

target_link_libraries(${LIB_NAME} PRIVATE glad)