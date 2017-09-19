#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:48:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDeviceWatcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    QDeviceWatcher/qdevicewatcher.cpp

HEADERS  += mainwidget.h \
    QDeviceWatcher/qdevicewatcher.h

FORMS    += mainwidget.ui
