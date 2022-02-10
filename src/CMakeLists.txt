add_subdirectory(Logger)
add_subdirectory(Application)
add_subdirectory(Layers)
add_subdirectory(Events)


if (BUILD_OPENGL_API)
    message("BUILDING OPENGL API")
    add_subdirectory(OpenGL)
endif()

