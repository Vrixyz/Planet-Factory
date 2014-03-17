#include "Generator.h"

Generator::Generator(System * system)
    :_system(system)
{
    _terrains = new std::list<Terrain *>;
}

int     Generator::run()
{
    //Construction de tout les threads, 1 par planète, 1 pour les déplacements
    _move = new Move(_system);
    std::list<Planet *>::iterator i;
    for(i = _system->getPlanetList()->begin(); i != _system->getPlanetList()->end(); ++i)
    {
        _terrains->push_front(new Terrain(*i));
    }

    //Ils reçoivent system * et éditent tout les X temps la classe System, mutex
    //SI modivication depuis le dernier état, on écrit dans le fichier, sinon non
    //booléen dans chaque objet pour savoir si il a été modif, mettre en pause tout les threads tant que chaque objet n'aura pas fait un état


    return 0;
}
