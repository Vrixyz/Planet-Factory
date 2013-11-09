#include "Component.hpp"

Component::Component()
{
}

Component::~Component()
{
}

void Component::setName(std::string name)
{
    _name = name;
}

void Component::setGazeousTemp(int gazeousTemp)
{
    _gazeousTemp = gazeousTemp;
}

void Component::setSolidTemp(int solidTemp)
{
    _solidTemp = solidTemp;
}

void Component::setHardness(int hardness)
{
    _hardness = hardness;
}

void Component::setMass(int mass)
{
    _mass = mass;
}

std::string Component::getName(void)
{
    return (_name);
}

int Component::getGazeousTemp(void)
{
    return (_gazeousTemp);
}

int Component::getSolidTemp(void)
{
    return (_solidTemp);
}

int Component::getHardness(void)
{
    return (_hardness);
}

int Component::getMass(void)
{
    return (_mass);
}
