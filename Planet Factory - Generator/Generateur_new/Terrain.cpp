#include "Terrain.hpp"

Terrain::Terrain(Planet * planet)
    :_planet(planet)
{
    _init = false;
}

void    Terrain::run()
{
    qDebug() << "Running " << _planet->getName().c_str() << "...";
    if (_init == false)
    {
        //Init Planet
        qDebug() << "Initialization of the planet...";
        _planet->init();
        _init = true;
        qDebug() << "Initialization of the planet : Done.";
    }
    else
    {
        //Gen terrain
        qDebug() << "Generating terrain...";
        _planet->getHeightMap()->terrain();

        //Create temp int ** to export heigtmap
        int ** tmp;

        //Export heightmap
        std::string path = "";
        std::string name = "";
        _planet->getHeightMap()->exportHeightmap(tmp, path, name);
        qDebug() << "Generating terrain : Done.";
    }
    emit thread_term();
}

Planet * Terrain::planet(void) const
{
    return _planet;
}
