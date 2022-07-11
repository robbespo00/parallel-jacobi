cmake_minimum_required(VERSION 3.22)
project(SPMProject)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O3)

add_executable(SPMProject main.cpp utility.cpp utility.h jacobi_sequential.cpp jacobi_sequential.h jacobi_threads.cpp jacobi_threads.h utimer.cpp jacobi_ff.cpp jacobi_ff.h)
