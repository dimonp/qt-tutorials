cmake_minimum_required(VERSION 3.16)

project(addressbook VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)

include_directories(
    "code",
    "resources",
    "build"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()

qt_wrap_ui(UI_SOURCES
    resources/adddialog.ui
    resources/addressbook.ui
)

message("UI_SOURCES ${UI_SOURCES}")

qt_add_executable(addressbook 
    code/main.cpp
    code/adddialog.cpp
    code/adddialog.h
    code/addressbook.cpp
    code/addressbook.h
    resources/adddialog.ui
    resources/addressbook.ui
)

target_link_libraries(addressbook PRIVATE 
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)