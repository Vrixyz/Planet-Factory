#include "Planet.hpp"
#include "System.hpp"

Planet::Planet(System* s)
    :_move(false), _evolve(false)
{
    _mapCompo = new std::map<Component*, int>();
    _mapIteration = 0;
    _system = s;
}

Planet::Planet(QJsonObject obj, System* s) :_move(false), _evolve(false)
{
    _mapCompo = new std::map<Component*, int>(); 
    _system = s;
    //On get les infos du fichier Json
    int type = obj["type"].toInt();
    switch (type)
    {
        case STAR:
            _type = STAR;
        break;

        case TELLURIC:
            _type = TELLURIC;
        break;

        case GAZEOUS:
            _type = GAZEOUS;
        break;

        case ASTEROID:
            _type = ASTEROID;
        break;
    }
    _name = obj["name"].toString().toStdString();
    _radius = obj["radius"].toInt();
    _tilt = obj["tilt"].toInt();
    _distance = obj["distance"].toInt();
    _revo = obj["period"].toInt();
    _rota = obj["rota"].toInt();

    _mapIteration = 0;

    _pos[0] = 0;
    _pos[1] = 0;
    _pos[2] = 0;

    QJsonArray composant = obj["composant"].toArray();
    foreach (QJsonValue value, composant)
    {
        QJsonObject comp = value.toObject();
        Component *c = s->getComponentByName(comp["name"].toString().toStdString());
        _mapCompo->insert(std::make_pair(c, comp["percent"].toInt()));
    }
}

Planet::~Planet()
{
}




QJsonArray    Planet::getJson()
{
    return _evo;
}

void    Planet::append(QJsonObject obj)
{
    _evo.append(obj);
}


void    Planet::calc_move(int duree)
{
    int delta = duree % _revo;
    qreal PI = 3.14;
    qreal rad = (2 * PI * delta) / (_revo);

    qreal x =  _distance * qCos(rad);
    qreal y =  _distance * qSin(rad);
    setPosition(x, y, 0);


    //End of calc
    QJsonObject position;
    position.insert("x", _pos[0]);
    position.insert("y", _pos[1]);
    position.insert("z", _pos[2]);

    QJsonObject last;
    last = _evo.last().toObject();
    int test = last["duree"].toInt();

    if (test == duree)
    {
        last.insert("pos", position);
        _evo.pop_back();
        _evo.append(last);
    }
    else
    {
        QJsonObject evo;
        evo.insert("pos", position);
        evo.insert("date", duree);
        _evo.append(evo);
    }
}

void    Planet::addHmToEvo(QString path)
{
    QString folder = _name.c_str();
    QString file = "Displacement" + QString::number(_mapIteration);
    QJsonObject evo = _evo.last().toObject();

    _mapIteration++;
    _evo.pop_back();
    _hm->exportHeightMap(path.toStdString()+"/"+_name, file.toStdString());
    evo.insert("displacement", folder+"/"+file);
    _evo.append(evo);
}

void    Planet::addCmToEvo(QString path)
{
    QString folder = _name.c_str();
    QJsonObject evo = _evo.last().toObject();

    _evo.pop_back();
    evo = _hm->exportComposentMap(path.toStdString()+"/"+_name, _mapIteration, evo, folder);
    _evo.append(evo);
}


void    Planet::setName(std::string name)
{
    _name = name;
}

void    Planet::setType(PlanetType type)
{
    _type = type;
}

void    Planet::setRadius(int radius)
{
    _radius = radius;
}

void    Planet::setTilt(int tilt)
{
    _tilt = tilt;
}

void    Planet::setRevo(int revo)
{
    _revo = revo;
}

void    Planet::setRota(int rota)
{
    _rota = rota;
}

void    Planet::setDistance(int distance)
{
    _distance = distance;
}

std::string Planet::getName(void)
{
    return (_name);
}

PlanetType  Planet::getType(void)
{
    return (_type);
}

int Planet::getRadius(void)
{
    return (_radius);
}

int Planet::getDistance(void)
{
    return (_distance);
}

int Planet::getRevo(void)
{
    return (_revo);
}

int Planet::getRota(void)
{
    return (_rota);
}

int Planet::getTilt(void)
{
    return (_tilt);
}

void    Planet::init()
{
    _hm = new HeightMap(_radius, this);
    _hm->PlateTectonic(_radius / RATIO_PLATE + 1, _mapCompo);
    //_hm->printMap();
    //_evolve = true;
}

void    Planet::initOther()
{
    if (this->getType()== STAR)
        this->_genHMStar();
    else if (this->getType()== GAZEOUS)
        this->_genHMGaz();
    else // asteroid
        this->_genHMAsteroid();
}

void    Planet::_genHMStar(void)
{
    qDebug() << "Generating star...";
}

void    Planet::_genHMGaz(void)
{
    qDebug() << "Generating gazeous planet...";
}

void    Planet::_genHMAsteroid(void)
{
    qDebug() << "Generating asteroid...";
}


std::map<Component*, int> *Planet::getComponentMap(void)
{
    return (_mapCompo);
}

HeightMap *             Planet::getHeightMap(void)
{
    return _hm;
}

void Planet::setPosition(int X, int Y, int Z)
{
    _mutex.lock();
    _pos[0] = X;
    _pos[1] = Y;
    _pos[2] = Z;
    _mutex.unlock();
}

void    Planet::move(bool b)
{
    _mutex.lock();
    _move = b;
    _mutex.unlock();
}

void    Planet::evolve(bool b)
{
    _evolve = b;
}

int *Planet::getPosition(void)
{
    return _pos;
}

bool    Planet::move(void) const
{
    return _move;
}

bool    Planet::evolve(void) const
{
    return _evolve;
}
