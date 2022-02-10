set(LIB_NAME Azathoth.RendererLib)

set(SOURCE GraphicsContextOpenGL.cpp
           VertexBuffer.cpp
           IndexBuffer.cpp
           Shader.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Renderer/IGraphicsContext.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/GraphicsContextOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/Shader.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/VertexBuffer.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/IndexBuffer.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/third_party/glfw/include
                                              ${PROJECT_BINARY_DIR}/third_paty/glad/include)

target_link_libraries(${LIB_NAME} PRIVATE glad)