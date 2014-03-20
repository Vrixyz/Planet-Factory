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

   QJsonObject vec = obj["vec"].toObject();
   _posVec[0] = vec["x"].toInt();
   _posVec[1] = vec["y"].toInt();
   _posVec[2] = vec["z"].toInt();

   QJsonObject pos = obj["pos"].toObject();
   _pos[0] = pos["x"].toInt();
   _pos[1] = pos["y"].toInt();
   _pos[2] = pos["z"].toInt();

   QJsonArray composant = obj["composant"].toArray();
   foreach (QJsonValue value, composant)
   {
        QJsonObject comp = value.toObject();
        Component *c = s->getComponentByName(comp["name"].toString().toStdString());

       _mapCompo->insert(std::make_pair(c, comp["percent"].toInt()));
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

void Planet::setPositionVec(int X, int Y, int Z)
{
    _posVec[0] = X;
    _posVec[1] = Y;
    _posVec[2] = Z;
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

int *Planet::getPositionVec(void)
{
    return _posVec;
}

bool    Planet::move(void) const
{
    return _move;
}

bool    Planet::evolve(void) const
{
    return _evolve;
}
