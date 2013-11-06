#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setStyleSheet("QMainWindow { background-image : url(bgcosmos.jpg);} QGroupBox { background-color: rgba(100%, 100%, 100%, 50%);}");

    _boxPlanetDetails = new PlanetDetailsBox(this);
    _boxPlanetCompo = new PlanetCompoBox(this);
    _boxCelestial = new CelestialBox(this);
    _boxOptions = new OptionsBox(this);

    _listPlanet = new std::list<Planet*>;
}

MainWindow::~MainWindow()
{
}

PlanetDetailsBox    *MainWindow::getPlanetDetails(void)
{
    return (_boxPlanetDetails);
}

PlanetCompoBox      *MainWindow::getPlanetCompo(void)
{
    return (_boxPlanetCompo);
}

CelestialBox        *MainWindow::getCelestial(void)
{
    return (_boxCelestial);
}

OptionsBox          *MainWindow::getOptions(void)
{
    return (_boxOptions);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        qApp->quit();
}
