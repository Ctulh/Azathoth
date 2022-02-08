set(LIB_NAME Azathoth.LoggerLib)

find_package(spdlog PATHS ${PROJECT_SOURCE_DIR}/third_party/spdlog)


set(SOURCE SpdLogger.cpp
           SpdLoggerProxy.cpp)

set(HEADER ${PROJECT_SOURCE_DIR}/include/Logger/Logger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/ILogger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/SpdLogger.hpp
           ${PROJECT_SOURCE_DIR}/include/Logger/SpdLoggerProxy.hpp)

add_library(${LIB_NAME} ${SOURCE} ${HEADER})


target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE spdlog)