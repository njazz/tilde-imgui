set(PD_SOURCES
    pure-data/src/d_arithmetic.c
    pure-data/src/d_array.c
    pure-data/src/d_ctl.c
    pure-data/src/d_dac.c
    pure-data/src/d_delay.c
    pure-data/src/d_fft.c
    pure-data/src/d_fft_fftsg.c
    pure-data/src/d_filter.c
    pure-data/src/d_global.c
    pure-data/src/d_math.c
    pure-data/src/d_misc.c
    pure-data/src/d_osc.c
    pure-data/src/d_resample.c
    pure-data/src/d_soundfile.c
    pure-data/src/d_ugen.c
    pure-data/src/g_all_guis.c
    pure-data/src/g_all_guis.h
    pure-data/src/g_array.c
    pure-data/src/g_canvas.c
    pure-data/src/g_canvas.h
    pure-data/src/g_clone.c
    pure-data/src/g_editor.c
    pure-data/src/g_graph.c
    pure-data/src/g_guiconnect.c
    pure-data/src/g_io.c
    pure-data/src/g_mycanvas.c
    pure-data/src/g_readwrite.c
    pure-data/src/g_rtext.c
    pure-data/src/g_scalar.c
    pure-data/src/g_template.c
    pure-data/src/g_text.c
    pure-data/src/g_traversal.c
    pure-data/src/m_atom.c
    pure-data/src/m_binbuf.c
    pure-data/src/m_class.c
    mocks/m_conf.c
    pure-data/src/m_glob.c
    pure-data/src/m_imp.h
    pure-data/src/m_memory.c
    pure-data/src/m_obj.c
    pure-data/src/m_pd.c
    pure-data/src/m_pd.h
    pure-data/src/m_sched.c
    pure-data/src/s_audio.c
    pure-data/src/s_audio_paring.c
    pure-data/src/s_audio_dummy.c
    pure-data/src/s_file.c
    pure-data/src/s_inter.c
    pure-data/src/s_loader.c
    pure-data/src/s_main.c
    pure-data/src/s_midi.c
    pure-data/src/s_path.c
    pure-data/src/s_print.c
    pure-data/src/s_stuff.h
    pure-data/src/s_utf8.c
    pure-data/src/s_utf8.h
    pure-data/src/x_acoustics.c
    pure-data/src/x_arithmetic.c
    pure-data/src/x_array.c
    pure-data/src/x_connective.c
    pure-data/src/x_gui.c
    pure-data/src/x_interface.c
    pure-data/src/x_list.c
    pure-data/src/x_midi.c
    pure-data/src/x_misc.c
    pure-data/src/x_net.c
    pure-data/src/x_scalar.c
    pure-data/src/x_text.c
    pure-data/src/x_time.c
    pure-data/src/x_vexp.c
    pure-data/src/x_vexp.h
    pure-data/src/x_vexp_fun.c
    pure-data/src/x_vexp_if.c
)

set(PD_EXTRA_SOURCES
    pure-data/extra/bob~/bob~.c
    pure-data/extra/bonk~/bonk~.c
    pure-data/extra/choice/choice.c
    pure-data/extra/fiddle~/fiddle~.c
    pure-data/extra/loop~/loop~.c
    pure-data/extra/lrshift~/lrshift~.c
    pure-data/extra/pique/pique.c
    pure-data/extra/sigmund~/sigmund~.c
    pure-data/extra/stdout/stdout.c
)

source_group(pd FILES ${PD_SOURCES})
source_group(pdextra FILES ${PD_EXTRA_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/pd/pure-data/src)

set(CMAKE_THREAD_PREFER_PTHREAD ON)

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/distrib/thread/pthreadwin)
    list(APPEND PD_EXTRA_SOURCES ${PROJECT_SOURCE_DIR}/distrib/thread/src/thd.c)
endif()

find_package(Threads REQUIRED)
add_definitions(-DPD=1 -DPD_INTERNAL=1 -DTHREAD_LOCKING=0)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(NOT ${IS_BIG_ENDIAN})
    add_definitions(-DLITTLE_ENDIAN=0x0001 -DBYTE_ORDER=LITTLE_ENDIAN)
endif()

set(PD_LINK_LIBRARIES)

