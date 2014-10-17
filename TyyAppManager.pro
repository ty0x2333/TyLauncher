#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T15:42:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TyyAppManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    appbutton.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    appbutton.h \
    aboutdialog.h \
    StaticSetting.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

include(qxtglobalshortcut/qxtglobalshortcut.pri)

RESOURCES += \
    res.qrc

include(StaticSetting.h)
RC_FILE += \
    TyyAppManager.rc
