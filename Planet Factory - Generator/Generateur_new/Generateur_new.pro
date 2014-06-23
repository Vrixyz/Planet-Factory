#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T23:31:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =    planetfactory
TEMPLATE =  app


SOURCES +=  main.cpp \
    MainWindow.cpp \
    Menu.cpp \
    CelestialBox.cpp \
    PlanetCompoBox.cpp \
    PlanetDetailsBox.cpp

OTHER_FILES +=

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

HEADERS += \
    MainWindow.hpp \
    Menu.hpp \
    CelestialBox.hpp \
    PlanetCompoBox.hpp \
    PlanetDetailsBox.hpp

RESOURCES   += \
    resources.qrc