if(UNIX AND NOT APPLE)
    add_definitions(-D_GNU_SOURCE)
    list(APPEND PD_LINK_LIBRARIES m)
    list(APPEND PD_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    set(LINUX True)
endif()

if(WIN32)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
        message("Building for UWP")
        set(FIPS_UWP 1)
    else()
        set(FIPS_UWP 0)
    endif()

    if (FIPS_UWP)
        set(CMAKE_CXX_STANDARD_LIBRARIES "WindowsApp.lib")
        set(CMAKE_C_STANDARD_LIBRARIES "WindowsApp.lib")
    else()
        set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -lgdi32 -lole32 -lwinmm -luuid -lwsock32 -lws2_32")
        set(CMAKE_C_STANDARD_LIBRARIES ${CMAKE_CXX_STANDARD_LIBRARIES})
    endif()

    add_definitions(-DWINVER=0x0502 -D_WIN32_WINNT=0x0502)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "-mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")
    list(APPEND PLATFORM_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols -lpthread")
    set(CMAKE_EXE_LINKER_FLAGS "-shared-libgcc -lpthread")
endif()

# ALSA
if(WITH_ALSA_AUDIO)
    list(APPEND PD_SOURCES pure-data/src/s_audio_alsa.c pure-data/src/s_audio_alsamm.c)
    list(APPEND PD_LINK_LIBRARIES ${ALSA_LIBRARIES})
endif()

if(WITH_ALSA_MIDI)
    list(APPEND PD_SOURCES pure-data/src/s_midi_alsa.c)
    list(APPEND PD_LINK_LIBRARIES ${ALSA_LIBRARIES})
endif()

# JACK
if(WITH_JACK)
    list(APPEND PD_SOURCES pure-data/src/s_audio_jack.c)
    list(APPEND PD_LINK_LIBRARIES ${JACK_LIBRARIES})
endif()

if(WITH_PORTAUDIO)
    list(APPEND PD_SOURCES pure-data/src/s_audio_pa.c)
    list(APPEND PD_LINK_LIBRARIES ${PORTAUDIO_LIBRARIES})
    include_directories(PORTAUDIO_INCLUDE_DIRS)
    if(MINGW)
        # this is a link fix when portaudio was build with ASIO support.
        # and it requires C++ linking
        # we are making empty C++ file, so cmake automatically uses c++ linker
        set(_asio_link_fix ${CMAKE_CURRENT_BINARY_DIR}/asio_link_fix.cpp)
        if(NOT EXISTS ${_asio_link_fix})
            file(WRITE ${_asio_link_fix} "")
        endif()
        list(APPEND PD_SOURCES ${_asio_link_fix})
    endif()
endif()

if(WITH_MMIO)
    add_definitions(-DUSEAPI_MMIO)
    list(APPEND PD_SOURCES pure-data/src/s_audio_mmio.c)
endif()

#if(WITH_PORTMIDI)
#    include_directories(pure-data/portmidi/portmidi/pm_common)
#    include_directories(pure-data/portmidi/portmidi/porttime)
#    list(APPEND S_SRC pure-data/src/s_midi_pm.c)
#    list(APPEND PD_LINK_LIBRARIES portmidi-static)
#endif()

if(WITH_OSS)
    list(APPEND PD_SOURCES pure-data/src/s_audio_oss.c)
    list(APPEND PD_SOURCES pure-data/src/s_midi_oss.c)
    list(APPEND PD_LINK_LIBRARIES ${OSSLIB})
endif()

# Dummy
if(WITH_DUMMY_AUDIO)
    list(APPEND PD_SOURCES pure-data/src/s_audio_dummy.c)
endif()

if(WITH_DUMMY_MIDI)
    list(APPEND PD_SOURCES pure-data/src/s_midi_dummy.c)
endif()

include(FindLibDL)
if(LIBDL_FOUND)
    list(APPEND PD_LINK_LIBRARIES ${LIBDL_LIBRARIES})
endif()

add_library(pd_core_shared SHARED ${PD_SOURCES} ${PD_EXTRA_SOURCES})
add_library(pd_core_static STATIC ${PD_SOURCES} ${PD_EXTRA_SOURCES})
target_link_libraries(pd_core_shared ${PD_LINK_LIBRARIES})
target_link_libraries(pd_core_static ${PD_LINK_LIBRARIES})

if(UNIX)
    set_target_properties(pd_core_static PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

add_subdirectory(cpd)
