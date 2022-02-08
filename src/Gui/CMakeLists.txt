#---------------------SET COMPONENT NAME---------------------------------------#
set(LIB_NAME Azathoth.Gui)

message(${PROJECT_NAME})
message ( "     SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )
message ( "     BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
#------------------------------------------------------------------------------#
#---------------------SET LOCAL NAME TO LINK COMPONENT-------------------------#
set(IMGUI_LIB ImGui)
set(LOGGER_LIB Azathoth.LoggerLib)
#------------------------------------------------------------------------------#
#---------------------FIND PACKAGES--------------------------------------------#
find_package(OpenGL REQUIRED)
#------------------------------------------------------------------------------#
#---------------------ADD SOURCE-----------------------------------------------#
set(SOURCE)
#------------------------------------------------------------------------------#
#---------------------ADD HEADER-----------------------------------------------#
set(HEADER ${PROJECT_SOURCE_DIR}/include/Gui/IGui.hpp
           ${PROJECT_SOURCE_DIR}/include/Gui/ImGuiOpenGL.hpp)
#------------------------------------------------------------------------------#
#------------------ADD LIBRARY-------------------------------------------------#
add_library(${LIB_NAME} ${HEADER} ${SOURCE})
#------------------------------------------------------------------------------#
#------------------SET COMPILE DEFINITIONS-------------------------------------#
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#------------------------------------------------------------------------------#
#---------------------INCLUDE DIRECTORIES--------------------------------------#
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/third_party/imgui/
                           ${PROJECT_SOURCE_DIR}/third_party/imgui/backends)
#------------------------------------------------------------------------------#
#---------------------LINK COMPONENTS------------------------------------------#
target_link_libraries(${LIB_NAME} PRIVATE ${IMGUI_LIB}
                                          ${LOGGER_LIB}
                                          GL)
#------------------------------------------------------------------------------#