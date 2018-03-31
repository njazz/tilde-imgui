set(SERVER_SRC 
    abstractserver.cpp
    abstractserverprocess.cpp
    arguments.cpp    
    audiodevice.cpp
    audiodevicemanager.cpp
    array.cpp
    canvas.cpp
    canvasobserver.cpp
    classinfo.cpp
    connection.cpp
    consoleobserver.cpp
    device.cpp
    libraryinfo.cpp
    logger.h
    logger.cpp
    mididevice.cpp
    mididevicemanager.cpp
    object.cpp
    objectlist.cpp
    objectproperties.cpp
    observer.cpp
    pd_arguments.cpp
    pd_floatarray.cpp
    pd_canvas.cpp
    pd_catcher.cpp
    pd_localprocess.cpp
    pd_localserver.cpp 
    pd_objectobserver.cpp
    pd_object.cpp
    pd_consoleobserver.cpp
    propertyobserver.cpp
    serverpath.cpp
    videodevice.cpp
    xlets.cpp
    pdLib.hpp pdServer.hpp 
#pdLib.cpp  pdServer.cpp
    )

if(WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include_directories(${PROJECT_SOURCE_DIR}/pd/pure-data/src)
include_directories(${PROJECT_SOURCE_DIR}/pd)
include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/distrib/variant/include)

add_library(xpd_static STATIC ${SERVER_SRC})
add_library(xpd_shared SHARED ${SERVER_SRC})
target_link_libraries(xpd_static pd_core_static cpd)
target_link_libraries(xpd_shared pd_core_static cpd)
