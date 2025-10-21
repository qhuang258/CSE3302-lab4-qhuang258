# author: d.horn
cmake_minimum_required(VERSION 3.16)
project(lab3_qhuang258)

# 启用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab3-qhuang258
        src/Main.cpp
        src/TicTacToeGame.cpp
        src/TicTacToeGame.h
)
