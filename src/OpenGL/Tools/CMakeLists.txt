set(LIB_NAME Azathoth.OpenGL.DebugToolsLib)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )


set(LOGGER_LIB Azathoth.LoggerLib)

set(SOURCE ${PROJECT_SOURCE_DIR}/src/OpenGL/Tools/OpenGLTools.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/OpenGL/Tools/OpenGLTools.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

