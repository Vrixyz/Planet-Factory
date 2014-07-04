#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "Planet.hpp"

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
    QString                 getJsonPath();

    void                    initJson(QString);
    void                    endJson();
private:
    QString _path;
    std::list<Planet*>      *_listPlanet;
    std::list<Component*>   *_listCompo;
};

#endif // SYSTEM_HPP
