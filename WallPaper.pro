#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T09:03:22
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wallpaper
TEMPLATE = app

CODECFORTR = UTF-8
CODECFORSRC = UTF-8

win32{
LIBS += -luser32
}

SOURCES += main.cpp\
        titlebar.cpp \
    mainwindow.cpp \
    download.cpp \
    webview.cpp \
    statubar.cpp \
    pichistory.cpp \
    picinfo.cpp \
    setpaper.cpp

HEADERS  += titlebar.h \
    mainwindow.h \
    download.h \
    webview.h \
    statubar.h \
    pichistory.h \
    picinfo.h \
    setpaper.h

TRANSLATIONS += i18n/zh_CN.ts

RESOURCES += \
    res.qrc

win32{
RC_FILE = app.rc
}
