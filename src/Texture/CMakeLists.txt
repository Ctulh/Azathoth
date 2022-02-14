set(LIB_NAME Azathoth.TextureLib)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Texture/Texture.h)

set(SOURCE ${PROJECT_SOURCE_DIR}/src/Texture/Texture.cpp)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE CXX)

find_package(GLEW REQUIRED)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/stb
                                             ${PROJECT_SOURCE_DIR}/include/Texture)


target_link_libraries(${LIB_NAME} PRIVATE GL GLEW::GLEW stb)