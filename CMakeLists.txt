cmake_minimum_required (VERSION 2.8)
#set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10")
#if(NOT CMAKE_VERSION VERSION_LESS 3.1)
#    set(CMAKE_CXX_STANDARD 11)
#else()
##    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (APPLE)
	set(CMAKE_MACOSX_RPATH FALSE)
endif(APPLE)

project(tilde_imgui)

set (MY_APP_VERSION "0.01")
set (MY_APP_NAME "tilde~")

set (MACOSX_BUNDLE true)
set (MACOSX_BUNDLE_BUNDLE_NAME ${MY_APP_NAME})
set (MACOSX_BUNDLE_INFO_STRING "${MY_APP_NAME} ${MY_APP_VERSION}")
set (MACOSX_BUNDLE_LONG_VERSION_STRING "${MY_APP_VERSION}")
set (MACOSX_BUNDLE_SHORT_VERSION_STRING "${MY_APP_VERSION}")
set (MACOSX_BUNDLE_BUNDLE_VERSION "${MY_APP_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_SOURCE_DIR}/../imgui/lib)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/imgui)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/GL)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/GLFW)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/lib)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/nfd/src)
include_directories(${PROJECT_SOURCE_DIR}/../imgui/nfd/src/include)

include_directories(${PROJECT_SOURCE_DIR}/../imgui/addons/imguidock)


set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icons/tilde~.icns)
set_source_files_properties(${APP_ICON} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources/")

file (GLOB SRC_IMGUI
    "${PROJECT_SOURCE_DIR}/../imgui/lib/*.cpp"
    "${PROJECT_SOURCE_DIR}/../imgui/main/*.cpp"
    "${PROJECT_SOURCE_DIR}/../imgui/GL/*.c"
    "${PROJECT_SOURCE_DIR}/../imgui/imgui/*.c*"

    "${PROJECT_SOURCE_DIR}/../imgui/addons/imguidock/*.c*"
    )

set (SRC_IMGUI
    ${SRC_IMGUI}

    "${PROJECT_SOURCE_DIR}/../imgui/nfd/src/nfd_common.c"
)

if(APPLE)
    set (SRC_IMGUI
        ${SRC_IMGUI}
        "${PROJECT_SOURCE_DIR}/../imgui/nfd/src/nfd_cocoa.m")
else()
#    find_package(GTK2 2.6 COMPONENTS gtk)
    find_package(GTK3 3.0 COMPONENTS gtk)
    set (SRC_IMGUI
        ${SRC_IMGUI}
        "${PROJECT_SOURCE_DIR}/../imgui/nfd/src/nfd_gtk.c")
#    INCLUDE_DIRECTORIES(${GTK2_INCLUDE_DIRS})
#    LINK_DIRECTORIES(${GTK2_LIBRARY_DIRS})
    INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
endif(APPLE)

#FILE(GLOB R_FONTS "${PROJECT_SOURCE_DIR}fonts/SourceCodePro*.ttf")
#set_property(
#    SOURCE ${R_FONTS}
#    PROPERTY MACOSX_PACKAGE_LOCATION "Resources/fonts"
#   )

FILE(GLOB R_FONTS
#    ${R_FONTS}

    "${PROJECT_SOURCE_DIR}/../imgui/fonts/Arial*.ttf"
    "${PROJECT_SOURCE_DIR}/fonts/*.ttf"
    )
set_property(
    SOURCE ${R_FONTS}
    PROPERTY MACOSX_PACKAGE_LOCATION "Resources/fonts"
   )


find_package(OpenGL REQUIRED)
set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} ${OPENGL_LIBRARIES})

#todo: x-platform
if(APPLE)
find_library(FOUNDATION Foundation REQUIRED)
find_library(COCOA Cocoa REQUIRED)
endif(APPLE)

#######



#######
file(GLOB SRC_tilde_imgui
    "src/*.cpp"
    "src/Controllers/*.cpp"
    "src/Controllers/Patch/*.cpp"
    "src/Views/*.cpp"
    "src/UIObjects/*.cpp"
    "src/Properties/*.cpp"
    "src/Properties/*.h*"
    "src/Menus/*.cpp"
    "src/Undo/*.cpp"
    "src/DataModels/*.cpp"
    "src/FileIO/*.cpp"
    )
include_directories(src)

include_directories(src/Controllers)
include_directories(src/Controllers/Patch)
include_directories(src/DataModels)
include_directories(src/FileIO)
include_directories(src/Menus)
include_directories(src/Properties)
#include_directories(src/Properties/json)
include_directories(src/UIObjects)
include_directories(src/Undo)
include_directories(src/Views)

include_directories(distrib/json)

INCLUDE_DIRECTORIES(xpd/src)

INCLUDE_DIRECTORIES(xpd/distrib/variant/include)
INCLUDE_DIRECTORIES(xpd/pd)

#######
add_subdirectory(ui-lib)
#######
add_subdirectory(xpd)
#######
add_executable(tilde_imgui
    ${SRC_IMGUI} ${SRC_tilde_imgui}
    ${R_FONTS} ${APP_ICON}
    )
set_target_properties(tilde_imgui PROPERTIES DEPENDS xpd)

set_property(TARGET tilde_imgui PROPERTY CXX_STANDARD 11)

set_target_properties(
     tilde_imgui
     PROPERTIES
     MACOSX_BUNDLE TRUE
     )
set_target_properties(tilde_imgui
     PROPERTIES
     MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/res/Info.plist.in)

 set (tilde_imgui
     PROPERTIES
     MACOSX_BUNDLE_ICON_FILE tilde~.icns)

if (APPLE)
    target_link_libraries(tilde_imgui glfw)
    target_link_libraries(tilde_imgui ${EXTERNAL_LIBRARIES} ${FOUNDATION} ${COCOA})
else()
    # linux
   target_link_libraries(tilde_imgui glfw3 pthread dl GLU GL rt Xrandr Xxf86vm Xi Xinerama X11)
   TARGET_LINK_LIBRARIES(tilde_imgui ${GTK3_LIBRARIES})
endif(APPLE)

target_link_libraries(tilde_imgui xpd_static)

if (LCOV AND GCOV)
    target_link_libraries(tilde_imgui gcov )
endif()

#####
enable_testing(true)
add_subdirectory(tests)
add_subdirectory(${PROJECT_SOURCE_DIR}/../imgui/tests ${CMAKE_BINARY_DIR}/imgui_tests/)

########

#macro(add_unit_test target target_test)
#    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${target_test})
#    add_test(target ${CMAKE_BINARY_DIR}/tests/${target_test})
#endmacro(add_unit_test)

#add_unit_test (all_tests test_imgui)

#add_custom_target( all_tests ALL
#                   DEPENDS ${UNIT_TEST_TARGETS}
#)

#add_custom_command(TARGET all_tests
#                   COMMENT "Running tests..."
#                   POST_BUILD
#                   COMMAND ${CMAKE_CTEST_COMMAND}
#                   ARGS --output-on-failure -fprofile-arcs -ftest-coverage
#                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#                   )





