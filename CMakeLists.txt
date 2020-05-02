cmake_minimum_required(VERSION 3.16)
project(fm)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Simpleini)

add_executable(fm
        Config.cpp
        Config.h
        Directory.cpp
        Directory.h
        main.cpp
        Operations.cpp
        Operations.h
        version.h
        Workspace.cpp
        Workspace.h)

target_link_libraries(fm panel ncurses)
