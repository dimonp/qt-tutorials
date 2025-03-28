cmake_minimum_required(VERSION 3.16)

project(yamlsettings-test LANGUAGES CXX)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Test Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yamlsettings-test main.cpp
    test_yamlsettings.h test_yamlsettings.cpp
)

add_test(NAME TestYamlSettings COMMAND yamlsettings-test)

target_link_libraries(yamlsettings-test PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(yamlsettings-test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(yamlsettings-test PRIVATE common-lib)
