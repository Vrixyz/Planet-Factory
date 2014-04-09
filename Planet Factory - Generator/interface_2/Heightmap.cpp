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
    std::cout << "Radius of this planet " << _r << " Plate number : " << n << std::endl;
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
                //std::cout << "Plate found at " << x << " " << y << " " << _map[x][y]->n() << std::endl;
                std::list<int>::iterator it;
                for (it = check.begin(); it != check.end(); it++)
                {
                    //std::cout << "Check if already in the list" << std::endl;
                    if ((*it) == _map[x][y]->n())
                    {
                        //std::cout << "Find..." << std::endl;
                        find = true;
                        break;
                    }
                }
                if (find == false)// No in the check list
                {
                    std::cout << "Not on list" << std::endl;
                    check.push_back(_map[x][y]->n());
                    //Upate tectonique plate
                    if (_updateMap(x, y, _map[x][y]->n()) == 0)
                    {
                        counter++;
                        x = 0;
                        y = 0;
                    }
                    if (counter == (_x * _y))
                    {
                        std::cout << "Counter : " << counter << std::endl;
                        return 0;
                    }
                }
            }
            if (check.size() == (unsigned int)n) // list full
            {
                std::cout << "Clear check list..." << std::endl;
                check.clear();
            }
        }
    }
    return 0;
}

int    HeightMap::_updateMap(int x, int y, int c)
{
    std::cout << "Update of the map..." << std::endl;
    int nx, ny;

    //Left
    if (x - 1 < 0)
        nx = _x - 1;
    else
        nx = x - 1;
    if (_map[nx][y]->n() == 0)
    {
        _map[nx][y]->n(c);
        return 0;
    }

    //Top
    if (y - 1 < 0)
        ny = _y - 1;
    else
        ny = y - 1;
    if (_map[x][ny]->n() == 0)
    {
        _map[x][ny]->n(c);
        return 0;
    }

    //Right
    if (x + 1 >= _x)
        nx = 0;
    else
        nx = x + 1;
    if (_map[nx][y]->n() == 0)
    {
        _map[nx][y]->n(c);
        return 0;
    }


    //Bot
    if (y + 1 >= _y)
        ny = 0;
    else
        ny = y + 1;
    if (_map[x][ny]->n() == 0)
    {
        _map[x][ny]->n(c);
        return 0;
    }
    return 1;
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
