cmake_minimum_required(VERSION 3.2)
project(Simpleini)

set(CMAKE_C_STANDARD 11)
set(SOURCES ConvertUTF.cpp ConvertUTF.h Simpleini.h)

add_library(Simpleini STATIC ${SOURCES})
