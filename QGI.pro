QT       += core network sql
QT       -= gui
TARGET    = Application.qgi
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += main.cpp \
    Html.cpp \
    Cgi.cpp

HEADERS += \
    QGI \
    Html.h \
    Cgi.h
