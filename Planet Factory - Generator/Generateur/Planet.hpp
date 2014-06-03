#ifndef PLANET_HPP
#define PLANET_HPP

#include <QMutex>

#include <iostream>
#include <list>
#include <map>

#include <QJsonArray>
#include <QJsonObject>
#include <QtCore/qmath.h>

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
    void                        calc_move(int);
    void                        append(QJsonObject);
    QJsonArray                  getJson();
    void                        init(void);
    void                        initOther(void);
    std::map<Component*, int>   *getComponentMap(void);

    //GETTER SETTER
    bool                    move(void) const;
    bool                    evolve(void) const;

    void                    move(bool);
    void                    evolve(bool);

    //
    void                    setName(std::string);
    std::string             getName(void);
    void                    setType(PlanetType);
    PlanetType              getType(void);
    void                    setRadius(int);
    int                     getRadius(void);
    void                    setDistance(int);
    int                     getDistance(void);
    void                    setRevo(int);
    int                     getRevo(void);
    void                    setTilt(int);
    int                     getTilt(void);
    void                    setPosition(int, int, int);
    int                     *getPosition(void);

private:
    void                    _genHMStar(void);
    void                    _genHMGaz(void);
    void                    _genHMAsteroid(void);

    QMutex                  _mutex;
    QJsonArray              _evo;
    std::string             _name;
    int                     _radius;
    int                     _distance;
    int                     _tilt;
    int                     _revo;
    PlanetType              _type;
    int                     _pos[3];
    bool                    _move;
    bool                    _evolve;

    std::map<Component*, int>   *_mapCompo;
    HeightMap *             _hm;

};

#endif // PLANET_HPP
