#include "Move.h"

Move::Move(System * system) :_system(system)
{
    _time = 0;
}

void    Move::setTime(int t)
{
    _time = t;
}

void    Move::run()
{
    qDebug() << "Moving...";

    std::list<Planet*> *list = _system->getPlanetList();
    std::list<Planet*>::iterator itp;
    for (itp = list->begin(); itp != list->end(); ++itp)
    {
        (*itp)->calc_move(_time);
    }
    emit thread_term();
}
