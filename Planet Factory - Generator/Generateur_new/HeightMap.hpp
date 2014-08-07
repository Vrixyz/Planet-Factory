#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <QtDebug>
#include <QtGui/qimage.h>
#include <QJsonArray>

//#include <libNoise/include/noise/noise.h>
//#include <libNoise/noiseutils/noiseutils.h>

#include "Component.hpp"
#include "MapInfo.hpp"

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
    bool fillPic(const std::string & path, const std::string & name);

    //export heightmap
    void        exportHeightMap(const std::string & path, const std::string & name);
    QJsonObject exportComposentMap(const std::string & path, int iteration, QJsonObject evo, QString name);
    void        genCompImg(const std::string & name, const std::string & path, const std::string & file);
    void        genCompImgV2(const std::string & name, const std::string & path, const std::string & file);

    //Print in qDebug the different heightmap
    void    printMap();

    /**Getter **/
    MapInfo *** map(void) const;
    Planet*     planet(void) const;
private:
    int         _n;
    int         _r;
    int         _x;
    int         _y;
    MapInfo *** _map;
    std::map<Component*, int> *_cmp;
    e_tectoDirect * _tectoDirect;
    Planet      *_planet;

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
