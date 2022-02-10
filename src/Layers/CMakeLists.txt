set(LIB_NAME Azathoth.LayersLib)
list(APPEND ${LINK_LIST} ${LIB_NAME})

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )

set(HEADER ${PROJECT_SOURCE_DIR}/include/Layers/Layer.hpp
           ${PROJECT_SOURCE_DIR}/include/Layers/LayerStack.hpp)

set(LOGGER_LIB Azathoth.LoggerLib)

set(SOURCE Layer.cpp
           LayerStack.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE ${LOGGER_LIB})