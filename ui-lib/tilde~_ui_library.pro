#-------------------------------------------------
#
# Project created by QtCreator 2017-06-24T23:05:14
#
#-------------------------------------------------

QT       -= core gui

TARGET = tilde~_ui

TEMPLATE = lib

unix:QMAKE_LFLAGS += -undefined dynamic_lookup

DEFINES += QT_DEPRECATED_WARNINGS \
    PD_INTERNAL

SOURCES += \
    #../qtpd_ceammc_lib/src/ceammc_atomlist.cpp \
    #../qtpd_ceammc_lib/src/ceammc_atom.cpp \
    ../qtpd_ceammc_lib/src/ceammc_log.cpp \
    ../qtpd_ceammc_lib/src/ceammc_object.cpp \
    ../qtpd_ceammc_lib/src/ceammc_property.cpp \
    ../qtpd_ceammc_lib/src/ceammc_format.cpp \
    ../qtpd_ceammc_lib/src/ceammc_message.cpp \
    src/ui_bang.cpp \
    src/ui_sliders.cpp \
    src/ui_matrix.cpp \
    src/ui_float.cpp \
    src/ui_msg.cpp \
    src/ui_script.cpp \
    src/ui_toggle.cpp \
    src/ui_array.cpp \
    tilde~_ui_library/tilde~_ui_library.cpp \
    src/ui_text.cpp \
    src/baseUIClass.cpp \
    src/ui_dsp.cpp

HEADERS +=\
    ../../pd-server/pure-data-src/src/m_pd.h \
    ../../pd-server/pure-data-src/src/m_imp.h \
    ../../pd-server/pure-data-src/ceammc/ext/src/lib/ceammc_atomlist.h \
    ../../pd-server/pure-data-src/ceammc/ext/src/lib/ceammc_atom.h \
    ../qtpd_ceammc_lib/src/ceammc_object.h \
    ../qtpd_ceammc_lib/src/ceammc_factory.h \
    ../qtpd_ceammc_lib/src/ceammc_format.h \
    ../qtpd_ceammc_lib/src/ceammc_log.h \
    ../qtpd_ceammc_lib/src/ceammc_property.h \
    src/ui_bang.h \
    src/ui_float.h \
    src/ui_msg.h \
    src/ui_toggle.h \
    src/ui_matrix.h \
    src/ui_script.h \
    src/ui_sliders.h \
    src/ui_array.h \
    src/ui_text.h \
    src/baseUIClass.h \
    tilde~_ui_library/tilde~_ui_library.h \
    src/ui_dsp.h

INCLUDEPATH += ../qtpd_ceammc_lib/src/ \
    ../../pd-server/pure-data-src/src/ \
    ../../pd-server/src/
    ../../pd-server/tilde~_ui_library/

unix {
    #target.path = $$PWD/bin #/usr/local/lib
    target.path = ~/Documents/tilde~/Libraries
    INSTALLS += target
}

win32 {
    #target.path = $$PWD/bin #/usr/local/lib
    target.path = ~/Documents/tilde~/Libraries
    INSTALLS += target
}

win32:{
    LIBS += -L$$OUT_PWD/../../pd-server/src/qt-creator-project/debug -lpd-server \ #-L~/Documents/tilde~/Libraries -lpd-server #
   # -L$$OUT_PWD/../qtpd_ceammc_lib/debug -lqtpd_ceammc_lib
}

QMAKE_EXTENSION_SHLIB = "pd_darwin"
CONFIG += plugin no_plugin_name_prefix


