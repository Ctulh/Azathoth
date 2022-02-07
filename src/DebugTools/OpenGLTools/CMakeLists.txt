set(LIB_NAME Azathoth.DebugTools.OpenGLToolsLib)

set(LOGGER_LIB Azathoth.LoggerLib)

set(SOURCE ErrorCallback.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/DebugTools/OpenGLTools/ErrorCallback.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

