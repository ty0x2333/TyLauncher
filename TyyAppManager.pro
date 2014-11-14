#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T15:42:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = TyyAppManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    appbutton.cpp \
    aboutdialog.cpp \
    appbuttondialog.cpp \
    dynamicdata.cpp

HEADERS  += mainwindow.h \
    appbutton.h \
    aboutdialog.h \
    StaticSetting.h \
    appbuttondialog.h \
    dynamicdata.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    appbuttondialog.ui

include(qxtglobalshortcut/qxtglobalshortcut.pri)

RESOURCES += \
    res.qrc

include(StaticSetting.h)
RC_FILE += \
    TyyAppManager.rc

TRANSLATIONS += TyyAppManager_zh_CN.ts
