#include "Generator.h"

Generator::Generator(System * system, int time, int inter)
    :_system(system), _time(time), _inter(inter)
{
    _terrains = new std::list<Terrain *>;
}

int     Generator::run()
{
    qDebug() << "Starting generation...";
    //Construction de tout les threads, 1 par planète, 1 pour les déplacements
    qDebug() << "Creating threads...";
    _move = new Move(_system);
    std::list<Planet *>::iterator it;
    for(it = _system->getPlanetList()->begin(); it != _system->getPlanetList()->end(); ++it)
    {
        _terrains->push_front(new Terrain(*it));
    }
    qDebug() << "Threads creation done...";
    qDebug() << "Starting main loop...";
    for (int i = 0; i < _time; i += _inter)
    {
        qDebug() << "Cycle " << i << "...";
        //Calculez les mouvements
        qDebug() << "Calculating movement...";
        _move->start();
        //Calculez les reliefs
        qDebug() << "Calculating terrains...";
        std::list<Terrain*>::iterator itT;
        for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
        {
            Terrain * t = *itT;
            t->start();
        }
    }
    qDebug() << "Main loop finished...";
    //Ils reçoivent system * et éditent tout les X temps la classe
    // system ou planet
    //Si modivication depuis le dernier état, on écrit dans le
    //fichier, sinon non
    //booléen dans chaque objet pour savoir si il a été modif,
    //mettre en pause tout les threads tant que chaque objet
    //n'aura pas fait un état


    return 0;
}
