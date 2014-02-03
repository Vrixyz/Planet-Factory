#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <list>
#include <map>

#include "Component.hpp"
#include <QJsonArray>
#include <QJsonObject>

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
    void                    setPosition(int, int, int);
    void                    setPositionVec(int, int, int);
    void                    append(QJsonObject);
    QJsonArray              getJson();

    std::string                 getName(void);
    PlanetType                  getType(void);
    int                         getRadius(void);
    std::map<Component*, int>   *getComponentMap(void);
    int                         *getPosition(void);
    int                         *getPositionVec(void);

private:

    QJsonArray              _evo;
    std::string             _name;
    int                     _radius;
    PlanetType              _type;
    int                     _pos[3];
    int                     _posVec[3];

    std::map<Component*, int>   *_mapCompo;

};

#endif // PLANET_HPP
