CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

file(GLOB source_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.h)

add_library(engine ${source_files})

target_link_libraries(engine PRIVATE glfw libglew_static glm GLTFSDK ${Threads})

target_include_directories(engine PUBLIC include)