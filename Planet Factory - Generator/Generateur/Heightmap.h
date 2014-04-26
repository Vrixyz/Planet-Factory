#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>

#include "Component.hpp"
#include "MapInfo.h"

#define RATIO_PLATE 25

class HeightMap
{
public:
    HeightMap(int radius);
    //Create heightmap picture
    int exportHeighMap(const std::string & name, const std::string & path);
    //Update map
    int changeAlt(int x, int y, int z);
    //Create random zone
    int PlateTectonic(int n, std::map<Component *, int> * mapCompo);

    void    printMap();

    /**Getter **/
    MapInfo *** map(void)const;
private:
    int         _n;
    int         _r;
    int         _x;
    int         _y;
    MapInfo *** _map;

    int _fillComponent(std::map<Component*, int>   *mapCompo);
    int _updateMap(int x, int y, int c);
    int _updateMapSecondAlgo();
    int _updateTop(int x, int y, int c);
    int _updateRight(int x, int y, int c);
    int _updateBot(int x, int y, int c);
    int _updateLeft(int x, int y, int c);
};

#endif // HEIGHTMAP_H
