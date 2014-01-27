#include "System.h"

System::System()
{
    _listPlanet = new std::list<Planet *>;
    _listCompo = new std::list<Component *>;
}

System::~System()
{
}

void System::setPlanetList(std::list<Planet*> *list)
{
    _listPlanet = list;
}

void System::setComponentList(std::list<Component*> *list)
{
    _listCompo = list;
}

std::list<Planet*> *System::getPlanetList(void)
{
    return _listPlanet;
}

std::list<Component*> *System::getComponentList(void)
{
    return _listCompo;
}
