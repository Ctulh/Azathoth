set(LIB_NAME Azathoth.ApplicationLib)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )

set(LOGGER_LIB Azathoth.LoggerLib)
set(LAYERS_LIB Azathoth.LayersLib)
#set(WINDOW_LIB Azathoth.WindowLib)

set(SOURCE Application.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Application/IApplication.hpp
           ${PROJECT_SOURCE_DIR}/include/Application/Application.hpp)

add_library(${LIB_NAME} ${SOURCE} ${HEADER})


target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/third_party/glfw/include
                                              ${PROJECT_BINARY_DIR}/third_party/glad/include)
#target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB} ${LAYERS_LIB})
