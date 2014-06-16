#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <QtDebug>

#include "Component.hpp"
#include "MapInfo.h"

#define RATIO_PLATE 25

enum e_tectoDirect
{
    NORTH = 0,
    NE,
    EAST,
    SE,
    SOUTH,
    SW,
    WEST,
    NW
};

class HeightMap
{
public:
    HeightMap(int radius);
    //Update map
    int changeAlt(int x, int y, int z);
    //Create plates
    int PlateTectonic(int n, std::map<Component *, int> * mapCompo);
    //export heightmap
    int exportHeightmap(int ** tab, const std::string & path, const std::string & name);
    //Print in qDebug the different heightmap
    void    printMap();

    /**Getter **/
    MapInfo *** map(void)const;
private:
    int         _n;
    int         _r;
    int         _x;
    int         _y;
    MapInfo *** _map;
    e_tectoDirect * _tectoDirect;

    int _fillComponent(std::map<Component*, int>   *mapCompo);
    int _updateMap(int x, int y, int c);
    int _updateMapSecondAlgo();
    int _updateTop(int x, int y, int c);
    int _updateRight(int x, int y, int c);
    int _updateBot(int x, int y, int c);
    int _updateLeft(int x, int y, int c);
};

#endif // HEIGHTMAP_H
