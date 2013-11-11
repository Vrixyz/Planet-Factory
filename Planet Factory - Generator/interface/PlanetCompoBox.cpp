#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QGroupBox(parent)
{
    setGeometry(205, 405, 790, 290);
    setTitle("Planet Composition");

    _boxDetails = new GroupTools(parent);
    _boxDetails->setGeometry(605, 435, 380, 250);
    _boxDetails->setTitle("Composition Detail");

    _boxList = new GroupTools(parent);
    _boxList->setGeometry(215, 435, 380, 250);
    _boxList->setTitle("Composition List");

    createCompoDetails();
    createCompoList();
}

PlanetCompoBox::~PlanetCompoBox()
{
}

void PlanetCompoBox::createCompoDetails(void)
{ 
    _lName = new QLabel("Name :", _boxDetails);
    _lName->setGeometry(10, 45, 80, 15);
    _lSolidTemp = new QLabel("Solid < ", _boxDetails);
    _lSolidTemp->setGeometry(10, 85, 80, 15);
    _lGazeousTemp = new QLabel("Gazeous > ", _boxDetails);
    _lGazeousTemp->setGeometry(10, 125, 80, 15);
    _lMass = new QLabel("Mass :", _boxDetails);
    _lMass->setGeometry(10, 165, 80, 15);
    _lHardness = new QLabel("Hardness :", _boxDetails);
    _lHardness->setGeometry(10, 205, 80, 15);
}

void PlanetCompoBox::createCompoList(void)
{

}
