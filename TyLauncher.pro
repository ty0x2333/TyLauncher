#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T15:42:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = TyLauncher
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    widget/mainwindow.cpp \
    widget/aboutdialog.cpp \
    widget/appbuttondialog.cpp \
    widget/tabwidget.cpp \
    widget/appbuttonform.cpp \
    widget/appbutton.cpp \
    widget/appconfigdialog.cpp \
    utils/uiutils.cpp \
    utils/apputils.cpp \
    utils/shearplateutils.cpp \
    utils/stringutils.cpp \
    model/appinfo.cpp \
    model/option.cpp \
    dynamicdata.cpp

HEADERS  += widget/mainwindow.h \
    widget/aboutdialog.h \
    widget/appbuttondialog.h \
    widget/tabwidget.h \
    widget/appbuttonform.h \
    widget/appbutton.h \
    widget/appconfigdialog.h \
    utils/uiutils.h \
    utils/apputils.h \
    utils/shearplateutils.h \
    utils/stringutils.h \
    model/appinfo.h \
    model/option.h \
    dynamicdata.h \
    TyLog_Qt.h \
    datasettings.h \
    StaticSetting.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    appbuttondialog.ui \
    tabwidget.ui \
    appconfigdialog.ui \
    appbuttonform.ui

include(qxtglobalshortcut/qxtglobalshortcut.pri)

RESOURCES += \
    res.qrc

include(StaticSetting.h)
win32:RC_FILE += \
    TyLauncher.rc

TRANSLATIONS += language/zh_CN.ts

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
    QMAKE_MAC_SDK = macosx # work around QTBUG-41238
    # Copy the custom Info.plist to the app bundle
    QMAKE_INFO_PLIST = ./shared/Info.plist

    # Only Intel binaries are accepted so force this
    CONFIG += x86
    LIBS += -framework Carbon -framework Cocoa
    QT += macextras

    # Icon is mandatory for submission
    ICON = res/icon.icns
}

DISTFILES += \
    language/zh_CN.qm
