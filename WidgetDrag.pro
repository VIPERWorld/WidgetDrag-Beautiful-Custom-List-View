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
    mylistwidget.cpp \
    parserengine.cpp \
    vectoritemwidget.cpp

HEADERS  += widgetdrag.h \
    variablewidget.h \
    mylistwidget.h \
    parserengine.h \
    vectoritemwidget.h

FORMS    += widgetdrag.ui

OTHER_FILES += \
    variablewidget.css \
    mylistwidget.css
