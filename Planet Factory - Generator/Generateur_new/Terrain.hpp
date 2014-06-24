#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <QThread>
#include <QtDebug>

#include "Planet.hpp"

class Terrain : public QThread
{
    Q_OBJECT
public:
    Terrain(Planet *);
    Planet * planet(void) const;
private:
    void run();
    bool _init;
    Planet * _planet;

signals:
    void thread_term();
};

#endif // TERRAIN_HPP
