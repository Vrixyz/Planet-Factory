#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QGroupBox(parent)
{
    QSignalMapper* signalMapper;

    _parent = parent;
    setGeometry(205, 405, 790, 290);
    setTitle("System Composition");

    signalMapper = new QSignalMapper(this);
    _winSys = new QDialog(_parent);
    _winSys->hide();
    _winSys->setFixedSize(265, 280);
    _winPla = new QDialog(_parent);
    _winPla->hide();
    _winPla->setFixedSize(265, 280);

    _boxSystem = new GroupTools(parent);
    _boxSystem->setGeometry(605, 425, 380, 260);
    _boxSystem->setTitle("System Composition");

    _compoAdd = new QPushButton("Add component to selected planet", this);
    _compoAdd->setEnabled(FALSE);

    for (int i = 0; i < 8; i++)
    {
        _compoName[i] =  new QLabel("HELLO!", this);
        _compoValue[i] = new QSpinBox(this);
        _compoDel[i] = new QPushButton("Delete", this);
        QObject::connect(_compoDel[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping (_compoDel[i], i) ;
    }
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(delCompoToPla(int))) ;

    createWindowSysComponent();
    createWindowPlaComponent();
    createCompoDetails();
    createCompoList();
}

PlanetCompoBox::~PlanetCompoBox()
{
}

void PlanetCompoBox::windowPlaAddCompo()
{
    std::list<Component*>::iterator it;

    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        _listCompo->addItem((*it)->getName().c_str());
    if (_winPla->isHidden() == TRUE)
        _winPla->show();
}

void PlanetCompoBox::addCompoToPla()
{
    std::list<Planet*>::iterator    it;

    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            std::list<Component*>::iterator    it_compo;

            for (it_compo = (*it)->getComponentList()->begin(); it_compo != (*it)->getComponentList()->end(); ++it_compo)
            {
                if ((*it_compo)->getName() == _listCompo->currentItem()->text().toStdString())
                    return; /*  AJOUTER MSG ERREUR  */
            }
            for (it_compo = _parent->getSystem()->getComponentList()->begin(); it_compo != _parent->getSystem()->getComponentList()->end(); ++it_compo)
            {
                if ((*it_compo)->getName() == _listCompo->currentItem()->text().toStdString())
                {
                    (*it)->getComponentList()->push_front(*it_compo);
                    updateListCompoPla();
                    windowPlaCloseAndClean();
                    return;
                }
            }
            return;
        }
    windowPlaCloseAndClean();
}

void PlanetCompoBox::delCompoToPla(int pos)
{
    std::list<Planet*>::iterator    it;

    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            (*it)->getComponentList();
        }
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

    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(windowSysAddCompo()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delCompoToSys()));
    QObject::connect(_listObjects, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(componentSysSelected()));
}

void PlanetCompoBox::updateListCompoPla()
{
    std::list<Component*>::iterator     it_compo;
    std::list<Planet*>::iterator        it;
    int i;

    std::cout << "000" << std::endl;
    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == _parent->_currPlanet)
        {
            _compoAdd->show();
            for (i = 0; i < 8; i++)
            {
                _compoName[i]->hide();
                _compoValue[i]->hide();
                _compoDel[i]->hide();
            }
            for (i = 0, it_compo = (*it)->getComponentList()->begin(); it_compo != (*it)->getComponentList()->end(); ++it_compo, i++)
            {
                _compoName[i]->setText((*it_compo)->getName().c_str());
                _compoName[i]->show();
                _compoValue[i]->show();
                _compoDel[i]->show();
            }
            _compoAdd->setGeometry(20, (20 + (33 * i)), 360, 30);
            if (i == 7)
                _compoAdd->hide();
            return;
        }
    std::cout << "001" << std::endl;
}

void PlanetCompoBox::createCompoList(void)
{
    _compoAdd->setGeometry(20, 20, 360, 30);

    for (int i = 0; i < 8; i++)
    {
        _compoName[i]->setGeometry(20, (15 + (33 * i)), 150, 30);
        _compoValue[i]->setGeometry(220, (20 + (33 * i)), 50, 25);
        _compoDel[i]->setGeometry(280, (20 + (33 * i)), 80, 25);
        _compoName[i]->hide();
        _compoValue[i]->hide();
        _compoDel[i]->hide();
    }
    QObject::connect(_compoAdd, SIGNAL(clicked()), this, SLOT(windowPlaAddCompo()));
}

