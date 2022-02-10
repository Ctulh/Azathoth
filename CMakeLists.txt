#---------------------SET CMAKE VERSION----------------------------------------#
cmake_minimum_required(VERSION 3.14)
#------------------------------------------------------------------------------#
#---------------------CONFIGURE PROJECT----------------------------------------#
project(Azathoth
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

option(BUILD_OPENGL_API "Build openGL API" ON)
#------------------------------------------------------------------------------#
#---------------------ADD SUBDIRECTORIES---------------------------------------#
add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(app)
#------------------------------------------------------------------------------#