set(LIB_NAME Azathoth.InputLib)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Input/Input.h
           ${PROJECT_SOURCE_DIR}/include/Input/GlfwWindowInput.hpp)


set(LOGGER_LIB Azathoth.LoggerLib)

set(SOURCE GlfwWindowInput.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/third_party/glfw/include)

target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB})