set(LIB_NAME Azathoth.RendererLib)

set(SOURCE Renderer.cpp)

set(LOGGER_LIB Azathoth.LoggerLib)
set(WINDOW_LIB Azathoth.WindowLib)


set(HEADER ${PROJECT_SOURCE_DIR}/include/Renderer/IRenderer.hpp
           ${PROJECT_SOURCE_DIR}/include/Renderer/Renderer.hpp)

add_library(${LIB_NAME} ${SOURCE} ${HEADER})


target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB} ${WINDOW_LIB})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)