cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

if(TARGET_ARCHITECTURE STREQUAL x86)
    set(RAINMETER_ARCH x32)
else()
    set(RAINMETER_ARCH x64)
endif()

set(MAINTARGET "LibreHardwareService")
set(MAINTARGET "${MAINTARGET}" PARENT_SCOPE)

message("TARGET=${MAINTARGET}")

set(SOURCE_FILES Plugin.cpp Measure.cpp API.cpp RtssAppStat.cpp)

add_library(${MAINTARGET} SHARED ${SOURCE_FILES})

target_compile_features(${MAINTARGET} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set(Boost_NO_WARN_NEW_VERSIONS 1)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED  ON)
find_package(Boost REQUIRED COMPONENTS locale)
if(Boost_FOUND)
    target_link_libraries(${MAINTARGET} PRIVATE ${Boost_LIBRARIES})
    target_include_directories(${MAINTARGET} PRIVATE ${Boost_INCLUDE_DIRS})
endif()

find_package(lhwservice CONFIG REQUIRED NO_DEFAULT_PATH
        PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/../extern/lhwservice/build/install
        ${CMAKE_CURRENT_SOURCE_DIR}/../extern/lhwservice/out/install
        ${CMAKE_CURRENT_SOURCE_DIR}/../extern/lhwservice/install
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lhwservice/build/install
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lhwservice/out/install
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lhwservice/install
)
if(lhwservice_FOUND)
	target_include_directories(${MAINTARGET} PRIVATE lhwservice)
	target_link_libraries(${MAINTARGET} PRIVATE lhwservice)
endif()

target_include_directories(${MAINTARGET} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/extern/rtss/include"
        "${CMAKE_SOURCE_DIR}/extern/rainmeter-plugin-sdk/API")

target_link_libraries(${MAINTARGET} PRIVATE
        "${CMAKE_SOURCE_DIR}/extern/rainmeter-plugin-sdk/API/${RAINMETER_ARCH}/Rainmeter.lib")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
    target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
endif()

install(TARGETS ${MAINTARGET}
        RUNTIME DESTINATION ".")

set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_NAME ${PROJECT_LONG_NAME})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CMAKE_PROJECT_VERSION}-${TARGET_ARCHITECTURE}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
include(CPack)
