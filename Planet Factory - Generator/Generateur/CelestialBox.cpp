#include "CelestialBox.hpp"
#include "MainWindow.hpp"

CelestialBox::CelestialBox(MainWindow *parent) : QGroupBox(parent)
{
    setGeometry(5, 105, 295, 295);
    setTitle("Celestial objects");

    _parent = parent;
    _listObjects = new QListWidget(this);
    _listObjects->setGeometry(10, 30, 275, 205);
    _add = new QPushButton(this);
    _del = new QPushButton(this);
    _add->setGeometry(10, 240, 135, 50);
    _del->setGeometry(150, 240, 135, 50);
    _add->setText("Add / Edit");
    _del->setText("Delete");
    _del->setEnabled(false);

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(addObject()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delObject()));
    QObject::connect(_listObjects, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(planetSelected(QListWidgetItem*)));
}

CelestialBox::~CelestialBox()
{
}

void CelestialBox::updateListPlanet(void)
{
    std::list<Planet*>::iterator it;

    _listObjects->clear();
    for (it = _parent->getSystem()->getPlanetList()->begin();
         it != _parent->getSystem()->getPlanetList()->end(); ++it)
        _listObjects->addItem((*it)->getName().c_str());
}

void CelestialBox::planetSelected(QListWidgetItem* currItem)
{
    std::list<Planet*>::iterator    it;
    int                             *pos;
    int                             *posVec;

    it = _parent->getSystem()->getPlanetList()->begin();
    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == currItem->text().toStdString())
        {
            _parent->getPlanetDetails()->_eName->setText((*it)->getName().c_str());
            _parent->_currPlanet = (*it);
            if ((*it)->getType() == STAR)
                _parent->getPlanetDetails()->_eType->setCurrentIndex(0);
            else if ((*it)->getType() == TELLURIC)
                _parent->getPlanetDetails()->_eType->setCurrentIndex(1);
            else if ((*it)->getType() == GAZEOUS)
                _parent->getPlanetDetails()->_eType->setCurrentIndex(2);
            else if ((*it)->getType() == ASTEROID)
                _parent->getPlanetDetails()->_eType->setCurrentIndex(3);
            pos = (*it)->getPosition();
            posVec = (*it)->getPositionVec();
            _parent->getPlanetDetails()->_eRadius->setValue((*it)->getRadius());
            _parent->getPlanetDetails()->_eDistance->setValue((*it)->getDistance());
            _parent->getPlanetDetails()->_eRevo->setValue((*it)->getRevo());
            _parent->getPlanetDetails()->_eTilt->setValue((*it)->getTilt());
/*            _parent->getPlanetDetails()->_ePosX->setValue(pos[0]);
            _parent->getPlanetDetails()->_ePosY->setValue(pos[1]);
            _parent->getPlanetDetails()->_ePosZ->setValue(pos[2]);
            _parent->getPlanetDetails()->_ePosVecX->setValue(posVec[0]);
            _parent->getPlanetDetails()->_ePosVecY->setValue(posVec[1]);
            _parent->getPlanetDetails()->_ePosVecZ->setValue(posVec[2]);*/
            _parent->getPlanetCompo()->_compoAdd->setEnabled(TRUE);
            _parent->getPlanetCompo()->updateListCompoPla();
            _del->setEnabled(TRUE);
        }
}

void CelestialBox::delObject()
{
    if (_listObjects->currentItem() != NULL)
    {
        std::list<Planet*>::iterator it;

        it = _parent->getSystem()->getPlanetList()->begin();
        for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
            if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
                it = _parent->getSystem()->getPlanetList()->erase(it);
        _listObjects->takeItem(_listObjects->row(_listObjects->currentItem()));
        cleanAllFields();
        _parent->_currPlanet = NULL;
        _parent->getPlanetCompo()->updateListCompoPla();
    }
}

void CelestialBox::addObject()
{
    std::list<Planet*>::iterator    it;
    Planet                          *toAdd;

    toAdd = new Planet();
    _parent->getPlanetDetails()->setInfosDetails(toAdd);
    if (toAdd->getName().size() < 1)
    {
        qDebug("Un astre ne peut pas être créé sans un nom valide.");
        return;
    }
    it = _parent->getSystem()->getPlanetList()->begin();
    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == toAdd->getName())
        {
            (*it)->setName(_parent->getPlanetDetails()->_eName->text().toStdString().c_str());
            (*it)->setRadius(_parent->getPlanetDetails()->_eRadius->value());
            (*it)->setDistance(_parent->getPlanetDetails()->_eDistance->value());
            (*it)->setRevo(_parent->getPlanetDetails()->_eRevo->value());
            (*it)->setTilt(_parent->getPlanetDetails()->_eTilt->value());
            //(*it)->setPosition(_parent->getPlanetDetails()->_ePosX->value(), _parent->getPlanetDetails()->_ePosY->value(), _parent->getPlanetDetails()->_ePosZ->value());
            //(*it)->setPositionVec(_parent->getPlanetDetails()->_ePosVecX->value(), _parent->getPlanetDetails()->_ePosVecY->value(), _parent->getPlanetDetails()->_ePosVecZ->value());
            if (_parent->getPlanetDetails()->_eType->currentText().toStdString() == std::string("Star"))
                (*it)->setType(STAR);
            else if (_parent->getPlanetDetails()->_eType->currentText().toStdString() == std::string("Telluric planet"))
                (*it)->setType(TELLURIC);
            else if (_parent->getPlanetDetails()->_eType->currentText().toStdString() == std::string("Gazeous planet"))
                (*it)->setType(GAZEOUS);
            else if (_parent->getPlanetDetails()->_eType->currentText().toStdString() == std::string("Asteroid"))
                (*it)->setType(ASTEROID);
            cleanAllFields();
            return;
        }
    _parent->getSystem()->getPlanetList()->push_front(toAdd);
    _listObjects->addItem(QString(toAdd->getName().c_str()));
    cleanAllFields();
}

void CelestialBox::cleanAllFields()
{
    _parent->getPlanetCompo()->_compoAdd->setEnabled(FALSE);
    _parent->getPlanetDetails()->_eName->setText("");
    _parent->getPlanetDetails()->_eType->setCurrentIndex(0);
    _parent->getPlanetDetails()->_eRadius->setValue(1);
    _parent->getPlanetDetails()->_eDistance->setValue(1);
    _parent->getPlanetDetails()->_eRevo->setValue(1);
    _parent->getPlanetDetails()->_eTilt->setValue(1);
/*    _parent->getPlanetDetails()->_ePosX->setValue(0);
    _parent->getPlanetDetails()->_ePosY->setValue(0);
    _parent->getPlanetDetails()->_ePosZ->setValue(0);
    _parent->getPlanetDetails()->_ePosVecX->setValue(0);
    _parent->getPlanetDetails()->_ePosVecY->setValue(0);
    _parent->getPlanetDetails()->_ePosVecZ->setValue(0);*/
    _del->setEnabled(FALSE);
}
