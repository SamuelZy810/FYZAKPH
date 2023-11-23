cmake_minimum_required(VERSION 3.20)
project(CV_7 C)

set(CMAKE_C_STANDARD 99)

add_executable(CV_7 main.c)

target_link_libraries(CV_7 libfreeglut.a opengl32.dll libglu32.a)