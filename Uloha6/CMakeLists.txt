cmake_minimum_required(VERSION 3.20)
project(Skuska3d C)

set(CMAKE_C_STANDARD 99)

add_executable(Skuska3d main.c)

target_link_libraries(Skuska3d libfreeglut.a opengl32.dll libglu32.a)