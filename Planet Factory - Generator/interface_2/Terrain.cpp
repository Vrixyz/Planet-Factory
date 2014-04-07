#include "Terrain.h"

Terrain::Terrain(Planet * planet)
    :_planet(planet)
{
}

void    Terrain::run()
{
    qDebug() << "Running " << _planet->getName().c_str() << "...";
}

Planet * Terrain::planet(void) const
{
    return _planet;
}
