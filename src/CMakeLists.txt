# author: d.horn

# Modify lab_x to the lab number if you'd like, add any source files you create here as needed

cmake_minimum_required(VERSION 3.16)
project(lab3_qhuang258)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(lab_x
        src/Main.cpp
        src/TicTacToeGame.cpp
        src/TicTacToeGame.h
)
