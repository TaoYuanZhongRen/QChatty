#设置CMake的最小版本号，如果当前版本小于指定的版本号，则报错。
cmake_minimum_required(VERSION 3.12) 
#设置项目名
project(QChatty VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 这样在 Linux/macOS 上可以默认 Debug，而在 Windows 下不会冲突。
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# 定义用户可配置的选项
#option(ENABLE_DEBUG "Enable debug output" ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

message("Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Top level source directory: ${CMAKE_SOURCE_DIR}")
message("Current binary directory: ${CMAKE_BINARY_DIR}")


# 定义变量Project_MOC_HDRS，其值为所列的文件列表，包含所有含有Q_OBJECT的头文件
set(QChatty_MOC_HEADERS
    header/logindialog.h
    header/mainwindow.h
    header/registerdialog.h
        header/httpmgr.h
)
set(QChatty_HEADER_SOURCES
    header/globle.h  
    header/singleton.h    
)
set(QChatty_SRC_SOURCES
    src/logindialog.cpp
    src/mainwindow.cpp
    src/main.cpp
    src/registerdialog.cpp 
    src/singleton.cpp
    src/globle.cpp
    src/httpmgr.cpp
)
# 这一行代码的作用是查找并收集项目中所有 .ui 文件，并将它们存储在一个变量 QChatty_UI_FILES 中。具体来说：
# file(GLOB ...)：这是 CMake 的一个命令，用于从文件系统中查找匹配特定模式的文件。
# QChatty_UI_FILES：这是目标变量，用于存储找到的文件路径。
# RELATIVE ${CMAKE_SOURCE_DIR}：表示返回的文件路径是相对于 ${CMAKE_SOURCE_DIR} 的相对路径。${CMAKE_SOURCE_DIR} 是 CMake 项目的根目录。
# "ui/*.ui"：这是文件匹配模式，表示查找 ui 目录下所有扩展名为 .ui 的文件。
#file(GLOB QChatty_UI_FILES RELATIVE ${CMAKE_SOURCE_DIR} "ui/*.ui")

# 定义变量Project_UIS，其值为所列的文件列表，包含程序所有的UI文件
set(QChatty_UI_FILES
    ui/logindialog.ui
    ui/registerdialog.ui
    ui/mainwindow.ui
)
# qt_wrap_ui通过Qt的uic.exe生成UI文件对应的ui_xxxx.h文件
#     并将生成的ui_xxxx.h文件列表存储于变量QChatty_UI_FILES_H中
qt5_wrap_ui(QChatty_UI_FILES_H ${QChatty_UI_FILES})

# qt_wrap_cpp通过Qt的moc.exe将包含Q_OBJECT的头文件生成对应的moc_xxx.cxx文件，
# 并将生成的moc_xxx.cxx文件列表存储在变量Project_MOC_SRCS里
qt5_wrap_cpp(QChatty_MOC_SRCS ${QChatty_MOC_HEADERS})

SOURCE_GROUP("Source Files" FILES ${QChatty_SRC_SOURCES})
SOURCE_GROUP("Header Files" FILES ${QChatty_HEADER_SOURCES} ${QChatty_MOC_HEADERS} )
SOURCE_GROUP("UI" FILES ${QChatty_UI_FILES_H} ${QChatty_UI_FILES} )
SOURCE_GROUP("MOC" FILES ${QChatty_MOC_SRCS})

include_directories(${Project_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )
include_directories(./header)
include_directories(./build)

# 根据程序的cpp文件、头文件以及生成的ui_xxx.h、moc_xxx.cxx、qrc_xxx.cxx
# 等生成可执行文件，并链接Qt的动态库（Qt的动态库都定义在QT_LIBRARIES变量里了）
add_executable(QChatty
        ${QChatty_HEADER_SOURCES}
        ${QChatty_SRC_SOURCES} 
        ${QChatty_MOC_HEADERS}
        ${QChatty_UI_FILES_H}
        ${QChatty_MOC_SRCS})

target_link_libraries(QChatty PRIVATE Qt::Widgets)
target_link_libraries(QChatty PRIVATE Qt::Network)
