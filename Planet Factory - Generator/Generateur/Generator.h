#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtDebug>
#include <QProgressDialog>

#include "System.h"
#include "Terrain.h"
#include "Move.h"

class Generator : QObject
{
     Q_OBJECT
public:
    Generator(System *, int time, int inter);
    void run();
    void launch();
private:
    QProgressDialog *_progress;
    System * _system;
//    System * _old; // Save de l'ancien état pour vérif si modification il y a eu
    Move * _move;
    std::list<Terrain*> * _terrains;
    int _time;
    int _iteration;
    int _nb_thread;
    int _thread_term;
    int _inter;
public slots:
    void thread_term();
};

#endif // GENERATOR_H