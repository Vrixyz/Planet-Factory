#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QGroupBox(parent)
{
    _parent = parent;
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
    _lName->setGeometry(55, 45, 100, 15);
    _lSolidTemp = new QLabel("Solid < (°C)", _boxDetails);
    _lSolidTemp->setGeometry(55, 85, 100, 15);
    _lGazeousTemp = new QLabel("Gazeous > (°C)", _boxDetails);
    _lGazeousTemp->setGeometry(55, 125, 100, 15);
    _lMass = new QLabel("Mass : (kg/m3)", _boxDetails);
    _lMass->setGeometry(55, 164, 100, 18);
    _lHardness = new QLabel("Hardness :", _boxDetails);
    _lHardness->setGeometry(55, 205, 100, 15);

    _eName = new QLineEdit(_boxDetails);
    _eName->setGeometry(160, 40, 150, 30);
    _eSolidTemp = new QSpinBox(_boxDetails);
    _eSolidTemp->setGeometry(160, 80, 150, 30);
    _eGazeousTemp = new QSpinBox(_boxDetails);
    _eGazeousTemp->setGeometry(160, 120, 150, 30);
    _eMass = new QSpinBox(_boxDetails);
    _eMass->setGeometry(160, 160, 150, 30);
    _eHardness = new QSlider(Qt::Horizontal, _boxDetails);
    _eHardness->setGeometry(160, 200, 150, 30);
    _eHardness->setMinimum(0);
    _eHardness->setMaximum(50);
}

void PlanetCompoBox::createCompoList(void)
{
    _listObjects = new QListWidget(_boxList);
    _listObjects->setGeometry(10, 30, 275, 210);

    _add = new QPushButton(_boxList);
    _del = new QPushButton(_boxList);
    _add->setGeometry(290, 30, 85, 103);
    _del->setGeometry(290, 137, 85, 103);
    _add->setText("Add / Edit");
    _del->setText("Delete");
    _add->setEnabled(false);
    _del->setEnabled(false);

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(addCompo()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delCompo()));
    QObject::connect(_listObjects, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(componentSelected(QListWidgetItem*)));
}

void PlanetCompoBox::cleanAllFields(void)
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    _del->setEnabled(false);
}

void PlanetCompoBox::addCompo(void)
{
    std::list<Planet*>::iterator        it;
    Component                           *toAdd;

    toAdd = new Component(_eName->text().toStdString(), _eGazeousTemp->value(), _eSolidTemp->value(), _eMass->value(), _eHardness->value());
    if (toAdd->getName().size() < 1)
    {
        qDebug("Un composant ne peut pas être créé sans un nom valide.");
        return;
    }
    for (it = _parent->_listPlanet->begin(); it != _parent->_listPlanet->end(); ++it)
    {
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            std::list<Component*> *toCheck;
            toCheck = (*it)->getListCompo();
            std::list<Component*>::iterator     it_compo;
            for (it_compo = toCheck->begin(); it_compo != toCheck->end(); ++it_compo)
            {
                if ((*it_compo)->getName() == _parent->getPlanetCompo()->_eName->text().toStdString())
                {
                    (*it_compo)->setGazeousTemp(_eGazeousTemp->value());
                    (*it_compo)->setSolidTemp(_eSolidTemp->value());
                    (*it_compo)->setMass(_eMass->value());
                    (*it_compo)->setHardness(_eHardness->value());
                    cleanAllFields();
                    return;
                }
            }
            toCheck->push_front(toAdd);
            _listObjects->addItem(QString(toAdd->getName().c_str()));
            cleanAllFields();
            return;
        }
    }
}

void PlanetCompoBox::componentSelected(QListWidgetItem* currItem)
{
    std::list<Component*>::iterator     it_compo;
    std::list<Planet*>::iterator        it;
    std::list<Component*>               *toCheck;

    for (it = _parent->_listPlanet->begin(); it != _parent->_listPlanet->end(); ++it)
    {
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            toCheck = (*it)->getListCompo();
            for (it_compo = toCheck->begin(); it_compo != toCheck->end(); ++it_compo)
            {
                if ((*it_compo)->getName() == currItem->text().toStdString())
                {
                    _parent->getPlanetCompo()->_eName->setText((*it_compo)->getName().c_str());
                    _parent->getPlanetCompo()->_eGazeousTemp->setValue((*it_compo)->getGazeousTemp());
                    _parent->getPlanetCompo()->_eSolidTemp->setValue((*it_compo)->getSolidTemp());
                    _parent->getPlanetCompo()->_eHardness->setValue((*it_compo)->getHardness());
                    _parent->getPlanetCompo()->_eMass->setValue((*it_compo)->getMass());
                    _del->setEnabled(true);
                    return;
                }
            }
        }
    }
}

void PlanetCompoBox::delCompo(void)
{
    std::list<Component*>::iterator     it_compo;
    std::list<Planet*>::iterator        it;
    std::list<Component*>               *toCheck;

    if (_listObjects->currentItem() != NULL)
    {
        for (it = _parent->_listPlanet->begin(); it != _parent->_listPlanet->end(); ++it)
            if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
            {
                toCheck = (*it)->getListCompo();
                for (it_compo = toCheck->begin(); it_compo != toCheck->end(); ++it_compo)
                    if ((*it_compo)->getName() == _listObjects->currentItem()->text().toStdString())
                        it_compo = toCheck->erase(it_compo);
            }
        _listObjects->takeItem(_listObjects->row(_listObjects->currentItem()));
        cleanAllFields();
    }
}
