#-------------------------------------------------
#
# Project created by QtCreator 2013-05-15T06:29:03
#
#-------------------------------------------------

QT       += core gui sql webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommunitySoftwareInstaller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlmodel.cpp \
    sqldelegate.cpp \
    webbrowser.cpp

HEADERS  += mainwindow.h \
    sqlmodel.h \
    sqldelegate.h \
    webbrowser.h

FORMS    += mainwindow.ui \
    webbrowser.ui
