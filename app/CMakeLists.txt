#---------------------SET COMPONENT NAME---------------------------------------#
set(PROJECT_NAME Azathoth)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
set(LOGGER_LIB Azathoth.LoggerLib)
set(RENDERER_LIB Azathoth.RendererLib)
set(WINDOW_LIB Azathoth.WindowLib)
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
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGGER_LIB} ${RENDERER_LIB} ${WINDOW_LIB})
#------------------------------------------------------------------------------#
#--------------------INCLUDE DIRS----------------------------------------------#
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#------------------------------------------------------------------------------#