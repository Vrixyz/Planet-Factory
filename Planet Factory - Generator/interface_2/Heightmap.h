#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "MapInfo.h"

class HeightMap
{
public:
    HeightMap(int radius);
    //Create heightmap picture
    int exportHeighMap(const std::string & name, const std::string & path);
    //Update map
    int changeAlt(int x, int y, int z);
    //Create random zone
    int PlateTectonic(int n);

    /**Getter **/
    MapInfo *** map(void)const;
private:
    int         _r;
    MapInfo *** _map;

};

#endif // HEIGHTMAP_H
