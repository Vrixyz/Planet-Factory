#ifndef TERRAIN_H
#define TERRAIN_H

#include <QThread>
#include "Planet.hpp"

class Terrain : public QThread
{
    Q_OBJECT
public:
    Terrain(Planet *);

private:
    void run();
    Planet * _planet;
};

#endif // TERRAIN_H
