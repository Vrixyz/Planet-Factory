#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <list>

#include "Component.hpp"

enum PlanetType
{
    STAR,
    TELLURIC,
    GAZEOUS,
    ASTEROID
};

class Planet
{

public:

    Planet();
    ~Planet();

    void                    setName(std::string);
    void                    setType(PlanetType);
    void                    setRadius(int);

    std::string             getName(void);
    PlanetType              getType(void);
    int                     getRadius(void);
    std::list<Component*>   *getListCompo(void);

private:

    std::string             _name;
    int                     _radius;
    PlanetType              _type;
    std::list<Component*>   *_listCompo;

};

#endif // PLANET_HPP
