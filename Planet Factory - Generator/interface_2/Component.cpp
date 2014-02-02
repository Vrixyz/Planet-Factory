#include "Component.hpp"

Component::Component()
{
}

Component::Component(const std::string & path)
    :_name(""), _gazeousTemp(0), _solidTemp(0), _hardness(0), _mass(0), _path(path)
{
}

Component::Component(std::string name, int gazeousTemp, int solidTemp, int mass, int hardness, const std::string & path)
    : _path(path)
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

void Component::setPercent(int percent)
{
    _percent = percent;
}

void Component::setMass(int mass)
{
    _mass = mass;
}

void    Component::path(const std::string & path)
{
    _path = path;
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

int Component::getPercent(void)
{
    return (_percent);
}

int Component::getMass(void)
{
    return (_mass);
}

const std::string & Component::path(void)
{
    return _path;
}