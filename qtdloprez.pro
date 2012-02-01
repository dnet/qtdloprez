QT += core gui
TARGET = qtdloprez
HEADERS += libdlo.h dlo_defs.h displaylinkadapter.h displaylinkexception.h mainwindow.h resolutiondialog.h
TEMPLATE = app
SOURCES += main.cpp displaylinkadapter.cpp displaylinkexception.cpp mainwindow.cpp resolutiondialog.cpp
FORMS += mainwindow.ui resolutiondialog.ui
LIBS += -ldlo
