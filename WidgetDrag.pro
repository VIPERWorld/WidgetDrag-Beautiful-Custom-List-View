#-------------------------------------------------
#
# Project created by QtCreator 2013-02-10T21:04:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetDrag
TEMPLATE = app


SOURCES += main.cpp\
        widgetdrag.cpp \
    variablewidget.cpp \
    parserengine.cpp \
    vectoritemwidget.cpp \
    livelistwidget.cpp

HEADERS  += widgetdrag.h \
    variablewidget.h \
    parserengine.h \
    vectoritemwidget.h \
    livelistwidget.h

FORMS    += widgetdrag.ui

OTHER_FILES += \
    variablewidget.css \
    mylistwidget.css
