#include "CelestialBox.hpp"
#include "MainWindow.hpp"

CelestialBox::CelestialBox(MainWindow *parent) : QWidget(parent)
{
    setGeometry(218, 44, 288, 295);

    _parent = parent;
    _listObjects = new QListWidget(this);
    _listObjects->setGeometry(0, 0, 288, 205);
    _listObjects->setStyleSheet("QListWidget { border: none }");
    _add = new QPushButton(this);
    _del = new QPushButton(this);
    _add->setGeometry(0, 210, 141, 30);
    _add->setText("Add / Edit");
//    _add->setObjectName("celestial_add");
    _del->setGeometry(147, 210, 141, 30);
    _del->setText("Delete");
//    _del->setObjectName("celestial_del");
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
            _parent->getPlanetDetails()->_eRadius->setValue((*it)->getRadius());
            _parent->getPlanetDetails()->_eDistance->setValue((*it)->getDistance());
            _parent->getPlanetDetails()->_eRevo->setValue((*it)->getRevo());
            _parent->getPlanetDetails()->_eTilt->setValue((*it)->getTilt());
            _parent->getPlanetCompo()->_compoAdd->setEnabled(TRUE);
            _parent->getPlanetCompo()->updateListCompoPla();
            _del->setEnabled(TRUE);
        }
    _parent->getPlanetCompo()->checkPercentPla();
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
    _parent->getPlanetCompo()->checkPercentPla();
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
    _del->setEnabled(FALSE);
}

