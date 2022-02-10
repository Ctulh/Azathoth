#---------------------SET COMPONENT NAME---------------------------------------#
set(PROJECT_NAME Azathoth)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
set(LOGGER_LIB Azathoth.LoggerLib)
set(APPLICATION_LIB Azathoth.ApplicationLib)
set(WINDOW_LIB Azathoth.WindowLib)
set(APIFACTORY_LIB Azathoth.GraphicApiFactory)
set(DEBUG_LIB Azathoth.DebugTools.OpenGLToolsLib)
set(GUI_LIB Azathoth.GuiLib)
set(LAYERS_LIB Azathoth.LayersLib)
set(INPUT_LIB Azathoth.InputLib)
set(IMGUI_LIB ImGui)
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
target_link_libraries(${PROJECT_NAME} PRIVATE
                                                ${LOGGER_LIB}
                                                ${APPLICATION_LIB}
                                                ${WINDOW_LIB}
                                                ${DEBUG_LIB}
                                                ${GUI_LIB}
                                                ${LAYERS_LIB}
                                                ${INPUT_LIB}
                                                ${IMGUI_LIB})
#------------------------------------------------------------------------------#
#--------------------INCLUDE DIRS----------------------------------------------#
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#------------------------------------------------------------------------------#