set(LIB_NAME Azathoth.LoggerLib)
list(APPEND ${LINK_LIST} ${LIB_NAME})

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
find_package(spdlog PATHS ${PROJECT_SOURCE_DIR}/third_party/spdlog)


set(SOURCE SpdLogger.cpp
           SpdLoggerProxy.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Logger/Logger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/ILogger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/SpdLogger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/SpdLoggerProxy.hpp)

add_library(${LIB_NAME} SHARED ${SOURCE} ${HEADER})


target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE spdlog)