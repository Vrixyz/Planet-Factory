#include "HeightMap.hpp"

HeightMap::HeightMap(int radius)
    :_r(radius), _x(radius * 4), _y(radius * 2)
{
    _map = new MapInfo**[_x];

    //test libnoise
    /*noise::module::Perlin perlin;
    noise::utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;

    heightMapBuilder.SetSourceModule(perlin);
    heightMapBuilder.SetDestNoiseMap(noiseMap);
    heightMapBuilder.SetDestSize (_x, _y);
    heightMapBuilder.SetBounds(0, _x, 0, _y);
    heightMapBuilder.Build();

    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            _map[x][y]->z(perlin.GetValue(x, y, 0.5));
        }
    }*/
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

    //Temp component array to check percent
    float tmp[size];
    for (int i = 0; i < size; i++)
        tmp[i] = 0;

    //New component system

    //For each component
    std::map<Component*, int>::iterator it = mapCompo->begin();
    for (it; it != mapCompo->end(); it++)
    {
        int total = 0;
        //In each case of the map
        for (int i = 0; i <_x; i++)
        {
            for (int j = 0; j < _y; j++)
            {
                //Calc a random percent, can't > 100% for case and total > 100%
                int libre = _map[i][j]->freeSpace();
                if (libre > 0)
                {
                    int p = 0;

                    _map[i][j]->editComponent(it->first, p, SOLID);
                    total += p;
                }
                else
                    _map[i][j]->editComponent(it->first, 0, SOLID);

            }
        }
    }


    qDebug() << "Filling planet with component... BIS";

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
                    /*qDebug() << "[" << i << "][" << j << "] random: " << x
                             << " composant: " << it->first->getName().c_str()
                             << " percent: " << it->second
                             << " actual:" << tmp[x];*/
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
    _cmp = mapCompo;
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

int HeightMap::terrain()
{
    //Stocker les cases de frontières 2, par 2, la 1ère et celle qui est dans le sens influer
    qDebug() << "Checking border...";
    std::map<MapInfo*, MapInfo*> borders;
    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            MapInfo * tmp = _isBorder(x, y);
            if (tmp)
            {
                borders[_map[x][y]] = tmp;
            }
        }
    }
    qDebug() << "Checking border, done.";

    //Influer le mouvement des plaques
    qDebug() << "Move plates...";
    if (borders.size() == 0)
    {
        qDebug() << "Move plates, error : No border.";
        return 1;
    }
    std::map<MapInfo*, MapInfo*>::iterator it;
    for (it = borders.begin(); it != borders.end(); it++)
    {
        Component * c1 = it->first->component();
        Component * c2 = it->second->component();
        e_etat e1 = it->first->etat();
        e_etat e2 = it->second->etat();
    }
    qDebug() << "Move plates, done.";
    return 0;
}

