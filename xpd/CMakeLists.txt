cmake_minimum_required(VERSION 2.8)
project(xpd)
enable_language(CXX C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(in_source_build.cmake)
include(version)
include(sound)
include(options) 
include(config)
include(cmake_uninstall)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -funroll-loops -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++11 -funroll-loops -fomit-frame-pointer")
#set(CMAKE_OSX_DEPLOYMENT_TARGET 10.6)
#set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
set(CMAKE_MACOSX_RPATH ON)

if(WIN32)
	add_definitions("/D_CRT_SECURE_NO_WARNINGS /wd4091 /wd4996")
endif()

add_subdirectory(distrib/rtaudio)

add_subdirectory(pd)
add_subdirectory(src)

enable_testing(true)
add_subdirectory(tests)

include(cmake/summary.cmake)
