#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QGroupBox(parent)
{
    _parent = parent;
    setGeometry(205, 405, 790, 290);
    setTitle("System Composition");

    _win = new QDialog(_parent);
    _win->hide();
    _win->setFixedSize(265, 280);

    _boxPlanet = new GroupTools(parent);
    _boxPlanet->setGeometry(215, 425, 380, 260);
    _boxPlanet->setTitle("Planet Components");

    _boxSystem = new GroupTools(parent);
    _boxSystem->setGeometry(605, 425, 380, 260);
    _boxSystem->setTitle("System Composition");

    createWindowComponent();
    createCompoDetails();
    createCompoList();
}

PlanetCompoBox::~PlanetCompoBox()
{
}

void PlanetCompoBox::createCompoDetails(void)
{ 
    _listObjects = new QListWidget(_boxSystem);
    _listObjects->setGeometry(10, 20, 360, 185);

    _add = new QPushButton(_boxSystem);
    _del = new QPushButton(_boxSystem);
    _edi = new QPushButton(_boxSystem);
    _add->setGeometry(10, 212, 115, 40);
    _edi->setGeometry(135, 212, 115, 40);
    _del->setGeometry(260, 212, 110, 40);
    _add->setText("Add component\nto the system");
    _edi->setText("Edit selected\ncomponent");
    _del->setText("Delete selected\ncomponent");
    _add->setEnabled(true);
    _edi->setEnabled(false);
    _del->setEnabled(false);

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(cleanWindowCompoSys()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delCompo()));
    QObject::connect(_edi, SIGNAL(clicked()), this, SLOT(delCompo()));
    QObject::connect(_listObjects, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(componentSelected(QListWidgetItem*)));
}

void PlanetCompoBox::createCompoList(void)
{

}

void PlanetCompoBox::createWindowComponent()
{
    QLabel      *lName;
    QLabel      *lTitle;
    QLabel      *lGazeousTemp;
    QLabel      *lSolidTemp;
    QLabel      *lHardness;
    QLabel      *lMass;
    QPushButton *add;
    QPushButton *cancel;

    lName = new QLabel("Name :", _win);
    lName->setGeometry(10, 45, 100, 15);
    lTitle = new QLabel("Choose the paramters of the new component", _win);
    lTitle->setGeometry(20, 10, 250, 15);
    lSolidTemp = new QLabel("Solid < (°C)", _win);
    lSolidTemp->setGeometry(10, 85, 100, 15);
    lGazeousTemp = new QLabel("Gazeous > (°C)", _win);
    lGazeousTemp->setGeometry(10, 125, 100, 15);
    lMass = new QLabel("Mass : (kg/m3)", _win);
    lMass->setGeometry(10, 165, 100, 18);
    lHardness = new QLabel("Hardness :", _win);
    lHardness->setGeometry(10, 205, 100, 15);

    _eName = new QLineEdit(_win);
    _eName->setGeometry(100, 40, 150, 30);
    _eSolidTemp = new QSpinBox(_win);
    _eSolidTemp->setGeometry(100, 80, 150, 30);
    _eGazeousTemp = new QSpinBox(_win);
    _eGazeousTemp->setGeometry(100, 120, 150, 30);
    _eMass = new QSpinBox(_win);
    _eMass->setGeometry(100, 160, 150, 30);
    _eHardness = new QSlider(Qt::Horizontal, _win);
    _eHardness->setGeometry(100, 200, 150, 30);
    _eHardness->setMinimum(0);
    _eHardness->setMaximum(50);

    add = new QPushButton("Add component", _win);
    add->setGeometry(10, 240, 115, 30);
    cancel = new QPushButton("Cancel", _win);
    cancel->setGeometry(135, 240, 115, 30);
    QObject::connect(add, SIGNAL(clicked()), this, SLOT(cleanWindowCompoSys()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cleanWindowCompoSys()));
}

void PlanetCompoBox::cleanWindowCompoSys()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    _del->setEnabled(false);
    if (_win->isHidden() == TRUE)
        _win->show();
    else
        _win->hide();
}

void PlanetCompoBox::loadWindowCompoSys()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    _del->setEnabled(false);
}

void PlanetCompoBox::addCompoToSys()
{

}

void PlanetCompoBox::cleanAllFields(void)
{

}

void PlanetCompoBox::addCompo(void)
{
    std::list<Planet*>::iterator        it;
    Component                           *toAdd;

    toAdd = new Component(_eName->text().toStdString(), _eGazeousTemp->value(), _eSolidTemp->value(), _eMass->value(), _eHardness->value(), "");
    if (toAdd->getName().size() < 1)
    {
        qDebug("Un composant ne peut pas être créé sans un nom valide.");
        return;
    }
    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
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

    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
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
        for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
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

