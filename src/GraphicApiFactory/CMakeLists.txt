#---------------------SET COMPONENT NAME---------------------------------------#
set(LIB_NAME Azathoth.GraphicApiFactory)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
set(WINDOW_LIB Azathoth.WindowLib)
set(LOGGER_LIB Azathoth.LoggerLib)
#------------------------------------------------------------------------------#
#---------------------ADD SOURCE-----------------------------------------------#
set(SOURCE )
#------------------------------------------------------------------------------#
#---------------------ADD HEADER-----------------------------------------------#
set(HEADER ${PROJECT_SOURCE_DIR}/include/GraphicApiFactory/IGraphicApiFactory.hpp
        ${PROJECT_SOURCE_DIR}/include/GraphicApiFactory/FactoryGLFW.hpp)
#------------------------------------------------------------------------------#
#------------------ADD LIBRARY-------------------------------------------------#
add_library(${LIB_NAME} ${HEADER} ${SOURCE})
#------------------------------------------------------------------------------#
#------------------SET COMPILE DEFINITIONS-------------------------------------#
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#------------------------------------------------------------------------------#
#---------------------INCLUDE DIRECTORIES--------------------------------------#
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#------------------------------------------------------------------------------#
#---------------------LINK COMPONENTS------------------------------------------#
target_link_libraries(${LIB_NAME} PRIVATE ${WINDOW_LIB}
                                          ${LOGGER_LIB})
#------------------------------------------------------------------------------#