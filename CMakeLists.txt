cmake_minimum_required(VERSION 3.2)
project(fm)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(fm main.cpp Directory.cpp Config.cpp Workspace.cpp Workspace.h Operations.cpp Operations.h)

target_link_libraries(fm menu panel ncurses)