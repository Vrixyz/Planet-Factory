#ifndef MOVE_HPP
#define MOVE_HPP

#include <QThread>
#include <QtDebug>

#include "System.hpp"

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
    void step3sign();
};

#endif // MOVE_HPP
