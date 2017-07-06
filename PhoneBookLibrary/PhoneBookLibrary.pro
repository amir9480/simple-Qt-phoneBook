#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T22:44:04
#
#-------------------------------------------------

QT       += sql

QT       -= gui

CONFIG += c++11

TARGET = PhoneBookLibrary

#for deploy
TEMPLATE = lib

#for test
#TEMPLATE = app

# این قسمت باعث میشه که بدونه الان باید خروجی ها رو به
# dll
# اضافه کنه . اگه این وجود نداشته باشه منظور اینه که از
# dll
# دستورات فراخوانی بشه
# رو ببینید phonebooklibrary_global.h

DEFINES += PHONEBOOKLIBRARY_LIBRARY

SOURCES += contactdetail.cpp \
    contactdb.cpp

HEADERS += contactdetail.h\
        phonebooklibrary_global.h \
    contactdb.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
