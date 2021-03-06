QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = window
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    avl_tree.cpp \
    text.cpp \
    pr_queue.cpp

HEADERS += \
    avl_tree.h \
    pr_queue.h \
    text.h
