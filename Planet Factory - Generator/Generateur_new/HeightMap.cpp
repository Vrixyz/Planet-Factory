#include "HeightMap.hpp"

//1024 512 ALL TIME
HeightMap::HeightMap(int radius, Planet *p)
    :_r(radius), _x(radius * 4), _y(radius * 2)
{
    _map = new MapInfo**[_x];
    _planet = p;
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

    //Set componentn list in mapInfo
    for (int i = 0; i < _x; i++)
    {
        for (int j = 0; j < _y; j++)
        {
            _map[i][j]->components(mapCompo);
        }
    }

    //float coef = _x *_y / 100;
    int mapSize = _x * _y;
    int size = mapCompo->size();
    //qDebug() << "_x: " << _x << "_y: " << _y << " size: " << size << "coef:" << coef;

    //Temp component array to check percent
    float* tmp = (float*)malloc(size * sizeof(tmp));

    //Temp component array to check percent
    for (int i = 0; i < size; i++)
        tmp[i] = 0;

    //New component system

    //For each component
    std::map<Component*, int>::iterator it;
    for (it = mapCompo->begin(); it != mapCompo->end(); it++)
    {
        float totalFree = 0;
        //In each case of the map
        for (int i = 0; i <_x; i++)
        {
            for (int j = 0; j < _y; j++)
            {
                // If we can still put some of this component on the planet
                if (totalFree != 100)
                {
                    //Calc a random percent, can't > 100% for case and total > 100%
                    float free = _map[i][j]->freeSpace();
                    float p = 0;
                    if (free > 0)
                    {
                        //if it is the last component of the list p = all the free space
                        if (it == mapCompo->end())
                            p = free;
                        else
                        {
                            p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / free);
                            if (totalFree + (p / mapSize) > 100)
                                p = 100 - totalFree;
                        }
                        //qDebug() << "Filling [" << i << ";" << j << "] with " << p << "%. Total : " << totalFree;
                        if ((_map[i][j]->editComponent(it->first, p, SOLID)) != 0)
                            //qDebug() << "Edit KO";
                        totalFree += (p / mapSize);
                    }
                    else
                    {
                        //qDebug() << "Filling [" << i << ";" << j << "] with 0%. Total : " << totalFree;
                        _map[i][j]->editComponent(it->first, 0, SOLID);
                    }
                }
                else
                {
                    //qDebug() << "Filling [" << i << ";" << j << "] with 0%. Total : " << totalFree;
                    _map[i][j]->editComponent(it->first, 0, SOLID);
                }
            }
        }
    }

    for (int i = 0; i <_x; i++)
    {
        for (int j = 0; j < _y; j++)
        {
           (_map[i][j])->loadXY(i, j);
        }
    }
    qDebug() << "Done normaly.";
    return 0;
}

/*
 * TODO
 * A mon avis un changement des fillplate en passant a du recursif augmenterai grandement la rapidite
 * Donc a voir si c'est possible et si on ne passe pas la limite de recursion avec 1024*512 pixel.
 */
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
        _tectoDirect[i] = static_cast<e_tectoDirect>(rand() % WEST);
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
    qDebug() << "Done.";
    return 0;
}

int HeightMap::terrain()
{
    //Stocker les cases de frontières 2, par 2, la 1ère et celle qui est dans le sens influer
    qDebug() << "Checking border...";
    std::map<MapInfo*, MapInfo*> borders;
    int nb = 0;
    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            (_map[x][y])->loadN();
            MapInfo * tmp = _isBorder(x, y);
            if (tmp)
            {
                borders[_map[x][y]] = tmp;
                nb++;
            }
        }
    }
    qDebug() << "Checking border, done, " << nb << " borders found.";

    //Influer le mouvement des plaques
    qDebug() << "Move plates...";
    if (borders.size() == 0)
    {
        qDebug() << "Move plates, error : No border.";
        return 1;
    }
    std::map<MapInfo*, MapInfo*>::iterator it;
    qDebug() << "Map before...";
    this->printMap();
    for (it = borders.begin(); it != borders.end(); it++)
    {
        std::list<MyComponent*> c1 = it->first->components();
        std::list<MyComponent*> c2 = it->second->components();
        _calcTerrain(c1, c2);
    }
    qDebug() << "Map after...";
    this->printMap();
    qDebug() << "Move plates, done.";
    return 0;
}

