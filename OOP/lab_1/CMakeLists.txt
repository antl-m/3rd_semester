cmake_minimum_required(VERSION 3.17)
project(Lab_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Lab_1
        main.cpp
        Book.cpp    Book.h
        Graph.cpp   Graph.h Bool.cpp Bool.h)
