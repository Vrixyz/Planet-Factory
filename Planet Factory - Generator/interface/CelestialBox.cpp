#include "CelestialBox.hpp"

CelestialBox::CelestialBox(QWidget *parent) : QGroupBox(parent)
{
    setGeometry(5, 105, 295, 295);
    setTitle("Celestial objects");

    _listObjects = new QListView(this);
    _listObjects->setGeometry(10, 30, 275, 225);

    _add = new QPushButton(this);
    _del = new QPushButton(this);
    _add->setGeometry(10, 260, 135, 30);
    _del->setGeometry(150, 260, 135, 30);
    _add->setText("Add");
    _del->setText("Delete");
}

CelestialBox::~CelestialBox()
{
}
