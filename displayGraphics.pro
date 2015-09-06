#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T11:00:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = displayGraphics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algorithms.cpp

HEADERS  += mainwindow.h \
    algorithms.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../libs/qcustomplot/bin/ -lqcustomplot

INCLUDEPATH += $$PWD/../libs/qcustomplot/bin
DEPENDPATH += $$PWD/../libs/qcustomplot/bin

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lessentia -lyaml -lavformat -lavcodec -ltag -lsamplerate -lfftw3f

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libessentia.a

unix:!macx: LIBS += -L$$PWD/../libs/k52_dsp/ -lk52_dsp

INCLUDEPATH += $$PWD/../libs/k52_dsp/include
DEPENDPATH += $$PWD/../libs/k52_dsp/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../libs/k52_dsp/libk52_dsp.a
