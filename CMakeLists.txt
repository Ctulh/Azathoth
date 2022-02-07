cmake_minimum_required(VERSION 3.14)
project(Azathoth
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/glfw)
add_subdirectory(src)
add_subdirectory(app)
