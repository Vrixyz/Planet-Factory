#include "System.hpp"

System::System()
{
    _listPlanet = new std::list<Planet *>;
    _listCompo = new std::list<Component *>;
}


System::System(QJsonObject json)
{
    _listPlanet = new std::list<Planet *>;
    _listCompo = new std::list<Component *>;

    //On get la liste des materiaux
    QJsonArray components = json["materials"].toArray();
    foreach (QJsonValue value, components)
    {
        _listCompo->push_front(new Component(value.toObject()));
    }

    //On get les planete
    QJsonArray astres = json["astres"].toArray();
    foreach (QJsonValue value, astres)
    {
        _listPlanet->push_front(new Planet(value.toObject(), this));
    }
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

Component *System::getComponentByName(std::string toSearch)
{
    std::list<Component*>::iterator it;

    for (it = getComponentList()->begin(); it != getComponentList()->end(); ++it)
    {
        if ((*it)->getName() == toSearch)
            return (*it);
    }
    return NULL;
}

QString System::getTypeString(Planet *p)
{
    switch (p->getType())
    {
    case STAR:
        return "star";
    case TELLURIC:
        return "planet";
    case GAZEOUS:
        return "gazeous";
    case ASTEROID:
        return "asteroid";
    default:
        return "bad type";
    }
}

// TODO A MODIFIER SOON
void System::initJson(QString path)
{
    _path = path;
    std::list<Planet*>::iterator itp;

    QJsonArray planete;
    for (itp = _listPlanet->begin(); itp != _listPlanet->end(); ++itp)
    {
        QString name = (*itp)->getName().c_str();

        QDir dir(path + "/" + name);
        if (!dir.exists())
          dir.mkdir(path + "/" + name);
        planete.append("./" + name + ".json");

        //Infos fixe
        QJsonObject astre;
        astre.insert("name", name);
        astre.insert("type", getTypeString(*itp));
        astre.insert("evolution",  "./" + name + "_evolution.json");

        QJsonDocument astre_json;
        astre_json.setObject(astre);
        QFile astre_file;
        astre_file.setFileName(path + "/" + name + ".json");
        astre_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        astre_file.write(astre_json.toJson());
        astre_file.close();
        /**
        **  Les infos fixe sont ecrites dans un fichier.
        **  Les evolutions sont ajouter dans un objet mais pas ecrite pour le moment.
        **
        **/

        //Evolution
        QJsonObject evo;
        evo.insert("radius", (*itp)->getRadius());
        evo.insert("date", 0);
        (*itp)->append(evo);
    }

    std::list<Component*>::iterator itc;
    //On cree l'array component
    QJsonObject component;
    for (itc = _listCompo->begin(); itc != _listCompo->end(); ++itc)
    {
        QJsonObject obj;

        QString name = (*itc)->getName().c_str();

        obj.insert("solid", (*itc)->getSolidTemp());
        obj.insert("gas", (*itc)->getGazeousTemp());
        obj.insert("mass", (*itc)->getMass());
        obj.insert("hardness", (*itc)->getHardness());
        component.insert(name, obj);
    }

    QJsonObject save;
    save.insert("materials", component);
    save.insert("astres", planete);

    //write
    QJsonDocument json;
    json.setObject(save);
    QFile file;
    file.setFileName(path + "/systeme.json");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(json.toJson());
    file.close();
}

QString System::getJsonPath()
{
    return _path;
}

void System::endJson()
{
    QString path = _path;
    std::list<Planet*>::iterator itp;

    for (itp = _listPlanet->begin(); itp != _listPlanet->end(); ++itp)
    {
        QString name = (*itp)->getName().c_str();

        QJsonObject save;
        save.insert("evolutions", (*itp)->getJson());

        QJsonDocument astre_json;
        astre_json.setObject(save);

        QFile astre_file;
        astre_file.setFileName(path + "/" + name + "_evolution.json");
        astre_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        astre_file.write(astre_json.toJson());
        astre_file.close();
    }
}
