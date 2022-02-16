set(LIB_NAME Azathoth.OpenGL.CameraLib)

set(HEADER
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Camera/CameraOpenGL.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Camera/CameraManipulatorOpenGL.hpp)

set(SOURCE
        CameraOpenGL.cpp
        CameraManipulatorOpenGL.cpp)

set(LAYER_LIB Azathoth.LayersLib)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                              ${PROJECT_SOURCE_DIR}/include/OpenGL/)

target_link_libraries(${LIB_NAME} PRIVATE ${LAYER_LIB})