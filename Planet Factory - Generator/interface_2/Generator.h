#ifndef GENERATOR_H
#define GENERATOR_H

#include "System.h"

class Generator
{
public:
    Generator(System *);
    int run();
private:
    System * _system;
};

#endif // GENERATOR_H
