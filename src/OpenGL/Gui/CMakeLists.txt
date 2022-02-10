#---------------------SET COMPONENT NAME---------------------------------------#
set(LIB_NAME Azathoth.OpenGL.GuiLib)
list(APPEND ${LINK_LIST} ${LIB_NAME})

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
set(IMGUI_LIB ImGui)
set(LAYERS_LIB Azathoth.LayersLib)
set(LOGGER_LIB Azathoth.LoggerLib)
#------------------------------------------------------------------------------#
#---------------------FIND PACKAGES--------------------------------------------#
find_package(OpenGL REQUIRED)
#------------------------------------------------------------------------------#
#---------------------ADD SOURCE-----------------------------------------------#
set(SOURCE ImGuiLayerGLFW.cpp)
#------------------------------------------------------------------------------#
#---------------------ADD HEADER-----------------------------------------------#
set(HEADER
       ${PROJECT_SOURCE_DIR}/include/OpenGL/Gui/ImGuiLayerGLFW.hpp)
#------------------------------------------------------------------------------#
#------------------ADD LIBRARY-------------------------------------------------#
add_library(${LIB_NAME} ${HEADER} ${SOURCE})
#------------------------------------------------------------------------------#
#------------------SET COMPILE DEFINITIONS-------------------------------------#
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#------------------------------------------------------------------------------#
#---------------------INCLUDE DIRECTORIES--------------------------------------#
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/imgui
                                              ${PROJECT_SOURCE_DIR}/third_party/imgui/backends)
#------------------------------------------------------------------------------#
#---------------------LINK COMPONENTS------------------------------------------#
target_link_libraries(${LIB_NAME} PRIVATE ${IMGUI_LIB}
                                          ${LOGGER_LIB})
#------------------------------------------------------------------------------#