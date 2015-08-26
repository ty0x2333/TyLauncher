INCLUDEPATH += $$PWD  
DEPENDPATH += $$PWD  
 
HEADERS += $$PWD/qxtglobal.h \  
           $$PWD/qxtglobalshortcut.h \  
           $$PWD/qxtglobalshortcut_p.h  
SOURCES += $$PWD/qxtglobalshortcut.cpp  
win32{  
    SOURCES += $$PWD/qxtglobalshortcut_win.cpp  
    LIBS += -luser32  
}
unix:!macx:SOURCES += $$PWD/qxtglobalshortcut_x11.cpp
macx {
    SOURCES += $$PWD/qxtglobalshortcut_mac.cpp
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
    QMAKE_MAC_SDK = macosx # work around QTBUG-41238

    # Only Intel binaries are accepted so force this
    CONFIG += x86
}
