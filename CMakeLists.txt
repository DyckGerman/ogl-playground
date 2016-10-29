cmake_minimum_required(VERSION 3.0)
project(ogl-playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp shaders.h)
set(ELLIBRARIES "-lglfw3 -lGLEW -lGL -lX11 -lXrandr -lXi -lpthread -ldl -lXxf86vm -lXcursor -lXinerama")


add_executable(ogl-playground ${SOURCE_FILES})
target_link_libraries(ogl-playground ${ELLIBRARIES})
