#ifndef SYSTEM_H
#define SYSTEM_H

#include "Planet.hpp"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>

class System
{

public:

    System();
    System(QJsonObject);
    ~System();

    void                    setPlanetList(std::list<Planet*>*);
    void                    setComponentList(std::list<Component*>*);
    std::list<Planet*>      *getPlanetList(void);
    std::list<Component*>   *getComponentList(void);
    Component               *getComponentByName(std::string);

    void                    initJson(QString);
    void                    endJson(QString);
private:

    std::list<Planet*>      *_listPlanet;
    std::list<Component*>   *_listCompo;
};

#endif // SYSTEM_H
