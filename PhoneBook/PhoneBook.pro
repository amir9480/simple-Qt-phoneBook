#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T23:45:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhoneBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    contactmodel.cpp \
    contactdialog.cpp

HEADERS  += mainwindow.h \
    contactmodel.h \
    contactdialog.h

FORMS    += mainwindow.ui \
    contactdialog.ui

win32: LIBS += -L$$PWD/../PhoneBookLibrary/build-PhoneBookLibrary-Desktop_Qt_5_7_0_MinGW_32bit/release/ -lPhoneBookLibrary

INCLUDEPATH += $$PWD/../PhoneBookLibrary
DEPENDPATH += $$PWD/../PhoneBookLibrary


MOC_DIR=build
RCC_DIR=build
OBJECTS_DIR=build
UI_DIR=build
