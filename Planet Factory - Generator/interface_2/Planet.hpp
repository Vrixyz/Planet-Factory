#ifndef PLANET_HPP
#define PLANET_HPP

#include <QMutex>

#include <iostream>
#include <list>
#include <map>

#include <QJsonArray>
#include <QJsonObject>

#include "Component.hpp"
#include "Heightmap.h"

class System;

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
    Planet(QJsonObject, System *);
    ~Planet();

    void                    setName(std::string);
    void                    setType(PlanetType);
    void                    setRadius(int);
    void                    setPosition(int, int, int);
    void                    setPositionVec(int, int, int);
    void                    move(bool);
    void                    evolve(bool);
    void                    append(QJsonObject);
    QJsonArray              getJson();

    std::string                 getName(void);
    PlanetType                  getType(void);
    int                         getRadius(void);
    std::map<Component*, int>   *getComponentMap(void);
    int                         *getPosition(void);
    int                         *getPositionVec(void);
    bool                        move(void) const;
    bool                        evolve(void) const;

private:
    QMutex                  _mutex;
    QJsonArray              _evo;
    std::string             _name;
    int                     _radius;
    PlanetType              _type;
    int                     _pos[3];
    int                     _posVec[3];
    bool                    _move;
    bool                    _evolve;

    std::map<Component*, int>   *_mapCompo;
    HeightMap *             _hm;

};

#endif // PLANET_HPP
