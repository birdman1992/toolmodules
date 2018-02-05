#-------------------------------------------------
#
# Project created by QtCreator 2018-02-05T17:13:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolynomialCurveFitting
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    paintlab.cpp \
    polcurvefit.cpp

HEADERS  += widget.h \
    paintlab.h \
    polcurvefit.h

FORMS    += widget.ui \
    paintlab.ui
