#---------------------SET COMPONENT NAME---------------------------------------#
set(PROJECT_NAME Azathoth)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
if(BUILD_OPENGL_API)
    set(GRAPHIC_API Azathoth.OpenGL.Lib)
endif()

set(APPLICATION_LIB Azathoth.ApplicationLib)
set(EVENTS_LIB Azathoth.EventsLib)
set(LAYERS_LIB Azathoth.LayersLib)
set(LOGGER_LIB Azathoth.LoggerLib)
set(RENDERER_LIB Azathoth.RendererLib)

#------------------------------------------------------------------------------#
#-----------------------INCLUDE HEADER-----------------------------------------#
#------------------------------------------------------------------------------#
#---------------------ADD SOURCE-----------------------------------------------#
set(SOURCE main.cpp)
#------------------------------------------------------------------------------#
#------------------ADD EXECUTABLE----------------------------------------------#
add_executable(${PROJECT_NAME} ${SOURCE})
#------------------------------------------------------------------------------#
#---------------------LINK COMPONENTS------------------------------------------#
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHIC_API}
                                              ${APPLICATION_LIB}
        ${EVENTS_LIB}
        ${LAYERS_LIB}
        ${LOGGER_LIB}
        ${RENDERER_LIB}
        )

#------------------------------------------------------------------------------#
#--------------------INCLUDE DIRS----------------------------------------------#
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#------------------------------------------------------------------------------#