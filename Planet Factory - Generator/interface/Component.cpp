#include "Component.hpp"

Component::Component()
{
}

Component::~Component()
{
}

std::string Component::getName(void)
{
    return (_name);
}

int Component::getSolidTemp(void)
{
    return (_solidTemp);
}

int Component::getHardness(void)
{
    return (_hardness);
}

int Component::getGazTemp(void)
{
    return (_gazTemp);
}

int Component::getPercent(void)
{
    return (_percent);
}

int Component::getMass(void)
{
    return (_mass);
}

void    Component::setName(std::string name)
{
    _name = name;
}

void    Component::setSolidTemp(int solidTemp)
{
    _solidTemp = solidTemp;
}

void    Component::setHardness(int hardness)
{
    _hardness = hardness;
}

void    Component::setPercent(int percent)
{
    _percent = percent;
}

void    Component::setGazTemp(int gazTemp)
{
    _gazTemp = gazTemp;
}

void    Component::setMass(int mass)
{
    _mass = mass;
}
