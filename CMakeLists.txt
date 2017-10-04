cmake_minimum_required(VERSION 3.8)
project(ogl_playground)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        shaders.h)

SET(CMAKE_CXX_LINK_FLAGS "-framework OpenGL")

add_executable(ogl_playground ${SOURCE_FILES})
target_link_libraries(ogl_playground glfw glew )