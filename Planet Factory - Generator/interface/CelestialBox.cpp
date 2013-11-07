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
    _add->setText("Add / Edit");
    _del->setText("Delete");

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(addObject()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delObject()));
    QObject::connect(_listObjects, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(planetSelected(QListWidgetItem*)));
}

CelestialBox::~CelestialBox()
{
}

void CelestialBox::planetSelected(QListWidgetItem* currItem)
{
    qDebug(currItem->text().toStdString().c_str());
}

void CelestialBox::delObject()
{
    if (_listObjects->currentItem() != NULL)
    {
        std::list<Planet*>::iterator it;

        it = _parent->_listPlanet->begin();
        for (it = _parent->_listPlanet->begin(); it != _parent->_listPlanet->end(); ++it)
        {
            if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
                it = _parent->_listPlanet->erase(it);
        }
        _listObjects->takeItem(_listObjects->row(_listObjects->currentItem()));
    }
}

void CelestialBox::addObject()
{
    Planet *toAdd;
    std::list<Planet*>::iterator it;

    toAdd = new Planet();
    _parent->getPlanetDetails()->setInfosDetails(toAdd);
    if (toAdd->getName().size() < 1)
    {
        qDebug("Un astre ne peut pas être créé sans un nom valide.");
        return;
    }
    it = _parent->_listPlanet->begin();
    for (it = _parent->_listPlanet->begin(); it != _parent->_listPlanet->end(); ++it)
        if ((*it)->getName() == toAdd->getName())
        {
            qDebug("Impossible d'ajouter un astre ayant le même nom qu'un astre déjà créé.");
            return;
        }
    _parent->_listPlanet->push_front(toAdd);
    _listObjects->addItem(QString(toAdd->getName().c_str()));
    cleanAllFields();
}

void CelestialBox::cleanAllFields()
{
    _parent->getPlanetDetails()->_eName->setText("");
    _parent->getPlanetDetails()->_eRadius->setValue(1);
    _parent->getPlanetDetails()->_ePosX->setValue(1);
    _parent->getPlanetDetails()->_ePosY->setValue(1);
    _parent->getPlanetDetails()->_ePosZ->setValue(1);
    _parent->getPlanetDetails()->_ePosVecX->setValue(1);
    _parent->getPlanetDetails()->_ePosVecY->setValue(1);
    _parent->getPlanetDetails()->_ePosVecZ->setValue(1);
}
