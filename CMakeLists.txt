cmake_minimum_required(VERSION 4.3)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake main.cpp
        Point.cpp
        Point.h
        Board.cpp
        Board.h
        Snake.cpp
        Snake.h
        Food.cpp
        Food.h)
