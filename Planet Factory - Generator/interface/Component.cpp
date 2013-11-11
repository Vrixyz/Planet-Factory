#include "Component.hpp"

Component::Component()
{
}

Component::Component(std::string name, int gazeousTemp, int solidTemp, int mass, int hardness)
{
    _name = name;
    _gazeousTemp = gazeousTemp;
    _solidTemp = solidTemp;
    _hardness = hardness;
    _mass = mass;
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
