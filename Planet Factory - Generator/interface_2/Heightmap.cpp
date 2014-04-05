#include "Heightmap.h"

HeightMap::HeightMap(int radius)
{
    _map = new int*[radius * 2];
    for (int i = 0; i < radius * 2; i++)
        _map[i] = new int[radius];
}

int HeightMap::exportHeighMap(const std::string & name, const std::string & path)
{
    return 0;
}

int HeightMap::changeAlt(int x, int y, int z)
{
    _map[x][y] = z;
    return 0;
}

/** Getter **/
int ** HeightMap::map(void)const
{
    return _map;
}
