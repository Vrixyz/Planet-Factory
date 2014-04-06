#include "MapInfo.h"

MapInfo::MapInfo()
    :_z(0), _n(0)
{
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

/** Getter **/
int MapInfo::z(void)const
{
    return _z;
}
int MapInfo::n(void)const
{
    return _n;
}
