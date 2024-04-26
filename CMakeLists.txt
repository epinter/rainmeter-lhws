cmake_minimum_required(VERSION 3.21)

project(
        "rainmeter_lhws"
        VERSION 0.5.0
        LANGUAGES CXX)
set(PROJECT_LICENSE "MPL-2.0")
set(PROJECT_FRIENDLY_NAME ${PROJECT_NAME})
set(PROJECT_LONG_NAME "rainmeter_lhws")
set(PROJECT_COPYRIGHT "Emerson Pinter")
set(PROJECT_DESCRIPTION "LibreHardwareService plugin for Rainmeter")

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/version.rc
        @ONLY)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(src)
