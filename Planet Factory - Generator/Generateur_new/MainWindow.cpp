#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    _currPlanet = NULL;
    _system = new System();

    _menu = new Menu(this);
    _boxCelestial = new CelestialBox(this);
    _boxPlanetDetails = new PlanetDetailsBox(this);
    _boxPlanetCompo = new PlanetCompoBox(this);
}

MainWindow::~MainWindow()
{
}

PlanetDetailsBox    *MainWindow::getPlanetDetails(void)
{
    return _boxPlanetDetails;
}

PlanetCompoBox      *MainWindow::getPlanetCompo(void)
{
    return _boxPlanetCompo;
}

CelestialBox        *MainWindow::getCelestial(void)
{
    return _boxCelestial;
}

Menu                *MainWindow::getMenu(void)
{
    return _menu;
}

System              *MainWindow::getSystem()
{
    return _system;
}


void                MainWindow::setSystem(System *s)
{
   _system = s;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        qApp->quit();
}
