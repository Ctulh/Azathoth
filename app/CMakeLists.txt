set(PROJECT_NAME Azathoth)

set(SOURCE main.cpp)

set(LOGGER_LIB Azathoth.LoggerLib)
set(RENDERER_LIB Azathoth.RendererLib)

add_executable(${PROJECT_NAME} ${SOURCE})


target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGGER_LIB} ${RENDERER_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)