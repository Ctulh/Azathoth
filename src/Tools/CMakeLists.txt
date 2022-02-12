set(LIB_NAME Azathoth.ToolsLib)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Tools/File.hpp)

set(SHADERS_PATH ${PROJECT_SOURCE_DIR}/shaders)

configure_file(${PROJECT_SOURCE_DIR}/include/Tools/config.h.in ${PROJECT_SOURCE_DIR}/include/Tools/config.h)

set(SOURCE File.cpp)

add_library(${LIB_NAME} SHARED ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)