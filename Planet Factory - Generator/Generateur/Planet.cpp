#include "Planet.hpp"
#include "System.h"

Planet::Planet()
    :_move(false), _evolve(false)
{
    _mapCompo = new std::map<Component*, int>();
}

Planet::Planet(QJsonObject obj, System * s)
    :_move(false), _evolve(false)
{
    _mapCompo = new std::map<Component*, int>();

    _name = obj["name"].toString().toStdString();
    _radius = obj["radius"].toInt();

   QJsonObject pos = obj["pos"].toObject();
   _pos[0] = pos["x"].toInt();
   _pos[1] = pos["y"].toInt();
   _pos[2] = pos["z"].toInt();

   QJsonArray composant = obj["composant"].toArray();
   foreach (QJsonValue value, composant)
   {
        QJsonObject comp = value.toObject();
        Component *c = s->getComponentByName(comp["name"].toString().toStdString());
        int tmp = comp["percent"].toInt();
        qDebug() << "Pourcentage : " << tmp;
       _mapCompo->insert(std::make_pair(c, tmp));
   }
}

Planet::~Planet()
{
}


QJsonArray    Planet::getJson()
{
    return _evo;
}

void    Planet::append(QJsonObject obj)
{
    _evo.append(obj);
}


void    Planet::calc_move(int duree)
{
    int delta = duree % _revo;
    qreal PI = 3.14;
    qreal rad = (2 * PI * delta) / (_revo);

    qreal x =  _distance * qCos(rad);
    qreal y =  _distance * qSin(rad);
    setPosition(x, y, 0);

    QJsonObject evo;
    QJsonObject position;
    position.insert("x", _pos[0]);
    position.insert("y", _pos[1]);
    position.insert("z", _pos[2]);
    evo.insert("pos", position);
    evo.insert("date", duree);
    _evo.append(evo);
}

void    Planet::setName(std::string name)
{
    _name = name;
}

void    Planet::setType(PlanetType type)
{
    _type = type;
}

void    Planet::setRadius(int radius)
{
    _radius = radius;
}

void    Planet::setTilt(int tilt)
{
    _tilt = tilt;
}

void    Planet::setRevo(int revo)
{
    _revo = revo;
}

void    Planet::setDistance(int distance)
{
    _distance = distance;
}

std::string Planet::getName(void)
{
    return (_name);
}

PlanetType  Planet::getType(void)
{
    return (_type);
}

int Planet::getRadius(void)
{
    return (_radius);
}

int Planet::getDistance(void)
{
    return (_distance);
}

int Planet::getRevo(void)
{
    return (_revo);
}

int Planet::getTilt(void)
{
    return (_tilt);
}

void    Planet::init()
{
    _hm = new HeightMap(_radius);
    _hm->PlateTectonic(_radius / RATIO_PLATE + 1, _mapCompo);
    _hm->printMap();
}

void    Planet::initOther()
{
    if (this->getType()== STAR)
        this->_genHMStar();
    else if (this->getType()== GAZEOUS)
        this->_genHMGaz();
    else // asteroid
        this->_genHMAsteroid();
}

void    Planet::_genHMStar(void)
{
    qDebug() << "Generating star...";
}

void    Planet::_genHMGaz(void)
{
    qDebug() << "Generating gazeous planet...";
}

void    Planet::_genHMAsteroid(void)
{
    qDebug() << "Generating asteroid...";
}


std::map<Component*, int> *Planet::getComponentMap(void)
{
    return (_mapCompo);
}

void Planet::setPosition(int X, int Y, int Z)
{
    _mutex.lock();
    _pos[0] = X;
    _pos[1] = Y;
    _pos[2] = Z;
    _mutex.unlock();
}

void    Planet::move(bool b)
{
    _mutex.lock();
    _move = b;
    _mutex.unlock();
}

void    Planet::evolve(bool b)
{
    _evolve = b;
}

int *Planet::getPosition(void)
{
    return _pos;
}

bool    Planet::move(void) const
{
    return _move;
}

bool    Planet::evolve(void) const
{
    return _evolve;
}
