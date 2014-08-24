#include "Component.hpp"

Component::Component()
{
}


Component::Component(QJsonObject obj)
{
    _name = obj["name"].toString().toStdString();
    _gazeousTemp = obj["gas"].toInt();
    _solidTemp = obj["solid"].toInt();
    _mass = obj["mass"].toInt();
    _color1 = obj["minColor"].toString().toStdString();
    _color2 = obj["maxColor"].toString().toStdString();
}

Component::Component(const std::string & path)
    :_name(""), _gazeousTemp(0), _solidTemp(0), _mass(0), _path(path)
{
}

Component::Component(Component *c)
{
    _name = c->getName();
    _gazeousTemp = c->getGazeousTemp();
    _solidTemp = c->getSolidTemp();
    _mass = c->getMass();
    _path = c->path();
}

Component::Component(std::string name, int gazeousTemp, int solidTemp, int mass, const std::string & path)
    : _path(path)
{
    _name = name;
    _gazeousTemp = gazeousTemp;
    _solidTemp = solidTemp;
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

int Component::getMass(void)
{
    return (_mass);
}

const std::string & Component::path(void)
{
    return _path;
}

void Component::setColor1(std::string color)
{
    _color1 = color;
}

void Component::setColor2(std::string color)
{
    _color2 = color;
}

std::string Component::getColor1(void)
{
    return _color1;
}

std::string Component::getColor2(void)
{
    return _color2;
}
