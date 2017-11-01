QT += core network websockets
QT -= gui

CONFIG += c++11

TARGET = Email
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    smtp.cpp \
    worker.cpp

HEADERS += \
    smtp.h \
    worker.h
