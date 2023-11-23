cmake_minimum_required(VERSION 3.20)
project(Uloha_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Uloha_4 main.c)

target_link_libraries(Uloha_4 libfreeglut.a opengl32.dll libglu32.a)