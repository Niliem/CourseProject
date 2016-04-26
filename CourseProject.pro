#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T18:45:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseProject
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    filtrationform.cpp \
    segmentationform.cpp \
    cell.cpp \
    object.cpp \
    morphology.cpp

HEADERS  += mainwindow.hpp \
    filtrationform.hpp \
    segmentationform.hpp \
    cell.hpp \
    object.hpp \
    morphology.hpp
