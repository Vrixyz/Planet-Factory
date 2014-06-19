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

int HeightMap::_fillComponent(std::map<Component*, int> * mapCompo)
{
    qDebug() << "Filling planet with component...";
    srand(time(0));

    float coef = _x *_y / 100;
    int size = mapCompo->size();
    //qDebug() << "_x: " << _x << "_y: " << _y << " size: " << size << "coef:" << coef;

    float tmp[size];
    for (int i = 0; i < size; i++)
        tmp[i] = 0;

    //Adding component
    for (int i = 0; i < _x; i++)
    {
        for (int j = 0; j < _y; j++)
        {
            //Choose random component
            bool find = false;
            while (find == false)
            {
                std::map<Component*, int>::iterator it = mapCompo->begin();
                int x = rand() % size;
                std::advance(it, x);
                if (tmp[x] < it->second) // If componant still ok
                {
                    qDebug() << "[" << i << "][" << j << "] random: " << x
                             << " composant: " << it->first->getName().c_str()
                             << " percent: " << it->second
                             << " actual:" << tmp[x];
                    _map[i][j]->component(it->first);
                    if (coef < 1)
                        tmp[x] += 1.0 * coef;
                    else
                        tmp[x] += 1.0 / coef;
                    find = true;
                }

                //Check total percent
                float total = 0;
                for (x = 0; x < size; x++)
                    total += tmp[x];
                if (total >= 100)
                {
                    qDebug() << "Done.";
                    return 0;
                }
            }
        }
    }
    qDebug() << "Done normaly.";
    return 0;
}

int HeightMap::PlateTectonic(int n, std::map<Component*, int> * mapCompo)
{
    //Fill component
    if (_fillComponent(mapCompo) == 1)
        return 1;

    qDebug() << "Initialization of plates number...";
    if (n < 4)
        n = 4;
    _n = n;
    qDebug() << "Done.";

    qDebug() << "Giving to each plates a random direction...";
    srand(time(0));
    _tectoDirect = new e_tectoDirect[n];
    for (int i = 0; i < n; i++)
        _tectoDirect[i] = static_cast<e_tectoDirect>(rand() % NW);
    qDebug() << "Done.";

    //Plate init
    qDebug() << "Placing starting point of each plates...";
    int x, y;
    (_map[0][0])->n(1);
    for (int i = 2; i <= n; i++)
    {
        x = rand() % _x;
        y = rand() % _y;
        if ((_map[x][y])->n() == 0)
            (_map[x][y])->n(i);
        else
            i--;
    }
    qDebug() << "Done.";

    //Fill all planet with plate with random
    qDebug() << "Starting to fill the planet with plate...";
    std::list<int> check;
    int counter = 0;
    int nbCase = _x * _y;
    int countMax = (nbCase / 4);
    while (counter <= countMax) //check if all the planet if filled
    {
        for (x = 0; x < _x; x++)
        {
            for (y = 0; y < _y; y++)
            {
                bool find = false;
                if (_map[x][y]->n() != 0)//A plate found
                {
                    std::list<int>::iterator it;
                    for (it = check.begin(); it != check.end(); it++)
                    {
                        if ((*it) == _map[x][y]->n())
                        {
                            find = true;
                            break;
                        }
                    }
                    if (find == false)// No in the check list
                    {
                        check.push_back(_map[x][y]->n());
                        //Upate tectonique plate
                        if (_updateMap(x, y, _map[x][y]->n()) == 0)
                            counter++;
                    }
                }
                if (check.size() == (unsigned int)n) // list full
                    check.clear();
            }
        }
    }
    //Finish to fill the planet after the random part
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

    //printMap();
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
            std::cout << _map[x][y]->component()->getName() << '\t';
        std::cout << std::endl;
    }

    for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
            std::cout << _map[x][y]->z() << '\t';
        std::cout << std::endl;
    }

    for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
            std::cout << _map[x][y]->n() << '\t';
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

int HeightMap::exportHeightmap(int ** tab, const std::string & path, const std::string & name)
{
    return 0;
}
