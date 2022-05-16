cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME "rainmeter_lhws")
set(PROJECT_VERSION 0.2.0)
set(PROJECT_DESCRIPTION "LibreHardwareService plugin for Rainmeter")
set(PROJECT_HOMEPAGE_URL "https://github.com/epinter/rainmeter-lhws")
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project (${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(src)

if (PROJECT_IS_TOP_LEVEL)
    message("Configuring CMAKE_INSTALL_PREFIX to ${CMAKE_CURRENT_SOURCE_DIR}/install")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Installation directory" FORCE)
    message("CMAKE_INSTALL_PREFIX = ${CMAKE_CURRENT_SOURCE_DIR}/install")

    include(GNUInstallDirs)

    install(TARGETS ${MAINTARGET}
            EXPORT ${PROJECT_NAME}Targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
endif()