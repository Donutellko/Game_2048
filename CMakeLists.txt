cmake_minimum_required(VERSION 3.8)
project(Game_2048)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Model.cpp Model.h Viewer.cpp Viewer.h)
add_executable(Game_2048 ${SOURCE_FILES})