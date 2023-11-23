cmake_minimum_required(VERSION 3.20)
project(Uloha9 C)

set(CMAKE_C_STANDARD 99)

add_executable(Uloha9 main.c)

target_link_libraries(Uloha9 libfreeglut.a opengl32.dll libglu32.a)