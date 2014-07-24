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
    setObjectName("genWin");

    //Global progress
    _GlobalText = new QLabel(this);
    _GlobalText->setGeometry(10, 10, 1004, 20);
    _GlobalText->setText("Step 1 of 4");

    _progressGlobal = new QProgressBar(this);
    _progressGlobal->setGeometry(10, 30, 1004, 20);
    _progressGlobal->setTextVisible(false);

    //Number of step
    _progressGlobal->setMaximum(4);
    _progressGlobal->setValue(0);

    //Current Progress
    _CurrentText = new QLabel(this);
    _CurrentText->setGeometry(10, 60, 1004, 20);
    _CurrentText->setText("Initialisation of file");

    _progressCurrent = new QProgressBar(this);
    _progressCurrent->setGeometry(10, 80, 1004, 20);
    _progressCurrent->setTextVisible(false);
    //Number of step
    _progressCurrent->setMaximum(1);
    _progressCurrent->setValue(0);


    _textArea = new QScrollArea(this);
    _textArea->setObjectName("gen");
    _textInfo = new QTextEdit(_textArea);
    _textInfo->setObjectName("gen");
    _textArea->setGeometry(10, 120, 1004, 635);
    _textInfo->setGeometry(0, 0, 1004, 635);

    show();
}

void GenWin::appendInfo(QString txt)
{
    QString info = _textInfo->toHtml();
    info.append(txt);
    _textInfo->setHtml(info);
}

void GenWin::launch()
{
    _textInfo->setHtml("Starting generation...");
    appendInfo("Step 1 of 4");
    appendInfo("Initialisation of file");
    step1();
}

void GenWin::step1()
{
    appendInfo("Initialize JSON file...");
    _system->initJson(_path);
    _progressCurrent->setValue(1);
    step2();
}

void GenWin::step2()
{
    _GlobalText->setText("Step 2 of 4");
    _CurrentText->setText("Generate plate");
    appendInfo("Step 2 of 4");
    appendInfo("Generate plate");
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
    appendInfo("Number of planet generation: " + QString::number(_nb_thread));
    //Si aucune plaque a generer etape suivante
    if (_nb_thread == 0)
        connectTerrain();
}

void GenWin::connectTerrain()
{
    _GlobalText->setText("Step 3 of 4");
    _CurrentText->setText("Generate Move");
    appendInfo("Step 3 of 4");
    appendInfo("Generate Move");
    _progressGlobal->setValue(2);
    _progressCurrent->setValue(0);
    std::list<Terrain*>::iterator itT;
    for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
    {
        (*itT)->planet()->addHmToEvo(_path);
        (*itT)->planet()->addCmToEvo(_path);
        connect((*itT), SIGNAL(step3sign()), this, SLOT(step3prog()));
    }
    _move = new Move(_system);
    connect(_move, SIGNAL(step3sign()), this, SLOT(step3prog()));
    appendInfo("Time of generation: " + QString::number(_time));
    step3();
}

void GenWin::step2prog()
{
    _thread_term++;
    _progressCurrent->setValue(_progressCurrent->value() + 1);
    if(_thread_term == _nb_thread)
    {
        qDebug() << "End of all threads";
        connectTerrain();
    }
}

void GenWin::step3()
{
    Terrain * t;
    _progressCurrent->setMaximum(_time);

    appendInfo("Generate Move Current Time: " + QString::number(_iteration));
    if (_iteration < _time)
    {
        //Calculez les mouvements
        _thread_term = 0;
        _nb_thread = 0;
        appendInfo("Calculating movement... ");
        _move->setTime(_iteration);
        _move->start();
        _nb_thread ++;

        //Calculez les reliefs
        appendInfo("Calculating grounds... ");
        std::list<Terrain*>::iterator itT;
        for(itT = _terrains->begin(); itT != _terrains->end(); ++itT)
        {
            t = *itT;
            t->start();
            _nb_thread ++;
        }
        appendInfo("Number of thread waiting... " + QString::number(_nb_thread));
        _iteration += _inter;
    }
    else
    {
        step4();
    }
}

void GenWin::step3prog()
{
    _thread_term++;
    _progressCurrent->setValue(_iteration);
    appendInfo("Number of thread end... " + QString::number(_thread_term));

    if(_thread_term == _nb_thread)
    {
        appendInfo("End of all threads");
        step3();
    }
}


void GenWin::step4()
{
    appendInfo("Main loop finished...");
    _GlobalText->setText("Step 4 of 4");
    _CurrentText->setText("Finalise file");
    appendInfo("Step 4 of 4");
    appendInfo("Finalise file");
    _progressGlobal->setValue(3);
    _system->endJson();
    _progressGlobal->setValue(4);
    _progressCurrent->setMaximum(1);
    _progressCurrent->setValue(1);
    appendInfo("End of generation");
}



