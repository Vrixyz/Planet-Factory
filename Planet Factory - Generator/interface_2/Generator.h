#ifndef GENERATOR_H
#define GENERATOR_H

#include "System.h"
#include "Terrain.h"
#include "Move.h"

class Generator
{
public:
    Generator(System *);
    int run();
private:
    System * _system;
    System * _old; // Save de l'ancien état pour vérif si modification il y a eu
    Move * _move;
    std::list<Terrain*> * _terrains;
};

#endif // GENERATOR_H