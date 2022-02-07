set(PROJECT_NAME Azathoth)

set(SOURCE main.cpp)

set(LOGGER_LIB Azathoth.LoggerLib)


add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGGER_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)