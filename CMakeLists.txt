cmake_minimum_required(VERSION 3.31)
project(algorithmLab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithmLab1 main.cpp
        searchSource.cpp
        searchSource.h
        statistic.cpp
        statistic.h
        searchSourceTime.cpp
        searchSourceTime.h)
