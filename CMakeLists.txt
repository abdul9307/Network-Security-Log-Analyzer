cmake_minimum_required(VERSION 3.16)

project(MySOCApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)  # Auto-generate ui_*.h files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(ProjectFinal
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logicanalyzer.cpp
    logicanalyzer.h


)

target_link_libraries(ProjectFinal Qt6::Widgets)
