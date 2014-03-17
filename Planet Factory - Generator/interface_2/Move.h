#ifndef MOVE_H
#define MOVE_H

#include <QThread>
#include "System.h"

class Move : public QThread
{
    Q_OBJECT
public:
    Move(System *);

private:
    void run();
    System * _system;
};

#endif // MOVE_H
