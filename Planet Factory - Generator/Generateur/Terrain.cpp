#include "Terrain.h"

Terrain::Terrain(Planet * planet)
    :_planet(planet)
{
    _init = false;
}

void    Terrain::run()
{
    qDebug() << "Running " << _planet->getName().c_str() << "...";
    if (_init)
    {
        //CODE DES TERRAINS
    }
    else
    {
        _planet->init();
        _init = true;
    }
    emit thread_term();
}

Planet * Terrain::planet(void) const
{
    return _planet;
}
