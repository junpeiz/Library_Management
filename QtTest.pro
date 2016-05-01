#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T14:34:56
#
#-------------------------------------------------

CONFIG += c++11

LIBS += C:\Users\Flamingo\Desktop\DBExperiment05\QtTest\libmysql.lib

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    borrow_dialog.cpp \
    single_book_in_dialog.cpp \
    return_dialog.cpp \
    book_single_search.cpp \
    CDataBase.cpp \
    book_range_search.cpp \
    card_manage.cpp \
    borrow_list.cpp

HEADERS  += mainwindow.h \
    borrow_dialog.h \
    single_book_in_dialog.h \
    return_dialog.h \
    book_single_search.h \
    CDataBase.h \
    book_range_search.h \
    card_manage.h \
    mysql.h \
    borrow_list.h

FORMS    += mainwindow.ui \
    borrow_dialog.ui \
    single_book_in_dialog.ui \
    return_dialog.ui \
    book_single_search.ui \
    book_range_search.ui \
    card_manage.ui \
    borrow_list.ui

RESOURCES += \
    school_flag.qrc
