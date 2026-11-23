cmake_minimum_required(VERSION 4.3)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake main.cpp
        Point.h
        Point.cpp
        Board.cpp
        Board.h
        Snake.cpp
        Snake.h
        Food.cpp
        Food.h
        FoodType.cpp
        FoodType.h
        game.cpp
        game.h)
