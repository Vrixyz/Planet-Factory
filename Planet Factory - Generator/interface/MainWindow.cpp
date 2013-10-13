#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setStyleSheet("QMainWindow { background-image : url(bgcosmos.jpg);} QGroupBox { background-color: rgba(100%, 100%, 100%, 50%);}");

    _boxPlanetDetails = new PlanetDetailsBox(this);
    _boxPlanetCompo = new PlanetCompoBox(this);
    _boxCelestial = new CelestialBox(this);
    _boxOptions = new OptionsBox(this);
}

MainWindow::~MainWindow()
{
}
