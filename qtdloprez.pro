QT += core gui
TARGET = qtdloprez
HEADERS += libdlo.h dlo_defs.h displaylinkadapter.h mainwindow.h
TEMPLATE = app
SOURCES += main.cpp displaylinkadapter.cpp mainwindow.cpp
FORMS += mainwindow.ui
LIBS += -ldlo
