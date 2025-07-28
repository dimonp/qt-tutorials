cmake_minimum_required(VERSION 3.16)

project(addressbook-qml VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick)
qt_standard_project_setup()

qt_add_executable(addressbook-qml
    code/main.cpp
)

qt_add_qml_module(addressbook-qml
    URI addressbook
    VERSION 1.0
    QML_FILES
        view/Addressbook.qml
        view/Adddialog.qml
    SOURCES
        code/addressbook.cpp code/addressbook.h
)

target_link_libraries(addressbook-qml PRIVATE
    Qt6::Quick
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)
