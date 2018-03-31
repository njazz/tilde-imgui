include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
set(CMP_SOURCES
    cpd.h  cpd.cpp 
    cpd_atom.h cpd_atom.cpp 
    cpd_array.h cpd_array.cpp 
    cpd_array_element.h cpd_array_element.cpp
    cpd_canvas.h cpd_canvas.cpp
    cpd_catcher.h cpd_catcher.cpp
    cpd_class.h cpd_class.cpp
    cpd_connection.h cpd_connection.cpp
    cpd_dsp.h cpd_dsp.cpp
    cpd_globals.h cpd_globals.cpp
    cpd_list.h cpd_list.cpp 
    cpd_method.h cpd_method.cpp
    cpd_env.h cpd_env.cpp 
    cpd_object.h cpd_object.cpp
    cpd_patch.h cpd_patch.cpp
    cpd_types.h cpd_types.cpp 
    pr_log.cpp cpd_loader.h cpd_loader.cpp
    cpd_receiver.cpp
    cpd_system_lists.cpp
    )

if(WIN32)
    add_definitions(-DCPD_INTERNAL)
endif()

if(WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_library(cpd STATIC ${CMP_SOURCES})

if(UNIX)
    set_target_properties(cpd PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

target_link_libraries(cpd pd_core_static)