int HeightMap::_calcTerrain(std::list<MyComponent*> c1, std::list<MyComponent*> c2)
{
    //plate number
    int n1 = 0;
    int n2 = 0;

    //Temp lists to calc
    std::list<MyComponent*> solid1;
    std::list<MyComponent*> liquid1;
    std::list<MyComponent*> gaz1;
    std::list<MyComponent*> solid2;
    std::list<MyComponent*> liquid2;
    std::list<MyComponent*> gaz2;

    std::list<MyComponent*>::iterator it;

    qDebug() << "Doing temp list...";

    for (it = c1.begin(); it != c1.end(); ++it)
    {
        if (n1 == 0)
            n1 = (*it)->n();
        if ((*it)->etat() == SOLID)
            solid1.push_back(*it);
        else if ((*it)->etat() == LIQUID)
            liquid1.push_back(*it);
        else
            gaz1.push_back(*it);
    }

    for (it = c2.begin(); it != c2.end(); ++it)
    {
        if (n2 == 0)
            n2 = (*it)->n();
        if ((*it)->etat() == SOLID)
            solid2.push_back(*it);
        else if ((*it)->etat() == LIQUID)
            liquid2.push_back(*it);
        else
            gaz2.push_back(*it);
    }

    qDebug() << "Done.";

    //Find move type
    qDebug() << "Looking for move type...";
    e_typemove type = _typeMove(n1, n2);
    qDebug() << "Done.";

    //Move SOLID
    _moveSolid(solid1, solid2, type);

    //Move LIQUID
    _moveLiquid(liquid1, liquid2, type);

    //Move GAZ
    _moveGaz(gaz1, gaz2, type);

    return 0;
}

int HeightMap::_moveSolid(std::list<MyComponent*> solid1, std::list<MyComponent*> solid2, e_typemove type)
{
    //return 0;
    std::list<MyComponent*>::iterator it;
    int x = 0;
    int y = 0;
    switch (type)
    {
    case TRANSFORM: { //This one need to be up
        qDebug() << "TRANSFORM.";

        it = solid1.begin();
        x = (*it)->x();
        y = (*it)->y();
        _map[x][y]->z(_map[x][y]->z() - (MODIF * 2));

        it = solid2.begin();
        x = (*it)->x();
        y = (*it)->y();
        _map[x][y]->z(_map[x][y]->z() - (MODIF * 2));

        qDebug() << "Done.";
    }
    case DIVERGENT: {
        // eg <-->
        qDebug() << "DIVERGENT.";
        it = solid1.begin();
        x = (*it)->x();
        y = (*it)->y();
        _map[x][y]->z(_map[x][y]->z() - MODIF);

        it = solid2.begin();
        x = (*it)->x();
        y = (*it)->y();
        _map[x][y]->z(_map[x][y]->z() - MODIF);
        qDebug() << "Done.";
    }
    case CONVERGENT : {
        // eg -><-
        qDebug() << "CONVERGENT.";
        //calc bigger mass
        int mass1 = 0;
        for (it = solid1.begin(); it != solid1.end(); ++it)
            mass1 += (*it)->component()->getMass();
        it = solid1.begin();
        int x1 = (*it)->x();
        int y1 = (*it)->y();

        int mass2 = 0;
        for (it = solid2.begin(); it != solid2.end(); ++it)
            mass2 += (*it)->component()->getMass();
        it = solid2.begin();
        int x2 = (*it)->x();
        int y2 = (*it)->y();

        if (mass1 > mass2) //heavier go under
        {
            if (_map[x1][y1]->z() > (_map[x2][y2]->z() / 2))
                _map[x1][y1]->z(_map[x1][y1]->z() - MODIF);
            _map[x2][y2]->z(_map[x2][y2]->z() + MODIF);
        }
        else
        {
            if (_map[x2][y2]->z() > (_map[x1][y1]->z() / 2))
                _map[x1][y1]->z(_map[x1][y1]->z() + MODIF);
            _map[x2][y2]->z(_map[x2][y2]->z() - MODIF);
        }
        qDebug() << "Done.";
    }
    default : {
        // eg ->->
        qDebug() << "NONE.";
        //calc bigger mass
        int mass1 = 0;
        for (it = solid1.begin(); it != solid1.end(); ++it)
            mass1 += (*it)->component()->getMass();
        it = solid1.begin();
        int x1 = (*it)->x();
        int y1 = (*it)->y();

        int mass2 = 0;
        for (it = solid2.begin(); it != solid2.end(); ++it)
            mass2 += (*it)->component()->getMass();
        it = solid2.begin();
        int x2 = (*it)->x();
        int y2 = (*it)->y();

        if (mass1 > mass2) //heavier erase lighter
        {
            if (_map[x1][y1]->z() > (_map[x2][y2]->z() / 2))
            {
                _map[x2][y2]->z(_map[x1][y1]->z());
                _map[x2][y2]->n(_map[x1][y1]->n());
            }
            else
            {
                _map[x1][y1]->z(_map[x1][y1]->z() + MODIF);
                _map[x2][y2]->z(_map[x2][y2]->z() - MODIF);
            }
        }
        else
        {
            if (_map[x2][y2]->z() > (_map[x1][y1]->z() / 2))
            {
                _map[x1][y1]->z(_map[x2][y2]->z());
                _map[x1][y1]->n(_map[x2][y2]->n());
            }
            else
            {
                _map[x2][y2]->z(_map[x2][y2]->z() + MODIF);
                _map[x1][y1]->z(_map[x1][y1]->z() - MODIF);
            }
        }
        qDebug() << "Done.";
    }
    }

    return 0;
}