void PlanetCompoBox::createWindowPlaComponent()
{
    QLabel      *lName;

    lName = new QLabel("Please, select the component you\nwant to add to your planet", _winPla);
    lName->setGeometry(0, 10, 265, 30);
    lName->setAlignment(Qt::AlignCenter);

    _listCompo = new QListWidget(_winPla);
    _listCompo->setGeometry(10, 50, 245, 175);

    _winPlaAdd = new QPushButton("Add component", _winPla);
    _winPlaAdd->setGeometry(10, 240, 115, 30);
    _winPlaAdd->setEnabled(FALSE);
    _winPlaCan = new QPushButton("Cancel", _winPla);
    _winPlaCan->setGeometry(135, 240, 115, 30);
    QObject::connect(_winPlaAdd, SIGNAL(clicked()), this, SLOT(addCompoToPla()));
    QObject::connect(_winPlaCan, SIGNAL(clicked()), this, SLOT(windowPlaCloseAndClean()));
    QObject::connect(_listCompo, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(componentPlaSelected()));
}

void PlanetCompoBox::createWindowSysComponent()
{
    QLabel      *lName;
    QLabel      *lTitle;
    QLabel      *lGazeousTemp;
    QLabel      *lSolidTemp;
    QLabel      *lHardness;
    QLabel      *lMass;

    lName = new QLabel("Name :", _winSys);
    lName->setGeometry(10, 45, 100, 15);
    lTitle = new QLabel("Choose the paramters of the new component", _winSys);
    lTitle->setGeometry(20, 10, 250, 15);
    lSolidTemp = new QLabel("Solid < (°C)", _winSys);
    lSolidTemp->setGeometry(10, 85, 100, 15);
    lGazeousTemp = new QLabel("Gazeous > (°C)", _winSys);
    lGazeousTemp->setGeometry(10, 125, 100, 15);
    lMass = new QLabel("Mass : (kg/m3)", _winSys);
    lMass->setGeometry(10, 165, 100, 18);
    lHardness = new QLabel("Hardness :", _winSys);
    lHardness->setGeometry(10, 205, 100, 15);

    _eName = new QLineEdit(_winSys);
    _eName->setGeometry(100, 40, 150, 30);
    _eSolidTemp = new QSpinBox(_winSys);
    _eSolidTemp->setGeometry(100, 80, 150, 30);
    _eSolidTemp->setMinimum(-10000);
    _eSolidTemp->setMaximum(10000);
    _eGazeousTemp = new QSpinBox(_winSys);
    _eGazeousTemp->setGeometry(100, 120, 150, 30);
    _eGazeousTemp->setMinimum(-10000);
    _eGazeousTemp->setMaximum(10000);
    _eMass = new QSpinBox(_winSys);
    _eMass->setGeometry(100, 160, 150, 30);
    _eMass->setMinimum(1);
    _eMass->setMaximum(100000);
    _eHardness = new QSlider(Qt::Horizontal, _winSys);
    _eHardness->setGeometry(100, 200, 150, 30);
    _eHardness->setMinimum(0);
    _eHardness->setMaximum(50);

    _winSysAdd = new QPushButton("Add component", _winSys);
    _winSysAdd->setGeometry(10, 240, 115, 30);
    _winSysCan = new QPushButton("Cancel", _winSys);
    _winSysCan->setGeometry(135, 240, 115, 30);
    QObject::connect(_winSysAdd, SIGNAL(clicked()), this, SLOT(addCompoToSys()));
    QObject::connect(_winSysCan, SIGNAL(clicked()), this, SLOT(windowSysCloseAndClean()));
}

void PlanetCompoBox::windowSysAddCompo()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_winSys->isHidden() == TRUE)
        _winSys->show();
}

void PlanetCompoBox::windowPlaCloseAndClean()
{
    _listCompo->clear();
    _winPlaAdd->setEnabled(FALSE);
    if (_winPla->isHidden() == FALSE)
        _winPla->hide();
}

void PlanetCompoBox::windowSysCloseAndClean()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_winSys->isHidden() == FALSE)
        _winSys->hide();
}

void PlanetCompoBox::windowSysEditCompo()
{
    _eName->setText("");
    _eGazeousTemp->setValue(0);
    _eSolidTemp->setValue(0);
    _eHardness->setValue(0);
    _eMass->setValue(0);
    if (_winSys->isHidden() == TRUE)
        _winSys->show();
    else
        _winSys->hide();
}

void PlanetCompoBox::addCompoToSys()
{
    std::list<Component*>::iterator it;
    Component*                      toAdd;

    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        if ((*it)->getName() == _eName->text().toStdString())
            return;
    /*    FAIRE POP FENETRE ERREUR A LA PLACE DE NE RIEN FAIRE --> FAIRE UNE FONCTION GENERIQUE POUR LES ERREURS    */
    if (_winSys->isHidden() == FALSE)
        _winSys->hide();
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

void PlanetCompoBox::componentPlaSelected()
{
    _winPlaAdd->setEnabled(TRUE);
}

void PlanetCompoBox::componentSysSelected()
{
    _del->setEnabled(TRUE);
}
