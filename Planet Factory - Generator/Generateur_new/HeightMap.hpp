#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <QtDebug>
#include <QtGui/qimage.h>
#include <QJsonArray>
#include <time.h>

#include "libnoise/noise.h"
#include "libnoise/utils/noiseutils.h"
#include "Component.hpp"
#include "MapInfo.hpp"

#define RATIO_PLATE 2
#define SAFE_COUNTER 10000
#define MODIF 3

enum e_typemove
{
    TRANSFORM,
    DIVERGENT,
    CONVERGENT,
    NONE
};

enum e_tectoDirect
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

class Planet;

class HeightMap
{
public:
    HeightMap(int radius, Planet *);
    //Update map
    int changeAlt(int x, int y, int z);

    //Create plates
    int PlateTectonic(int n, std::map<Component *, int> * mapCompo);

    //Create terrain
    int terrain();

    // Save the pic
    bool fillPic(const QString & path, const QString & name);

    //export heightmap
    void        exportHeightMap(const QString & path, const QString & name);
    QJsonObject exportComposentMap(const QString & path, int iteration, QJsonObject evo, QString name);
    bool        genCompImg(const QString & name, const QString & path, const QString & file);

    //Print in qDebug the different heightmap
    void    printMap();

    /**Getter **/
    MapInfo *** map(void) const;
    Planet*     planet(void) const;
private:
    bool        _comp_change;
    int         _n;
    int         _r;
    int         _x;
    int         _y;
    MapInfo *** _map;
    std::map<Component*, int> *_cmp;
    e_tectoDirect * _tectoDirect;
    Planet      *_planet;

    e_typemove _typeMove(int, int);
    int _moveSolid(std::list<MyComponent*>, std::list<MyComponent*>, e_typemove);
    int _moveLiquid(std::list<MyComponent*>, std::list<MyComponent*>, e_typemove);
    int _moveGaz(std::list<MyComponent*>, std::list<MyComponent*>, e_typemove);
    int _fillComponent(std::map<Component*, int>   *mapCompo);
    int _updateMap(int x, int y, int c);
    int _updateTop(int x, int y, int c);
    int _updateRight(int x, int y, int c);
    int _updateBot(int x, int y, int c);
    int _updateLeft(int x, int y, int c);

    int _calcTerrain(std::list<MyComponent*>, std::list<MyComponent*>);

    //return border MapInfo if exist
    MapInfo * _isBorder(int x, int y);
};

#endif // HEIGHTMAP_HPP
