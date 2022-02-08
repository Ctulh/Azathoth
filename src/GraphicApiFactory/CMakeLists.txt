set(LIB_NAME Azathoth.GraphicApiFactory)

set(WINDOW_LIB Azathoth.WindowLib)



set(SOURCE )

set(HEADER ${PROJECT_SOURCE_DIR}/include/GraphicApiFactory/IGraphicApiFactory.hpp
        ${PROJECT_SOURCE_DIR}/include/GraphicApiFactory/OpenGLFactory.hpp)


add_library(${LIB_NAME} ${HEADER} ${SOURCE})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE ${WINDOW_LIB})