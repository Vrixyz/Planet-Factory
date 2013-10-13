#include "PlanetCompoBox.hpp"

PlanetCompoBox::PlanetCompoBox(QWidget *parent) : QGroupBox(parent)
{
    setGeometry(205, 405, 790, 290);
    setTitle("Planet Composition");

    _boxDetails = new GroupTools(parent);
    _boxDetails->setGeometry(605, 435, 380, 250);
    _boxDetails->setTitle("Composition Detail");

    _boxList = new GroupTools(parent);
    _boxList->setGeometry(215, 435, 380, 250);
    _boxList->setTitle("Composition List");

}

PlanetCompoBox::~PlanetCompoBox()
{
}
