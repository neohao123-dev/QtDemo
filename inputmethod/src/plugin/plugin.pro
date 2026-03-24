include(../common.pri)
QT          += gui-private widgets

TEMPLATE    = lib
TARGET      = cqdlcInputContextPlugin

DEST_DIR       = $${DEST_INPUTCONTEXTS}
REPORTS_DIR    = $${DEST_DIR}

macx{
    CONFIG  += app_bundle
}

unix:{
    DESTDIR = $$DEST_DIR
linux{
    #Link share lib to ../lib rpath
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../lib
    QMAKE_LFLAGS_RPATH += #. .. ./libs
}
    target.path = $${DEST_DIR}
    INSTALLS = target
}

win32 {
    EXTRA_DIR ~= s,/,\\,g
    DEST_DIR ~= s,/,\\,g
    REPORTS_DIR ~= s,/,\\,g

    DESTDIR = $$DEST_DIR
}

LIBS += -L$${DEST_LIBS}
CONFIG(debug, debug|release) {
        LIBS += -lgooglepinyin
} else {
        LIBS += -lgooglepinyin
}


HEADERS     += \
            cqdlcplatforminputcontext.h \
            cqdlcplatforminputcontextplugin.h \
            handinputform.h \
            paintarea.h \
            keyboardform.h

SOURCES     += \
            cqdlcplatforminputcontext.cpp \
            cqdlcplatforminputcontextplugin.cpp \
            handinputform.cpp \
            paintarea.cpp \
            keyboardform.cpp

RESOURCES   += \
            res.qrc

FORMS += \
    handinputform.ui

