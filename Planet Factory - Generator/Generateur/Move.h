#ifndef MOVE_H
#define MOVE_H

#include <QThread>
#include <QtDebug>

#include "System.h"

class Move : public QThread
{
    Q_OBJECT
public:
    Move(System *);
    void setTime(int);

private:
    void run();
    System * _system;
    int _time;

signals:
    void thread_term();
};

#endif // MOVE_H