MapInfo * HeightMap::_isBorder(int x, int y)
{
    e_tectoDirect direction = _tectoDirect[(_map[x][y])->n()];
    switch (direction)
    {
        case NORTH: {
            int nx;
            if (x - 1 < 0)
                nx = _x - 1;
            else
                nx = x - 1;
            if (_map[x][y]->n() != _map[nx][y]->n())
                return _map[nx][y];
            break;
        }
        case NE: {
            int nx;
            if (x - 1 < 0)
                nx = _x - 1;
            else
                nx = x - 1;
            int ny;
            if (y + 1 >= _y)
                ny = 0;
            else
                ny = y + 1;
            if (_map[x][y]->n() != _map[nx][ny]->n())
                return _map[nx][ny];
            break;
        }
        case EAST: {
            int ny;
            if (y + 1 >= _y)
                ny = 0;
            else
                ny = y + 1;
            if (_map[x][y]->n() != _map[x][ny]->n())
                return _map[x][ny];
            break;
        }
        case SE: {
            int nx;
            if (x + 1 >= _x)
                nx = 0;
            else
                nx = x + 1;
            int ny;
            if (y + 1 >= _y)
                ny = 0;
            else
                ny = y + 1;
            if (_map[x][y]->n() != _map[nx][ny]->n())
                return _map[nx][ny];
            break;
        }
        case SOUTH: {
            int nx;
            if (x + 1 >= _x)
                nx = 0;
            else
                nx = x + 1;
            if (_map[x][y]->n() != _map[nx][y]->n())
                return _map[nx][y];
            break;
        }
        case SW: {
            int nx;
            if (x + 1 >= _x)
                nx = 0;
            else
                nx = x + 1;
            int ny;
            if (y - 1 < 0)
                ny = _y - 1;
            else
                ny = y - 1;
            if (_map[x][y]->n() != _map[nx][ny]->n())
                return _map[nx][ny];
            break;
        }
        case WEST: {
            int ny;
            if (y - 1 < 0)
                ny = _y - 1;
            else
                ny = y - 1;
            if (_map[x][y]->n() != _map[x][ny]->n())
                return _map[x][ny];
            break;
        }
        case NW: {
            int nx;
            if (x - 1 < 0)
                nx = _x - 1;
            else
                nx = x - 1;
            int ny;
            if (y - 1 < 0)
                ny = _y - 1;
            else
                ny = y - 1;
            if (_map[x][y]->n() != _map[nx][ny]->n())
                return _map[nx][ny];
            break;
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
        {
            if (_updateLeft(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        }
        else if(i == 1)//Top
        {
            if (_updateTop(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        }
        else if(i == 2)//Right
        {
            if (_updateRight(x, y, c) == 0)
                return 0;
            else
            {
                i++;
                n++;
            }
        }
        else if(i == 3)//Bot
        {
            if (_updateBot(x, y, c) == 0)
                return 0;
            else
            {
                i = 0;
                n++;
            }
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
            std::cout << _map[x][y]->n();
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

void HeightMap::exportHeightMap(const std::string & path, const std::string & name)
{
    QImage pic(_x, _y, QImage::Format_RGB32);

    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            int value = _map[x][y]->z();
            QRgb color = qRgb(value, value, value);
            pic.setPixel(x, y, color);
        }
    }

    QString completePath = "";
    QString _path(path.c_str());
    QString _name(name.c_str());

    completePath += _path;
    completePath += "/";
    completePath += _name;
    completePath += ".png";

    if (!pic.save(completePath))
        qDebug() << "Error: pics not saved!";
    else
        qDebug() << "IMG save: " << completePath;
}

 void HeightMap::genCompImg(const std::string & name, const std::string & path, const std::string & file)
{
    QImage pic(_x, _y, QImage::Format_RGB32);

    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            std::string tmp = _map[x][y]->component()->getName();
            QRgb color;
            if (tmp == name)
                color = qRgb(255, 255, 255);
            else
                color = qRgb(0, 0, 0);
            pic.setPixel(x, y, color);
        }
    }

    QString completePath = "";
    QString _path(path.c_str());
    QString _name(file.c_str());

    completePath += _path;
    completePath += "/";
    completePath += _name;
    completePath += ".png";

    if (!pic.save(completePath))
        qDebug() << "Error: pics not saved!: " << completePath;
    else
        qDebug() << "IMG save: " << completePath;
}

QJsonObject HeightMap::exportComposentMap(const std::string & path, int iteration, QJsonObject evo, QString folder)
{
    std::map<Component*, int>::iterator it;
    QJsonArray materials;

    for(it = _cmp->begin(); it != _cmp->end(); it++)
    {
        Component* comp = it->first;
        QJsonObject obj;
        QString file = QString("Material") + comp->getName().c_str() + QString::number(iteration);
        QString file_path = folder + "/" + file;

        //obj.insert("name", comp->getName().c_str());
        obj.insert("file", file_path);
        materials.append(obj);
        genCompImg(comp->getName(), path, file.toStdString());
    }
    evo.insert("materials", materials);
    return evo;
}
