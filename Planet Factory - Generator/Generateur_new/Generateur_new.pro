#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T23:31:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =    planetfactory
TEMPLATE =  app

CONFIG += warn_off

SOURCES +=  main.cpp \
    MainWindow.cpp \
    Menu.cpp \
    CelestialBox.cpp \
    PlanetCompoBox.cpp \
    PlanetDetailsBox.cpp \
    Component.cpp \
    Planet.cpp \
    System.cpp \
    HeightMap.cpp \
    MapInfo.cpp \
    Move.cpp \
    MyComponent.cpp \
    Terrain.cpp \
    GenWin.cpp \
    HexToRgb.cpp \
    libnoise/model/cylinder.cpp \
    libnoise/model/line.cpp \
    libnoise/model/plane.cpp \
    libnoise/model/sphere.cpp \
    libnoise/module/abs.cpp \
    libnoise/module/add.cpp \
    libnoise/module/billow.cpp \
    libnoise/module/blend.cpp \
    libnoise/module/cache.cpp \
    libnoise/module/checkerboard.cpp \
    libnoise/module/clamp.cpp \
    libnoise/module/const.cpp \
    libnoise/module/curve.cpp \
    libnoise/module/cylinders.cpp \
    libnoise/module/displace.cpp \
    libnoise/module/exponent.cpp \
    libnoise/module/invert.cpp \
    libnoise/module/max.cpp \
    libnoise/module/min.cpp \
    libnoise/module/modulebase.cpp \
    libnoise/module/multiply.cpp \
    libnoise/module/perlin.cpp \
    libnoise/module/power.cpp \
    libnoise/module/ridgedmulti.cpp \
    libnoise/module/rotatepoint.cpp \
    libnoise/module/scalebias.cpp \
    libnoise/module/scalepoint.cpp \
    libnoise/module/select.cpp \
    libnoise/module/spheres.cpp \
    libnoise/module/terrace.cpp \
    libnoise/module/translatepoint.cpp \
    libnoise/module/turbulence.cpp \
    libnoise/module/voronoi.cpp \
    libnoise/latlon.cpp \
    libnoise/noisegen.cpp \
    NoiseComp.cpp \
    libnoise/utils/noiseutils.cpp

HEADERS += \
    MainWindow.hpp \
    Menu.hpp \
    CelestialBox.hpp \
    PlanetCompoBox.hpp \
    PlanetDetailsBox.hpp \
    Component.hpp \
    Planet.hpp \
    System.hpp \
    HeightMap.hpp \
    MapInfo.hpp \
    Move.hpp \
    MyComponent.hpp \
    Terrain.hpp \
    GenWin.hpp \
    HexToRgb.hpp \
    libnoise/model/cylinder.h \
    libnoise/model/line.h \
    libnoise/model/model.h \
    libnoise/model/plane.h \
    libnoise/model/sphere.h \
    libnoise/module/abs.h \
    libnoise/module/add.h \
    libnoise/module/billow.h \
    libnoise/module/blend.h \
    libnoise/module/cache.h \
    libnoise/module/checkerboard.h \
    libnoise/module/clamp.h \
    libnoise/module/const.h \
    libnoise/module/curve.h \
    libnoise/module/cylinders.h \
    libnoise/module/displace.h \
    libnoise/module/exponent.h \
    libnoise/module/invert.h \
    libnoise/module/max.h \
    libnoise/module/min.h \
    libnoise/module/module.h \
    libnoise/module/modulebase.h \
    libnoise/module/multiply.h \
    libnoise/module/perlin.h \
    libnoise/module/power.h \
    libnoise/module/ridgedmulti.h \
    libnoise/module/rotatepoint.h \
    libnoise/module/scalebias.h \
    libnoise/module/scalepoint.h \
    libnoise/module/select.h \
    libnoise/module/spheres.h \
    libnoise/module/terrace.h \
    libnoise/module/translatepoint.h \
    libnoise/module/turbulence.h \
    libnoise/module/voronoi.h \
    libnoise/basictypes.h \
    libnoise/exception.h \
    libnoise/interp.h \
    libnoise/latlon.h \
    libnoise/mathconsts.h \
    libnoise/misc.h \
    libnoise/noise.h \
    libnoise/noisegen.h \
    libnoise/vectortable.h \
    NoiseComp.hpp \
    libnoise/utils/noiseutils.h

RESOURCES   += \
    resources.qrc
