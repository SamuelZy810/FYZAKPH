cmake_minimum_required(VERSION 3.20)
project(Uloha3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Uloha3 main.c)

target_link_libraries(Uloha3 libfreeglut.a opengl32.dll libglu32.a)