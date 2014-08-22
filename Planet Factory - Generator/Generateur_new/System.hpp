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
    void                    setCentralStar(Planet*);
    Planet                  *getCentralStar(void);
    std::list<Planet*>      *getPlanetList(void);
    std::list<Component*>   *getComponentList(void);
    Component               *getComponentByName(std::string);
    QString                 getJsonPath();
    QString                 getTypeString(Planet *p);

    void                    initJson(QString);
    void                    endJson();
private:
    QString _path;
    std::list<Planet*>      *_listPlanet;
    std::list<Component*>   *_listCompo;
    Planet                  *_centralStar;
};

#endif // SYSTEM_HPP
