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

include_directories(../imgui/lib)
include_directories(../imgui/imgui)
include_directories(../imgui/GL)
include_directories(../imgui/GLFW)
include_directories(../imgui/lib)

FILE(GLOB R_FONTS "../imgui/fonts/Arial*.ttf")
set_property(
    SOURCE ${R_FONTS}
    PROPERTY MACOSX_PACKAGE_LOCATION "Resources/fonts"
   )

find_package(OpenGL REQUIRED)
set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} ${OPENGL_LIBRARIES})

find_library(FOUNDATION Foundation REQUIRED)

#######
file(GLOB SRC_PD_IMGUI
    "src/*.cpp"
    "src/views/*.cpp"
    "src/UiObjects/*.cpp"
#    "src/properties/*.cpp"
    "src/menus/*.cpp"
    )
include_directories(src)
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
target_link_libraries(pd_imgui ${EXTERNAL_LIBRARIES} ${FOUNDATION})

target_link_libraries(pd_imgui xpd_static)

#add_definitions(-DHAVE_UNISTD_H)

#file(GLOB UTF8
#    "utf8/*.h"
#    "utf8/*.c"
#    "utf8/internal/*.c"
#)

#set (CICM

#    CICMWrapper/ebox.c
#    CICMWrapper/eclass.c
#    CICMWrapper/ecommon.c
#    CICMWrapper/egraphics.c
#    CICMWrapper/eobj.c
#    CICMWrapper/epopup.c

#    )

#set (SDIFLIB
#    ../miniSDIF/src/mSDIFFile.cpp
#    ../miniSDIF/src/mSDIFFrame.cpp
#    ../miniSDIF/src/mSDIFMatrix.cpp
#    ../miniSDIF/src/mSDIFTypes.cpp
#    )

#set (SYNTH
#    ../PartialSynth/src/BasePartial.cpp
#    ../PartialSynth/src/SinePartial.cpp
#    ../PartialSynth/src/ResPartial.cpp
#    ../PartialSynth/src/SineSynth.cpp
#    ../PartialSynth/src/ResSynth.cpp
#    )

#set (SOURCES
#    sdif_lib.cpp
#    )

#set (SRC_SDIF

#    src/sdif/sdif_file.cpp
#    src/sdif/sdif_frame.cpp
#    src/sdif/sdif_matrix.cpp

#    src/sdif/sdif_data_types.cpp

#    src/sdif/sdif_1trc.cpp
#    src/sdif/sdif_1trc_merge.cpp
#    )

#set (SRC_SYNTH
#    src/synth/synth_sine.cpp
#    src/synth/synth_res.cpp
#    )

#set (SRC_LIST
#    src/list/list_do.cpp
#    )

#set (SRC_MLIST

#    src/mlist/mlist_obj.cpp
#    src/mlist/mlist_unpack.cpp

#    src/mlist/mlist_flip.cpp

#    src/mlist/mlist_data_type.cpp
#    )

#set (SRC_JSON
#    src/json/json_data_type.cpp
#    src/json/mstring_data_type.cpp

#    src/json/json_obj.cpp

#    src/json/json_dict.cpp

#    src/json/json_recorder.cpp
#    )

#set (SRC_IMG
#    src/img/image_obj.cpp

#    src/img/image_data_type.cpp
#    )

#set (SRC_MAT
#    src/matrix/matrix_obj.cpp

#    src/matrix/matrix_data_type.cpp
#    )

#set (SRC_CONV

#    src/conv/mlist_llll.cpp
#    src/conv/mlist_flat.cpp
#    src/conv/mlist_json.cpp
#    src/conv/mlist_image.cpp

#    src/conv/image_mlist.cpp
#    src/conv/image_matrix.cpp

#    src/conv/list_json.cpp

#    src/conv/json_mlist.cpp
#    src/conv/json_list.cpp

#    src/conv/conv_mlist.cpp
#    src/conv/conv_image.cpp
#    src/conv/conv_list.cpp
#    src/conv/conv_json.cpp
#    src/conv/conv_matrix.cpp

#    src/conv/matrix_image.cpp

#    )

#set (SRC_TL
#    src/tl/tl_bang.cpp
#    src/tl/tl_cue.cpp
#    src/tl/tl_transport.cpp

#    src/tl/tl_toggle.cpp
#    src/tl/tl_value.cpp
#    src/tl/tl_parameter.cpp
#    src/tl/tl_delay.cpp
#)

#set (HEADERS
#    ../miniSDIF/src/mSDIFFile.hpp
#    ../miniSDIF/src/mSDIFFrame.hpp
#    ../miniSDIF/src/mSDIFMatrix.hpp
#)

#file(GLOB LIB_SRC
#    "lib/ceammc_atomlist.cpp"
#    "lib/ceammc_atom.cpp"
#    "lib/ceammc_abstractdata.cpp"
#    "lib/ceammc_dataatom.cpp"
#    "lib/ceammc_data.cpp"
#    "lib/ceammc_datastorage.cpp"
#    "lib/ceammc_log.cpp"


#)

#find_package(Boost 1.47.0 REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories( ${CMAKE_BINARY_DIR} )

#include_directories(.)
#include_directories(./tl/)
#include_directories(./lib/)
#include_directories(./pd/)
#include_directories(./utf8/)
#include_directories(./CICMWrapper/)

#include_directories(../miniSDIF/src/)
#include_directories(../PartialSynth/src/)

#include_directories(../miniSDIF/src/mlist)
#include_directories(../miniSDIF/src/json)

#include_directories(../miniSDIF/src/img)
#include_directories(../miniSDIF/src/conv)

#add_library(sdif_lib SHARED
#    ${SOURCES}
#    ${UTF8}
#    ${SDIFLIB}
#    ${SYNTH}
#    ${SRC_SDIF}
#    ${SRC_SYNTH}
#    ${SRC_MLIST}
#    ${SRC_LIST}
#    ${SRC_JSON}
#    ${SRC_IMG}
#    ${SRC_MAT}
#    ${SRC_CONV}

#    #${LIB_SRC}
#    )

#target_link_libraries(sdif_lib "-undefined dynamic_lookup")
#SET_TARGET_PROPERTIES(sdif_lib PROPERTIES PREFIX "")
#set_target_properties(sdif_lib PROPERTIES SUFFIX ".pd_darwin")

#FIND_PACKAGE(JPEG REQUIRED)
#IF(JPEG_FOUND)
#  INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
#  TARGET_LINK_LIBRARIES(sdif_lib ${JPEG_LIBRARIES})
#ENDIF()

#add_subdirectory(tests)


########
#enable_testing()

#macro(add_unit_test target target_test)
#    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${target_test})
#    add_test(target ${CMAKE_BINARY_DIR}/tests/${target_test})
#endmacro(add_unit_test)

#add_unit_test (all_tests test_converters)

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


#install(TARGETS timeline LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../bin)


