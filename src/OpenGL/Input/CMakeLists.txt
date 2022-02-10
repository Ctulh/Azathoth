set(LIB_NAME Azathoth.OpenGL.InputLib)
list(APPEND ${LINK_LIST} ${LIB_NAME})

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
set(HEADER ${PROJECT_SOURCE_DIR}/include/OpenGL/Input/WindowInpuGLFW.hpp)

set(SOURCE WindowInpuGLFW.cpp)


set(LOGGER_LIB Azathoth.LoggerLib)


add_library(${LIB_NAME} ${HEADER} ${SOURCE})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                             ${PROJECT_SOURCE_DIR}/third_party/glfw/include)

target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB})