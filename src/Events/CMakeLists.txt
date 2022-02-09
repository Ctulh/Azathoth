set(LIB_NAME Azathoth.EventsLib)

set(SOURCE)
set(HEADER ${PROJECT_SOURCE_DIR}/include/Events/Event.hpp
           ${PROJECT_SOURCE_DIR}/include/Events/KeyEvent.hpp
           ${PROJECT_SOURCE_DIR}/include/Events/MouseEvent.hpp
           ${PROJECT_SOURCE_DIR}/include/Events/ApplicationEvent.hpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)