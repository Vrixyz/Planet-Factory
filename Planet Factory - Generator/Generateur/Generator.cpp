#include "Generator.h"

Generator::Generator(System *system, int time, int inter):_system(system), _time(time), _inter(inter)
{
    _iteration = 0;
    _terrains = new std::list<Terrain *>;

    qDebug() << "Starting generation...";

    //Construction de tout les threads, 1 par planète, 1 pour les déplacements
    qDebug() << "Creating threads...";
    _move = new Move(_system);
    connect(_move, SIGNAL(thread_term()), this, SLOT(thread_term()));

    std::list<Planet *>::iterator it;
    for(it = _system->getPlanetList()->begin(); it != _system->getPlanetList()->end(); ++it)
    {
        if ((*it)->getType() == TELLURIC) //Si la planète est telluric
        {
            Terrain *t = new Terrain(*it);
            _terrains->push_front(t);
            connect(t, SIGNAL(thread_term()), this, SLOT(thread_term()));
        }
        else // other object
            (*it)->initOther();
    }
    qDebug() << "Threads creation done...";
}

void     Generator::launch()
{
    _progress = new QProgressDialog("Generation des plaques", "Cancel", 0, _terrains->size());
    _progress->setWindowFlags(_progress->windowFlags() & ~Qt::WindowCloseButtonHint);
    _progress->setCancelButton(0);
    _progress->show();

    //Un threat par planete
    _thread_term = 0;
    _nb_thread = 0;


    qDebug() << "Calculating terrains...";
    std::list<Terrain*>::iterator itT;
    for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
    {
        (*itT)->start();
        _nb_thread ++;
    }
    if (_nb_thread == 0)
        run();
}

//Ils reçoivent system * et éditent tout les X temps la classe
// system ou planet
//Si modivication depuis le dernier état, on écrit dans le
//fichier, sinon non
//booléen dans chaque objet pour savoir si il a été modif,
//mettre en pause tout les threads tant que chaque objet
//n'aura pas fait un état
void     Generator::run()
{
    Terrain * t;

    qDebug() << "Starting main loop...";
    if (_iteration < _time)
    {
        _progress->setValue(_iteration);
        _progress->setMaximum(_time);
        _progress->setLabelText("Iteration de temps");

        qDebug() << "Cycle " << _iteration << "...";

        //Calculez les mouvements
        _thread_term = 0;
        _nb_thread = 0;

        qDebug() << "Calculating movement...";
        _move->setTime(_iteration);
        _move->start();
        _nb_thread ++;


        //Calculez les reliefs
        qDebug() << "Calculating terrains...";
        std::list<Terrain*>::iterator itT;
        for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
        {
            t = *itT;
            t->start();
            _nb_thread ++;
        }


        //ecoulement du temps
        _iteration += _inter;
    }
    else
    {
        //FIN de la generation.
        qDebug() << "Main loop finished...";
        _system->endJson();
        _progress->hide();
    }
}


void Generator::thread_term()
{
    _thread_term++;

     qDebug() << "THREAD TERM";

    if(_thread_term == _nb_thread)
    {
        qDebug() << "Fin de tout les thread";
        run();
    }
}
