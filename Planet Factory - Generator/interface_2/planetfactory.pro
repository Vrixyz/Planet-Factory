#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T23:31:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =    planetfactory
TEMPLATE =  app


SOURCES +=  PlanetDetailsBox.cpp \
            PlanetCompoBox.cpp \
            CelestialBox.cpp \
            MainWindow.cpp \
            OptionsBox.cpp \
            GroupTools.cpp \
            Component.cpp \
            Planet.cpp \
            main.cpp \
            System.cpp

HEADERS  += PlanetDetailsBox.hpp \
            PlanetCompoBox.hpp \
            CelestialBox.hpp \
            MainWindow.hpp \
            OptionsBox.hpp \
            GroupTools.hpp \
            Component.hpp \
            include.hpp \
            Planet.hpp \
            System.h

OTHER_FILES +=

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
