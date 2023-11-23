cmake_minimum_required(VERSION 3.20)
project(Uloha5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Uloha5 main.c)

target_link_libraries(Uloha5 libfreeglut.a opengl32.dll libglu32.a)