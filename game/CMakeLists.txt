CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

add_executable(game application.cpp)

target_link_libraries(game PRIVATE engine glfw libglew_static glm GLTFSDK ${Threads})

target_compile_options(game PRIVATE -Wall)