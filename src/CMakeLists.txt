if(MSVC)
  add_definitions("/D_CRT_SECURE_NO_WARNINGS /DNOMINMAX")
  set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
  add_definitions("-DGLM_FORCE_RADIANS")
  include_directories("${OPENGL_INCLUDE_DIR}")
endif()

set(SOURCES
  main.cpp
  Sandbox.hpp Sandbox.cpp
)

set(SOURCES ${SOURCES} "${CMAKE_BINARY_DIR}/ext/glad/src/glad.c")

add_executable(sandbox ${SOURCES})

target_link_libraries(sandbox glfw ${GLFW_LIBRARIES})

add_custom_target(run COMMAND sandbox DEPENDS sandbox WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
