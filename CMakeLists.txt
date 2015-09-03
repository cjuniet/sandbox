cmake_minimum_required(VERSION 3.0)
project(Sandbox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenGL
find_package(OpenGL REQUIRED)
# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
add_subdirectory("${CMAKE_SOURCE_DIR}/ext/glfw")
include_directories("${CMAKE_SOURCE_DIR}/ext/glfw/include")
# GLAD
set(GLAD_NO_LOADER ON CACHE BOOL "")
add_subdirectory("${CMAKE_SOURCE_DIR}/ext/glad")
include_directories("${GLAD_INCLUDE_DIRS}")
# GLM
include_directories("${CMAKE_SOURCE_DIR}/ext/glm")

add_subdirectory(src)
