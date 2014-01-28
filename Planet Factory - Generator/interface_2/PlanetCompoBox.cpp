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

void PlanetCompoBox::updateListCompoSys()
{
    std::list<Component*>::iterator it;

    _listObjects->clear();
    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        _listObjects->addItem((*it)->getName().c_str());
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
    _add->setEnabled(TRUE);
    _edi->setEnabled(FALSE);
    _del->setEnabled(FALSE);

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(windowAddCompo()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delCompoToSys()));
    QObject::connect(_listObjects, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(componentSelected()));
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

    _winAdd = new QPushButton("Add component", _win);
    _winAdd->setGeometry(10, 240, 115, 30);
    _winCan = new QPushButton("Cancel", _win);
    _winCan->setGeometry(135, 240, 115, 30);
    QObject::connect(_winAdd, SIGNAL(clicked()), this, SLOT(addCompoToSys()));
    QObject::connect(_winCan, SIGNAL(clicked()), this, SLOT(windowCloseAndClean()));
}

void PlanetCompoBox::windowAddCompo()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_win->isHidden() == TRUE)
        _win->show();
}

void PlanetCompoBox::windowCloseAndClean()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_win->isHidden() == FALSE)
        _win->hide();
}

void PlanetCompoBox::windowEditCompo()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_win->isHidden() == TRUE)
        _win->show();
    else
        _win->hide();
}

void PlanetCompoBox::addCompoToSys()
{
    std::list<Component*>::iterator it;
    Component*                      toAdd;

    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        if ((*it)->getName() == _eName->text().toStdString())
            return;
    /*    FAIRE POP FENETRE ERREUR A LA PLACE DE NE RIEN FAIRE --> FAIRE UNE FONCTION GENERIQUE POUR LES ERREURS    */
    if (_win->isHidden() == FALSE)
        _win->hide();
    toAdd = new Component();
    toAdd->setName(_eName->text().toStdString());
    toAdd->setMass(_eMass->value());
    toAdd->setHardness(_eHardness->value());
    toAdd->setGazeousTemp(_eGazeousTemp->value());
    toAdd->setSolidTemp(_eSolidTemp->value());
    _parent->getSystem()->getComponentList()->push_front(toAdd);
    updateListCompoSys();
}

void PlanetCompoBox::delCompoToSys()
{
    std::list<Component*>::iterator it;

    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
        {
            _parent->getSystem()->getComponentList()->erase(it);
            _del->setEnabled(FALSE);
            updateListCompoSys();
            return;
        }
}

void PlanetCompoBox::componentSelected()
{
    _del->setEnabled(TRUE);
}
