set(LIB_NAME Azathoth.ApplicationLib)


set(LOGGER_LIB Azathoth.LoggerLib)
set(LAYERS_LIB Azathoth.LayersLib)
#set(WINDOW_LIB Azathoth.WindowLib)

#set(SOURCE Renderer.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Application/IApplication.hpp
           ${PROJECT_SOURCE_DIR}/include/Application/Application.hpp)

add_library(${LIB_NAME} ${SOURCE} ${HEADER})


target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB} ${LAYERS_LIB})
