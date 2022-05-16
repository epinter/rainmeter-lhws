cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    string(TOLOWER ${CMAKE_VS_PLATFORM_NAME} ARCHITECTURE)
else ()
    string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCHITECTURE)
endif ()
if (ARCHITECTURE STREQUAL "amd64" OR ARCHITECTURE STREQUAL "x86_64")
    set(ARCHITECTURE "x64")
elseif (ARCHITECTURE STREQUAL "win32")
    set(ARCHITECTURE "x86")
endif ()
message("architecture: ${ARCHITECTURE}")

if(ARCHITECTURE STREQUAL x86)
    set(RAINMETER_ARCH x32)
else()
    set(RAINMETER_ARCH x64)
endif()

set(MAINTARGET "LibreHardwareService")
set(MAINTARGET "${MAINTARGET}" PARENT_SCOPE)

message("TARGET=${MAINTARGET}")

set(SOURCE_FILES Plugin.cpp Measure.cpp API.cpp RtssAppStat.cpp)


if (BUILD_SHARED_LIBS)
    add_library(${MAINTARGET} SHARED ${SOURCE_FILES})
else ()
    add_library(${MAINTARGET} STATIC ${SOURCE_FILES})
endif ()

target_compile_features(${MAINTARGET} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    message("Compiler is MSVC")
    if (BUILD_SHARED_LIBS)
        target_compile_options(${MAINTARGET} PRIVATE /W4 /WX /EHs)
    else ()
        target_compile_options(${MAINTARGET} PRIVATE /W4 /WX /EHs "$<$<CONFIG:Release>:/MD>" "$<$<CONFIG:Debug>:/MDd>"
                "$<$<CONFIG:Release>:/O2>" "$<$<CONFIG:Debug>:/Od>" /fp:fast)
        target_compile_definitions(${MAINTARGET} PRIVATE _Boost_USE_STATIC_LIBS BOOST_ALL_NO_LIB)
        set_property(TARGET ${MAINTARGET} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif ()
else ()
    message("UNSUPPORTED COMPILER")
endif ()

set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_WARN_NEW_VERSIONS ON)

find_package(Boost 1.79.0 REQUIRED COMPONENTS locale)
find_package(lhwservice CONFIG REQUIRED)

target_include_directories(${MAINTARGET} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/external/include"
        "${CMAKE_SOURCE_DIR}/rainmeter-plugin-sdk/API"
        lhwservice
        ${Boost_INCLUDE_DIR})

target_link_libraries(${MAINTARGET} PRIVATE
        lhwservice
        ${Boost_LIBRARIES}
        "${CMAKE_SOURCE_DIR}/rainmeter-plugin-sdk/API/${RAINMETER_ARCH}/Rainmeter.lib")


set(CPACK_GENERATOR ZIP)
include(CPack)