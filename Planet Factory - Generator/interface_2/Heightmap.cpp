#include "Heightmap.h"

HeightMap::HeightMap(int radius)
    :_r(radius), _x(radius * 4), _y(radius * 2)
{
    _map = new MapInfo**[_x];
    for (int i = 0; i < _x; i++)
    {
        _map[i] = new MapInfo*[_y];
        for (int j = 0; j < _y; j++)
            _map[i][j] = new MapInfo();
    }
}

int HeightMap::exportHeighMap(const std::string & name, const std::string & path)
{
    return 0;
}

int HeightMap::PlateTectonic(int n)
{
    if (n == 0)
        n = 1;
    _n = n;
    std::cout << "Radius of this planet " << _r << std::endl;
    srand(time(0));
    int x, y; //Plate init
    for (int i = 1; i <= n; i++)
    {
        x = rand() % _x;
        y = rand() % _y;
        if ((_map[x][y])->n() == 0)
        {
            std::cout << "Create a Tectonic plate at " << x << " " << y << std::endl;
            (_map[x][y])->n(i);
        }
        else
            i--;
    }
    //Fill all planet with plate
    std::list<int> check;
    std::cout << "Starting to fill the planet with plate..." << std::endl;
    int counter = 0;
    for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
        {
            //std::cout << "x: " << x << " y: " << y << std::endl;
            bool find = false;
            if (_map[x][y]->n() != 0)//A plate found
            {
                std::cout << "Plate found at " << x << " " << y << " " << _map[x][y]->n() << std::endl;
                std::list<int>::iterator it;
                for (it = check.begin(); it != check.end(); it++)
                {
                    std::cout << "Check if already in the list" << std::endl;
                    if ((*it) == _map[x][y]->n())
                    {
                        std::cout << "Find..." << std::endl;
                        find = true;
                        break;
                    }
                }
                if (find == false)// No in the check list
                {
                    std::cout << "Not on list" << std::endl;
                    check.push_back(_map[x][y]->n());
                    //Upate tectonique plate
                    _updateMap(x, y, _map[x][y]->n());
                    x = 0;
                    y = 0;
                    counter++;
                    if (counter == (_x * _y))
                        break;
                }
            }
            if (check.size() == (unsigned int)n) // list full
            {
                std::cout << "Clear check list..." << std::endl;
                check.clear();
            }
        }
    }
    printMap();
    return 0;
}

void    HeightMap::_updateMap(int x, int y, int c)
{
    std::cout << "Update of the map..." << std::endl;
    int nx, ny;
    if (x > 0 && x < _x)
    {
        if (y > 0 && y < _y)
        {
            for (nx = x - 1; nx <= x + 1; x++)
            {
                for (ny = y - 1; ny <= y + 1; y++)
                {
                    if (_map[nx][ny]->n() == 0)
                    {
                        std::cout << "Ajout de " << c << " en x: " << nx << " y: " << ny << std::endl;
                        _map[nx][ny]->n(c);
                        return;
                    }
                }
            }
        }
    }
}

void    HeightMap::printMap()
{
    int x, y;
    for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
        {
            std::cout << _map[x][y]->n();
        }
        std::cout << std::endl;
    }
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
