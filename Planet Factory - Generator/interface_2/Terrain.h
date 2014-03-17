#ifndef TERRAIN_H
#define TERRAIN_H

#include <QThread>

class Terrain : public QThread
{
    Q_OBJECT
private:
    void run();
};

#endif // TERRAIN_H
