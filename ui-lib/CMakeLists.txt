cmake_minimum_required (VERSION 2.8)

set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

set (CMAKE_PREFIX_PATH ~/Qt/5.8/clang_64)
set (CMAKE_CXX_STANDARD 11)
# set (QMAKE_MACOSX_DEPLOYMENT_TARGET 10.10)

if (APPLE)
	set(CMAKE_MACOSX_RPATH FALSE)
endif()

#fixes warning for app name
cmake_policy(SET CMP0037 OLD)

project(tilde~_ui_library)

set(CEAMMC_LIB_SOURCES

    ceammc_lib/ceammc_abstractdata.cpp
    ceammc_lib/ceammc_atom.cpp
    ceammc_lib/ceammc_atomlist.cpp
    ceammc_lib/ceammc_data.cpp
    ceammc_lib/ceammc_dataatom.cpp
    ceammc_lib/ceammc_dataatomlist.cpp
    ceammc_lib/ceammc_datastorage.cpp
    ceammc_lib/ceammc_factory.h
    ceammc_lib/ceammc_format.cpp
    ceammc_lib/ceammc_log.cpp
    ceammc_lib/ceammc_message.cpp
    ceammc_lib/ceammc_object.cpp
    ceammc_lib/ceammc_property.cpp

)

set (SOURCES
    src/baseUIClass.cpp

    src/ui_bang.cpp
    src/ui_sliders.cpp
    src/ui_matrix.cpp
    src/ui_float.cpp
    src/ui_msg.cpp
    src/ui_script.cpp
    src/ui_toggle.cpp
    src/ui_array.cpp
    src/ui_text.cpp
    src/ui_dsp.cpp

    tilde~_ui_library/tilde~_ui_library.cpp
)

set (HEADERS
    ceammc_lib/ceammc_object.h 
    ceammc_lib/ceammc_message.h 
    ceammc_lib/ceammc_format.h 
    ceammc_lib/ceammc_log.h 
    ceammc_lib/ceammc_property.h 

    src/ui_bang.h
    src/ui_float.h 
    src/ui_msg.h 
    src/ui_toggle.h 
    src/ui_matrix.h 
    src/ui_script.h 
    src/ui_sliders.h 
    src/ui_array.h 
    src/ui_text.h 
    src/baseUIClass.h 
    tilde~_ui_library/tilde~_ui_library.h 
    src/ui_dsp.h
)

find_package(Boost 1.47.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories( ${CMAKE_BINARY_DIR} )

include_directories(.)
include_directories(./src/)
include_directories(./ceammc_lib/)
include_directories(../../pd-server/pure-data-src/src/)

add_library(tilde~_ui SHARED ${CEAMMC_LIB_SOURCES} ${SOURCES} )
target_link_libraries(tilde~_ui "-undefined dynamic_lookup")
SET_TARGET_PROPERTIES(tilde~_ui PROPERTIES PREFIX "")
set_target_properties(tilde~_ui PROPERTIES SUFFIX ".pd_darwin")

#install(TARGETS tilde~_ui LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../bin)


