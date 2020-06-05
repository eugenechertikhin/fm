cmake_minimum_required(VERSION 3.16)
project(fm)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Simpleini)

add_executable(fm
        Config.cpp
        Directory.cpp
        main.cpp
        Workspace.cpp
        FilePanel.cpp
        WindowExit.cpp
        WindowView.cpp
        WindowEdit.cpp
        WindowError.cpp
        WindowHelp.cpp
        WindowCopy.cpp
        WindowMove.cpp
        WindowCreate.cpp
        WindowDelete.cpp)

target_link_libraries(fm panel ncurses)

