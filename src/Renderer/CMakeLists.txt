set(LIB_NAME Azathoth.RendererLib)


set(HEADER ${PROJECT_SOURCE_DIR}/include/Renderer/IGraphicsContext.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/RendererAPI.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/RenderCommand.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/Renderer.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/IVertexBuffer.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/IIndexBuffer.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/IShader.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/VertexArray.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/BufferLayout.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/Renderer.hpp)

set(SOURCE Renderer.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

#target_link_libraries(${LIB_NAME} PRIVATE glm::glm)