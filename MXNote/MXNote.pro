#-------------------------------------------------
#
# Project created by QtCreator 2020-12-23T14:17:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MXNote
TEMPLATE = app


SOURCES += main.cpp\
    mxnote.cpp

HEADERS  += \
    mxnote.h

FORMS    += mxnote.ui

#------------------------------------------------------
#QHotkey
INCLUDEPATH += $(PWD)../QHotkey/

HEADERS  += ../QHotkey/QHotkey \
    ../QHotkey/qhotkey.h \
    ../QHotkey/qhotkey_p.h

SOURCES += ../QHotkey/qhotkey.cpp
win32: SOURCES += ../QHotkey/qhotkey_win.cpp
#mac:   SOURCES += ../QHotkey/qhotkey_mac.cpp
#linux: SOURCES += ../QHotkey/qhotkey_x11.cpp

#------------------------------------------------------

DISTFILES += \
    MXNote.ico

RC_ICONS = MXNote.ico

RESOURCES += \
    mxnote.qrc
