cmake_minimum_required(VERSION 3.30)
project(adventure-test2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(adventure-test2 main.cpp)
