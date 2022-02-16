set(LIB_NAME Azathoth.OpenGL.RendererLib)

set(SOURCE GraphicsContextOpenGL.cpp
           IndexBufferOpenGL.cpp
           VertexBufferOpenGL.cpp
           ShaderOpenGL.cpp
           VertexArrayOpenGL.cpp
           RendererApiOpenGL.cpp
           )

set(HEADER
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/RendererApiOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/GraphicsContextOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/ShaderOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/VertexBufferOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/VertexArrayOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Renderer/IndexBufferOpenGL.hpp
        )

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party
                                              ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/third_party/glm/
                                              ${PROJECT_SOURCE_DIR}/third_party/glfw/include
                                              ${PROJECT_BINARY_DIR}/third_party/glad/include
                                              ${PROJECT_SOURCE_DIR}/include/OpenGL)

#target_link_libraries(${LIB_NAME} PRIVATE glad glm)