cmake_minimum_required(VERSION 3.13)
project(OpenGL-Win32)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL-Win32 src/main.cpp)

target_compile_options(OpenGL-Win32 PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(OpenGL-Win32 PRIVATE glfw)

# glew
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(OpenGL-Win32 PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(OpenGL-Win32 PRIVATE glm)