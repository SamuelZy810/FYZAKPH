cmake_minimum_required(VERSION 3.20)
project(FreeGL C)

set(CMAKE_C_STANDARD 99)

add_executable(FreeGL main.c)

target_link_libraries(FreeGL libfreeglut.a opengl32.dll libglu32.a)