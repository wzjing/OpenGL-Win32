cmake_minimum_required(VERSION 3.13)
project(OpenGLFoo)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DDEBUG
        -D__STDC_FORMAT_MACROS
        -DGLEW_STATIC
        -DPROJECT_DIR=\"${CMAKE_SOURCE_DIR}\")

file(GLOB source_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h)

add_executable(OpenGLFoo ${source_files})

target_compile_options(OpenGLFoo PRIVATE -Wall)

# glfw
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "disable glfw examples")
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "disable glfw tests")
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "disable glfw docs")
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# glew
SET(glew-cmake_BUILD_SHARED OFF CACHE BOOL "disable glew shared library")
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

# glm
SET(GLM_TEST_ENABLE OFF CACHE BOOL "disable glm test")
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

# Microsoft glTF-SDK
SET(ENABLE_UNIT_TESTS OFF CACHE BOOL "disable glTF-SDK test")
SET(ENABLE_SAMPLES OFF CACHE BOOL "disable glTF-SDK samples")
add_subdirectory(lib/glTF-SDK EXCLUDE_FROM_ALL)

find_package(Threads REQUIRED)

target_link_libraries(OpenGLFoo PRIVATE glfw libglew_static glm GLTFSDK Threads)