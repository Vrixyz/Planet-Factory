#include "Planet.hpp"

Planet::Planet()
{
    _mapCompo = new std::map<Component*, int>();
}

Planet::~Planet()
{
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
    _pos[0] = X;
    _pos[1] = Y;
    _pos[2] = Z;
}

void Planet::setPositionVec(int X, int Y, int Z)
{
    _posVec[0] = X;
    _posVec[1] = Y;
    _posVec[2] = Z;
}

int *Planet::getPosition(void)
{
    return _pos;
}

int *Planet::getPositionVec(void)
{
    return _posVec;
}
