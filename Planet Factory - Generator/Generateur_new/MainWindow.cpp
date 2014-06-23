#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _menu = new Menu(this);
    _celestialBox = new CelestialBox(this);
    _planetCompoBox = new PlanetCompoBox(this);
    _planetDetailsBox = new PlanetDetailsBox(this);
}

MainWindow::~MainWindow()
{
}
