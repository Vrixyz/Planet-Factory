#ifndef SYSTEM_H
#define SYSTEM_H

#include "Planet.hpp"

class System
{

public:

    System();
    ~System();

    void                    setPlanetList(std::list<Planet*>*);
    void                    setComponentList(std::list<Component*>*);
    std::list<Planet*>      *getPlanetList(void);
    std::list<Component*>   *getComponentList(void);

private:

    std::list<Planet*>      *_listPlanet;
    std::list<Component*>   *_listCompo;

};

#endif // SYSTEM_H
