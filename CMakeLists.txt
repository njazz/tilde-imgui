cmake_minimum_required (VERSION 2.8)
#set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10")
set (CMAKE_CXX_STANDARD 11)

if (APPLE)
	set(CMAKE_MACOSX_RPATH FALSE)
endif()

project(pd_imgui)

set (MY_APP_VERSION "0.01")
set (MY_APP_NAME "pd-imgui")

set (MACOSX_BUNDLE true)
set (MACOSX_BUNDLE_BUNDLE_NAME ${MY_APP_NAME})
set (MACOSX_BUNDLE_INFO_STRING "${MY_APP_NAME} ${MY_APP_VERSION}")
set (MACOSX_BUNDLE_LONG_VERSION_STRING "${MY_APP_VERSION}")
set (MACOSX_BUNDLE_SHORT_VERSION_STRING "${MY_APP_VERSION}")
set (MACOSX_BUNDLE_BUNDLE_VERSION "${MY_APP_VERSION}")
set (MACOSX_BUNDLE_ICON_FILE "${PROJECT_SOURCE_DIR}/${MY_APP_NAME}.icns")

file (GLOB SRC_IMGUI
    "../imgui/lib/*.cpp"
    "../imgui/main/*.cpp"
    "../imgui/GL/*.c"
    "../imgui/imgui/*.c*"

    )

#todo : x-platform
set (SRC_IMGUI
    ${SRC_IMGUI}

    "../imgui/nfd/src/nfd_common.c"
    "../imgui/nfd/src/nfd_cocoa.m"
    )

include_directories(../imgui/lib)
include_directories(../imgui/imgui)
include_directories(../imgui/GL)
include_directories(../imgui/GLFW)
include_directories(../imgui/lib)
include_directories(../imgui/nfd/src)
include_directories(../imgui/nfd/src/include)

FILE(GLOB R_FONTS "../imgui/fonts/Arial*.ttf")
set_property(
    SOURCE ${R_FONTS}
    PROPERTY MACOSX_PACKAGE_LOCATION "Resources/fonts"
   )

find_package(OpenGL REQUIRED)
set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} ${OPENGL_LIBRARIES})

#todo: x-platform
find_library(FOUNDATION Foundation REQUIRED)
find_library(COCOA Cocoa REQUIRED)

#######
file(GLOB SRC_PD_IMGUI
    "src/*.cpp"
    "src/views/*.cpp"
    "src/UiObjects/*.cpp"
    "src/properties/*.cpp"
    "src/menus/*.cpp"
    "src/undo/*.cpp"
    "src/patch_controller/*.cpp"
    "src/data_models/*.cpp"
    "src/file_io/*.cpp"
    )
include_directories(src)
include_directories(src/patch_controller)

INCLUDE_DIRECTORIES(xpd/src)

INCLUDE_DIRECTORIES(xpd/distrib/variant/include)
INCLUDE_DIRECTORIES(xpd/pd)

#######
add_subdirectory(ui-lib)
#######
add_subdirectory(xpd)
#######
add_executable(pd_imgui ${SRC_IMGUI} ${SRC_PD_IMGUI} ${R_FONTS}

    )
set_target_properties(pd_imgui PROPERTIES DEPENDS xpd)

set_target_properties(
     pd_imgui
     PROPERTIES
     MACOSX_BUNDLE TRUE
     )
set_target_properties(pd_imgui
     PROPERTIES
     MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/res/Info.plist.in)


target_link_libraries(pd_imgui glfw)
target_link_libraries(pd_imgui ${EXTERNAL_LIBRARIES} ${FOUNDATION} ${COCOA})

target_link_libraries(pd_imgui xpd_static)

#####
#add_subdirectory(../imgui/tests)


########
#enable_testing()

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





