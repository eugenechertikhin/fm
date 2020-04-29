cmake_minimum_required(VERSION 3.2)
project(fm)

set(CMAKE_C_STANDARD 11)
set(SOURCES main.cpp Directory.cpp Config.cpp Workspace.cpp Workspace.h Operations.cpp Operations.h)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_subdirectory(Simpleini)

add_executable(fm ${SOURCES})

target_link_libraries(fm menu panel ncurses)