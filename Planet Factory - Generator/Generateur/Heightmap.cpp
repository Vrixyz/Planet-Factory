#include "Heightmap.h"

HeightMap::HeightMap(int radius)
    :_r(radius), _x(radius * 4), _y(radius * 2)
{
    _map = new MapInfo**[_x];
    for (int i = 0; i < _x; i++)
    {
        _map[i] = new MapInfo*[_y];
        for (int j = 0; j < _y; j++)
        {
            if (i == 0 && j == 0)
                _map[i][j] = new MapInfo();
            else
                _map[i][j] = new MapInfo(i, j, _map);
        }
    }
}

int HeightMap::exportHeighMap(const std::string & name, const std::string & path)
{
    return 0;
}

int HeightMap::PlateTectonic(int n)
{
    //n = 2;
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
            if (i == 1)
                (_map[0][0])->n(i);
            else
                (_map[x][y])->n(i);
        }
        else
            i--;
    }
    //Fill all planet with plate
    std::list<int> check;
    std::cout << "Starting to fill the planet with plate..." << std::endl;
    int counter = 0;
    int nbCase = _x * _y;
    int countMax = (nbCase / 4);
    std::cout << "Count Max: " << countMax << std::endl;
    while (counter <= countMax)
    {
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
                        //std::cout << "Not on list" << std::endl;
                        check.push_back(_map[x][y]->n());
                        //Upate tectonique plate
                        if (_updateMap(x, y, _map[x][y]->n()) == 0)
                        {
                            counter++;
                            std::cout << "Counter : " << counter << std::endl;
                        }
                        else
                            std::cout << "No more room..." << std::endl;
                    }
                }
                if (check.size() == (unsigned int)n) // list full
                {
                    std::cout << "Clear check list..." << std::endl;
                    check.clear();
                }
            }
        }
    }
    _updateMapSecondAlgo();
    return 0;
}

int     HeightMap::_updateMapSecondAlgo()
{
    int last = 0;
    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            if (_map[x][y]->n() != 0)//A plate found
               last = _map[x][y]->n();
            else if (_map[x][y]->n() == 0 && last != 0)
                _map[x][y]->n(last);
        }
    }
    return 0;
}

int    HeightMap::_updateMap(int x, int y, int c)
{
    int i = rand() % 4;
    int n = 0;

    printMap();
    std::cout << "Update of the map... x: " << x << " y : " << y << " c : " << c << " i: " << i << std::endl;
    while(n < 4)
    {
        if(i == 0)//Left
            if (_updateLeft(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        else if(i == 1)//Top
            if (_updateTop(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        else if(i == 2)//Right
            if (_updateRight(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        else if(i == 3)//Bot
            if (_updateBot(x, y, c) == 0)
                return 0;
            else
            {
                i = 0;
                n++;
            }
    }
    return 1;
}

int     HeightMap::_updateTop(int x, int y, int c)
{
    int nx;
    if (x - 1 < 0)
        nx = _x - 1;
    else
        nx = x - 1;
    if (_map[nx][y]->n() == 0)
    {
        _map[nx][y]->n(c);
        return 0;
    }
    return 1;
}


int     HeightMap::_updateRight(int x, int y, int c)
{
    int ny;
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

int     HeightMap::_updateBot(int x, int y, int c)
{
    int nx;
    if (x + 1 >= _x)
        nx = 0;
    else
        nx = x + 1;
    if (_map[nx][y]->n() == 0)
    {
        _map[nx][y]->n(c);
        return 0;
    }
    return 1;
}

int     HeightMap::_updateLeft(int x, int y, int c)
{
    int ny;
    if (y - 1 < 0)
        ny = _y - 1;
    else
        ny = y - 1;
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
            std::cout << _map[x][y]->z() << '\t';
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
