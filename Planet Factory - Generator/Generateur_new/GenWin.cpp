#include "GenWin.hpp"

GenWin::GenWin(System *s, QString path, int time, int inter, QWidget *parent) : QWidget(parent)
{
    _system = s;
    _path = path;
    _time = time;
    _inter = inter;
    _terrains = new std::list<Terrain *>;
    _iteration = 0;
    _thread_term = 0;
    _nb_thread = 0;

    setGeometry(400, 200, 1024, 768);

    //Global progress
    _GlobalText = new QLabel(this);
    _GlobalText->setGeometry(10, 10, 1004, 20);
    _GlobalText->setText("Step 1 of 5");

    _progressGlobal = new QProgressBar(this);
    _progressGlobal->setGeometry(10, 30, 1004, 20);
    _progressGlobal->setTextVisible(false);

    //Number of step
    _progressGlobal->setMaximum(5);
    _progressGlobal->setValue(0);

    //Current Progress
    _CurrentText = new QLabel(this);
    _CurrentText->setGeometry(10, 60, 1004, 20);
    _CurrentText->setText("Initialisation des fichier");

    _progressCurrent = new QProgressBar(this);
    _progressCurrent->setGeometry(10, 80, 1004, 20);
    _progressCurrent->setTextVisible(false);
    //Number of step
    _progressCurrent->setMaximum(1);
    _progressCurrent->setValue(0);


    _textArea = new QScrollArea(this);
    _textInfo = new QLabel(_textArea);
    _textInfo->setText("");
    _textArea->setGeometry(10, 110, 1004, 660);

    show();
}

void GenWin::appendInfo(QString txt)
{
    QString info = _textInfo->text();
    info.append("\n");
    info.append(txt);
    _textInfo->setText(info);
}

void GenWin::launch()
{
    appendInfo("Starting generation...");
    step1();
}

void GenWin::step1()
{
    _system->initJson(_path);
    _progressCurrent->setValue(1);
    step2();
}

void GenWin::step2()
{
    _GlobalText->setText("Step 2 of 5");
    _CurrentText->setText("Generate plate");
    _progressGlobal->setValue(1);
    _progressCurrent->setValue(0);

    //Construction de tout les threads, 1 par planète
    std::list<Planet *>::iterator it;
    for(it = _system->getPlanetList()->begin(); it != _system->getPlanetList()->end(); ++it)
    {
        if ((*it)->getType() == TELLURIC) //Si la planète est telluric
        {
            Terrain *t = new Terrain(*it);
            _terrains->push_front(t);
            connect(t, SIGNAL(step2sign()), this, SLOT(step2prog()));
        }
        else // other object
            (*it)->initOther();
    }
    std::list<Terrain*>::iterator itT;
    for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
    {
        (*itT)->start();
        _nb_thread ++;
    }
    _progressCurrent->setMaximum(_nb_thread);
    //Si aucune plaque a generer etape suivante
    if (_nb_thread == 0)
        connectTerrain();
}

void GenWin::connectTerrain()
{
    std::list<Terrain*>::iterator itT;
    for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
    {
        connect((*itT), SIGNAL(step3sign()), this, SLOT(step3sign()));
    }
}

void GenWin::step2prog()
{
    _thread_term++;
    _progressCurrent->setValue(_progressCurrent->value() + 1);
    if(_thread_term == _nb_thread)
    {
        qDebug() << "Fin de tout les thread";
        _move = new Move(_system);
        connect(_move, SIGNAL(step3sign()), this, SLOT(step3sign()));
        connectTerrain();
    }
}

void GenWin::step3()
{
    Terrain * t;

    qDebug() << "Starting main loop...";
    if (_iteration < _time)
    {/*
        _progress->setValue(_iteration);
        _progress->setMaximum(_time);
        _progress->setLabelText("Iteration de temps");

        qDebug() << "Cycle " << _iteration << "...";
*/
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
        //_progress->hide();
    }
}

void GenWin::step3prog()
{
    _thread_term++;
    _progressCurrent->setValue(_progressCurrent->value() + 1);
    if(_thread_term == _nb_thread)
    {
        qDebug() << "Fin de tout les thread";
        step3();
    }
}



