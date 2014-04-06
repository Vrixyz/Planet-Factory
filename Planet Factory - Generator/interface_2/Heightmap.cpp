#include "Heightmap.h"

HeightMap::HeightMap(int radius)
    :_r(radius)
{
    _map = new MapInfo**[radius * 2];
    for (int i = 0; i < radius * 2; i++)
    {
        _map[i] = new MapInfo*[radius];
        for (int j = 0; j < radius; j++)
            _map[i][j] = new MapInfo();
    }
}

int HeightMap::exportHeighMap(const std::string & name, const std::string & path)
{
    return 0;
}

int HeightMap::PlateTectonic(int n)
{
    srand(time(0));
    int x, y; //Plate init
    for (int i = 1; i < n; i++)
    {
        x = rand() % (_r * 2);
        y = rand() % _r;
        if ((_map[x][y])->n() == 0)
        {
            std::cout << "Create a Tectonic plate at " << x << " " << y << std::endl;
            (_map[x][y])->n(i);
        }
        else
            i--;
    }
    //Fill all planet with plate

    return 0;
}

int HeightMap::changeAlt(int x, int y, int z)
{
    _map[x][y]->z(z);
    return 0;
}

/** Getter **/
MapInfo *** HeightMap::map(void)const
{
    return _map;
}
