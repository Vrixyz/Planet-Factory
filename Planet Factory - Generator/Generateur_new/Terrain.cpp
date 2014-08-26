#include "Terrain.hpp"

Terrain::Terrain(Planet * planet)
    :_planet(planet)
{
    _init = false;
}

void    Terrain::run()
{
    qDebug() << "Running " << _planet->getName() << "...";
    if (_init == false)
    {
        //Init Planet
        qDebug() << "Initialization of the planet...";
        _planet->init();
        _init = true;
        qDebug() << "Initialization of the planet : Done.";
        emit step2sign();
    }
    else
    {
        //Gen terrain
        qDebug() << "Generating terrain...";
        _planet->getHeightMap()->terrain();
        qDebug() << "Generating terrain : Done.";
        emit step3sign();
    }

}

Planet * Terrain::planet(void) const
{
    return _planet;
}
