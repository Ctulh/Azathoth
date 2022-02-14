set(LIB_NAME Azathoth.OpenGL.ObjectLib)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Object/Object.hpp
           ${PROJECT_SOURCE_DIR}/include/OpenGL/Object/GameObjectOpenGL.hpp
        ${PROJECT_SOURCE_DIR}/include/OpenGL/Object/PipeElements.hpp)
set(SOURCE GameObject.cpp
        PipeElements.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/OpenGL
                                                ${PROJECT_SOURCE_DIR}/include)