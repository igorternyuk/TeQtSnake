#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T21:26:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp \
    snakemodel.cpp \
    snakecontroller.cpp \
    snakeview.cpp \
    snake.cpp \
    digitaltable.cpp \
    fieldwidget.cpp \
    enemy.cpp

HEADERS  += \
    snakemodel.h \
    snakecontroller.h \
    snakeview.h \
    snake.h \
    digitaltable.h \
    fieldwidget.h \
    enemy.h

CONFIG += c++1z

FORMS    +=

