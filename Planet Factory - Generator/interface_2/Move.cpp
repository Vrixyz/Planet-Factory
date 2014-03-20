#include "Move.h"

Move::Move(System * system)
    :_system(system)
{
}

void    Move::run()
{
    qDebug() << "Moving...";
}