int HeightMap::_moveLiquid(std::list<MyComponent*> liquid1, std::list<MyComponent*> liquid2, e_typemove type)
{
    switch (type)
    {
        case TRANSFORM: {
            // eg \\

        }
        case DIVERGENT: {
            // eg <-->

        }
        case CONVERGENT : {
            // eg -><-

        }
        default : {
            // eg ->->

        }
    }
    return 0;
}

int HeightMap::_moveGaz(std::list<MyComponent*> gaz1, std::list<MyComponent*> gaz2, e_typemove type)
{
    switch (type)
    {
    case TRANSFORM: {
        // eg \\

    }
    case DIVERGENT: {
        // eg <-->

    }
    case CONVERGENT : {
        // eg -><-

    }
    default : {
        // eg ->->

    }
    }
    return 0;
}

e_typemove  HeightMap::_typeMove(int n1, int n2)
{
    if (_tectoDirect[n1] == _tectoDirect[n2])
    {
        //qDebug() << "NONE";
        return NONE;
    }
    else if ((_tectoDirect[n1] == NORTH && _tectoDirect[n2] == SOUTH)
             ||(_tectoDirect[n1] == WEST && _tectoDirect[n2] == EAST))
    {
        //qDebug() << "DIVERGENT";
        return DIVERGENT;
    }
    else if ((_tectoDirect[n1] == SOUTH && _tectoDirect[n2] == NORTH)
             || (_tectoDirect[n1] == EAST && _tectoDirect[n2] == WEST))
    {
        //qDebug() << "CONVERGENT";
        return CONVERGENT;
    }
    else
    {
        //qDebug() << "TRANSFORM";
        return TRANSFORM;
    }
    return NONE;
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
    default: {
        return 0;
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
    /*for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
            std::cout << _map[x][y]->component()->getName() << '\t';
        std::cout << std::endl;
    }*/

    QString tmp;

    for (x = 0; x < _x; x++)
    {
        tmp = "";
        for (y = 0; y < _y; y++)
        {
            tmp += QString::number(_map[x][y]->z());
            tmp += '\t';
        }
        qDebug() << tmp;
        qDebug() << "------------------------------";
    }

    /*for (x = 0; x < _x; x++)
    {
        for (y = 0; y < _y; y++)
            std::cout << _map[x][y]->n();
        std::cout << std::endl;
    }*/
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

void HeightMap::exportHeightMap(const QString & path, const QString & name)
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
    QString _path(path);
    QString _name(name);

    completePath += _path;
    completePath += "/";
    completePath += _name;
    completePath += ".png";

    if (!pic.save(completePath))
        qDebug() << "Error: pics not saved!";
    else
        qDebug() << "IMG save: " << completePath;
}

QJsonObject HeightMap::exportComposentMap(const QString & path, int iteration, QJsonObject evo, QString folder)
{
    std::map<Component*, int>::iterator it;
    QJsonArray materials;

    for(it = _cmp->begin(); it != _cmp->end(); it++)
    {
        Component* comp = it->first;
        QJsonObject obj;
        QString file = QString("Material") + comp->getName() + QString::number(iteration);
        QString file_path = folder + "/" + file;

        obj.insert("name", comp->getName());
        obj.insert("file", file_path);
        materials.append(obj);
        genCompImg(comp->getName(), path, file);
    }
    evo.insert("materials", materials);
    return evo;
}

void HeightMap::genCompImg(const QString & name, const QString & path, const QString & file)
{
    QImage pic(_x, _y, QImage::Format_RGB32);
    std::list<MyComponent *> comp_list;
    QRgb black = qRgb(0, 0, 0);

    for (int x = 0; x < _x; x++)
    {
        for (int y = 0; y < _y; y++)
        {
            QRgb color = black;
            comp_list = _map[x][y]->components();
            for (std::list<MyComponent *>::iterator it = comp_list.begin(); it != comp_list.end(); ++it)
            {
                QString tmp = (*it)->component()->getName();
                if (tmp == name)
                {
                    int percent = (*it)->percent();
                    int value = (255 * percent) / 100;
                    color = qRgb(value, value, value);
                }
            }
           pic.setPixel(x, y, color);
        }
    }

    QString completePath = "";
    QString _path(path);
    QString _name(file);

    completePath += _path;
    completePath += "/";
    completePath += _name;
    completePath += ".png";

    if (!pic.save(completePath))
        qDebug() << "Error: pics not saved!: " << completePath;
    else
        qDebug() << "IMG save: " << completePath;
}

Planet* HeightMap::planet(void)const
{
    return _planet;
}
