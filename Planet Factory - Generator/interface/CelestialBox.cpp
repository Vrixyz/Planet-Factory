#include "CelestialBox.hpp"
#include "MainWindow.hpp"

CelestialBox::CelestialBox(MainWindow *parent) : QGroupBox(parent)
{
    setGeometry(5, 105, 295, 295);
    setTitle("Celestial objects");

    _parent = parent;
    _listObjects = new QListWidget(this);
    _listObjects->setGeometry(10, 30, 275, 225);

    _add = new QPushButton(this);
    _del = new QPushButton(this);
    _add->setGeometry(10, 260, 135, 30);
    _del->setGeometry(150, 260, 135, 30);
    _add->setText("Add");
    _del->setText("Delete");

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(addObject()));
    QObject::connect(_del, SIGNAL(clicked()), qApp, SLOT(quit()));
}

CelestialBox::~CelestialBox()
{
}

void CelestialBox::addObject()
{
    Planet *toAdd;

    toAdd = new Planet();
    _parent->getPlanetDetails()->setInfosDetails(toAdd);
    _parent->_listPlanet->push_front(toAdd);
    _listObjects->addItem(QString(toAdd->getName().c_str()));
}
