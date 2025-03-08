cmake_minimum_required(VERSION 3.12) 

project(QChatty VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(QChatty_INCLUDE_SOURCES
    header/logindialog.h
    header/mainwindow.h
    header/registerdialog.h
)
set(QChatty_SRC_SOURCES
    src/logindialog.cpp
    src/mainwindow.cpp
    src/main.cpp
    src/registerdialog.cpp 
)
# 这一行代码的作用是查找并收集项目中所有 .ui 文件，并将它们存储在一个变量 QChatty_UI_FILES 中。具体来说：
# file(GLOB ...)：这是 CMake 的一个命令，用于从文件系统中查找匹配特定模式的文件。
# QChatty_UI_FILES：这是目标变量，用于存储找到的文件路径。
# RELATIVE ${CMAKE_SOURCE_DIR}：表示返回的文件路径是相对于 ${CMAKE_SOURCE_DIR} 的相对路径。${CMAKE_SOURCE_DIR} 是 CMake 项目的根目录。
# "ui/*.ui"：这是文件匹配模式，表示查找 ui 目录下所有扩展名为 .ui 的文件。
file(GLOB QChatty_UI_FILES RELATIVE ${CMAKE_SOURCE_DIR} "ui/*.ui")

add_executable(QChatty WIN32
        ${QChatty_INCLUDE_SOURCES}
        ${QChatty_SRC_SOURCES} 
        ${QChatty_UI_FILES} 
        rc.qrc "header/globle.h" "src/globle.cpp")

target_link_libraries(QChatty PRIVATE Qt::Widgets)

