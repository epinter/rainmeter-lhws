cmake_minimum_required(VERSION 3.21)

project(
        "rainmeter_lhws"
        VERSION 0.2.0
        LANGUAGES CXX)
set(PROJECT_LICENSE "MPL-2.0")
set(PROJECT_FRIENDLY_NAME ${PROJECT_NAME})
set(PROJECT_LONG_NAME "rainmeter_lhws")
set(PROJECT_DESCRIPTION "LibreHardwareService plugin for Rainmeter")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(src)
