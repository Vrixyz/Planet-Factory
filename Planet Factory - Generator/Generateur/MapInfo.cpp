#include <cstdlib>

#include "MapInfo.h"

MapInfo::MapInfo()
    :_n(0), _component(0), _etat(SOLID)
{
    _z = (rand() % 100) + 50;
}

MapInfo::MapInfo(int i, int j, MapInfo *** _map)
    :_n(0), _component(0)
{
    int tmp = (rand() % 100) + 50;
    if (i == 0)
    {
        _z = (tmp + _map[0][j - 1]->z()) / 2;
    }
    else
    {
        if (j == 0)
        {
            _z = (tmp + _map[i - 1][0]->z()) / 2;
        }
        else
        {
            _z = (tmp + _map[i - 1][j]->z() + _map[i][j - 1]->z()) / 3;
        }
    }
}

/** Setter **/
void MapInfo::z(int z)
{
    _z = z;
}

void MapInfo::n(int n)
{
    _n = n;
}

void MapInfo::component(Component * c)
{
    _component = c;
}

/** Getter **/
int MapInfo::z(void)const
{
    return _z;
}
int MapInfo::n(void)const
{
    return _n;
}

Component * MapInfo::component(void) const
{
    return _component;
}
