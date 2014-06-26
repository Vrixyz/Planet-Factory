#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QWidget(parent)
{
    QSignalMapper* signalMapperButton;
    QSignalMapper* signalMapperSpinBox;

    _parent = parent;
    setGeometry(218, 331, 756, 273);

    signalMapperButton = new QSignalMapper(this);
    signalMapperSpinBox = new QSignalMapper(this);
    _winSys = new QDialog(_parent);
    _winSys->hide();
    _winSys->setFixedSize(265, 280);
    _winPla = new QDialog(_parent);
    _winPla->hide();
    _winPla->setFixedSize(265, 280);

    QLabel *infos = new QLabel(this);
    infos->setPixmap(QPixmap(":/res/label_planet_compo.png"));
    infos->setGeometry(-17, 0, 362, 24);

    _listObjects = new QListWidget(this);
    _listObjects->setGeometry(394, 0, 362, 207);

    _add = new QPushButton(this);
    _add->setGeometry(394, 212, 114, 30);
    _add->setText("Add Component");
    _edi = new QPushButton(this);
    _edi->setGeometry(513, 212, 114, 30);
    _edi->setText("Edit Component");
    _edi->setEnabled(FALSE);
    _del = new QPushButton(this);
    _del->setGeometry(632, 212, 124, 30);
    _del->setText("Delete Component");
    _del->setEnabled(FALSE);

    _currComponent = NULL;

    _compoAdd = new QPushButton(this);
    _compoAdd->setGeometry(0, 213, 362, 30);
    _compoAdd->setText("Add created component to current planet");
    _compoAdd->setEnabled(FALSE);

    for (int i = 0; i < 7; i++)
    {
        _compoName[i] =  new QLabel("HELLO !", this);
        _compoValue[i] = new QSpinBox(this);
        _compoDel[i] = new QPushButton("Delete", this);
        QObject::connect(_compoDel[i], SIGNAL(clicked()), signalMapperButton, SLOT(map()));
        signalMapperButton->setMapping (_compoDel[i], i) ;
        QObject::connect(_compoValue[i], SIGNAL(valueChanged(int)), signalMapperSpinBox, SLOT(map()));
        signalMapperSpinBox->setMapping (_compoValue[i], i);
    }
    QObject::connect(signalMapperButton, SIGNAL(mapped(int)), this, SLOT(delCompoToPla(int))) ;
    QObject::connect(signalMapperSpinBox, SIGNAL(mapped(int)), this, SLOT(changePercentCompo(int))) ;
    QObject::connect(_add, SIGNAL(clicked()), this, SLOT(windowSysAddCompo()));
    QObject::connect(_edi, SIGNAL(clicked()), this, SLOT(windowSysEdiCompo()));
    QObject::connect(_del, SIGNAL(clicked()), this, SLOT(delCompoToSys()));
    QObject::connect(_listObjects, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(componentSysSelected()));

    createWindowSysComponent();
    createWindowPlaComponent();
    createCompoList();
    checkPercentPla();
}

PlanetCompoBox::~PlanetCompoBox()
{

}

void PlanetCompoBox::changePercentCompo(int pos)
{
    std::map<Component*, int>::iterator    it_compo;
    int i;

    for (i = 0, it_compo = _parent->_currPlanet->getComponentMap()->begin();
         it_compo != _parent->_currPlanet->getComponentMap()->end() && i < pos;
         ++it_compo, ++i);
    it_compo->second = _compoValue[i]->value();
    checkPercentPla();
}

void PlanetCompoBox::checkPercentPla()
{
    std::map<Component*, int>::iterator it_compo;
    int                                 total;

    if (_parent->_currPlanet == NULL)
    {
        _percentWarning->setStyleSheet("QLabel { color : red; }");
        _percentWarning->setText("No planet selected.");
    }
    else
    {
        for (total = 0, it_compo = _parent->_currPlanet->getComponentMap()->begin();
             it_compo != _parent->_currPlanet->getComponentMap()->end();
             ++it_compo)
            total += it_compo->second;
        if (total != 100)
        {
            _percentWarning->setStyleSheet("QLabel { color : red; }");
            _percentWarning->setText("The sum of the % of all the components is not equal to 100%. :(");
        }
        else
        {
            _percentWarning->setStyleSheet("QLabel { color : green; }");
            _percentWarning->setText("The sum of the % of all the components is equal to 100%. :)");
        }
    }
}

void PlanetCompoBox::windowPlaAddCompo()
{
    std::list<Component*>::iterator it;

    if (_winPla->isHidden() == TRUE)
    {
        for (it = _parent->getSystem()->getComponentList()->begin();
             it != _parent->getSystem()->getComponentList()->end(); ++it)
            _listCompo->addItem((*it)->getName().c_str());
        _winPla->show();
    }
}

void PlanetCompoBox::addCompoToPla()
{
    std::list<Planet*>::iterator    it;

    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            std::map<Component*, int>::iterator itMapCompo;
            std::list<Component*>::iterator     itListCompo;

            for (itMapCompo = (*it)->getComponentMap()->begin();
                 itMapCompo != (*it)->getComponentMap()->end(); ++itMapCompo)
            {
                if ((itMapCompo->first)->getName() == _listCompo->currentItem()->text().toStdString())
                    return; /*  AJOUTER MSG ERREUR  */
            }
            for (itListCompo = _parent->getSystem()->getComponentList()->begin();
                 itListCompo != _parent->getSystem()->getComponentList()->end(); ++itListCompo)
            {
                if ((*itListCompo)->getName() == _listCompo->currentItem()->text().toStdString())
                {
                    Component* compoToAdd = (*itListCompo);

                    (*it)->getComponentMap()->insert(std::make_pair(compoToAdd, 0));
                    updateListCompoPla();
                    windowPlaCloseAndClean();
                    return;
                }
            }
            return;
        }
    windowPlaCloseAndClean();
    checkPercentPla();
}

void PlanetCompoBox::delCompoToPla(int pos)
{
    std::list<Planet*>::iterator    it;

    for (it = _parent->getSystem()->getPlanetList()->begin(); it != _parent->getSystem()->getPlanetList()->end(); ++it)
        if ((*it)->getName() == _parent->getPlanetDetails()->_eName->text().toStdString())
        {
            std::map<Component*, int>::iterator    it_compo;
            int i;

            for (i = 0, it_compo = (*it)->getComponentMap()->begin();
                 it_compo != (*it)->getComponentMap()->end() && i < pos; ++it_compo, ++i);
            (*it)->getComponentMap()->erase(it_compo);
        }
    updateListCompoPla();
    checkPercentPla();
}

void PlanetCompoBox::updateListCompoSys()
{
    std::list<Component*>::iterator it;

    _listObjects->clear();
    for (it = _parent->getSystem()->getComponentList()->begin();
         it != _parent->getSystem()->getComponentList()->end(); ++it)
        _listObjects->addItem((*it)->getName().c_str());
}

void PlanetCompoBox::updateListCompoPla()
{
    std::map<Component*, int>::iterator     it_compo;
    std::list<Planet*>::iterator        it;
    int i;

    for (i = 0; i < 7; i++)
    {
        _compoValue[i]->hide();
        _compoName[i]->hide();
        _compoDel[i]->hide();
    }
    if (_parent->_currPlanet == NULL)
    {
        _compoAdd->setEnabled(FALSE);
    }
    else
    {
        for (i = 0, it_compo = _parent->_currPlanet->getComponentMap()->begin();
             it_compo != _parent->_currPlanet->getComponentMap()->end(); ++it_compo, i++)
        {
            _compoValue[i]->setValue(it_compo->second);
            _compoValue[i]->show();
            _compoName[i]->setText(it_compo->first->getName().c_str());
            _compoName[i]->show();
            _compoDel[i]->show();
        }
        _compoAdd->setEnabled(TRUE);
        _compoAdd->show();
        if (i == 7)
            _compoAdd->setEnabled(FALSE);
    }
    //checkPercentPla();
}

void PlanetCompoBox::createCompoList(void)
{
    _percentWarning = new QLabel("", this);
    _percentWarning->setGeometry(0, 248, 360, 20);
    _percentWarning->setAlignment(Qt::AlignCenter);
    for (int i = 0; i < 7; i++)
    {
        _compoName[i]->setGeometry(0, (18 + (26 * i)), 150, 30);
        _compoName[i]->setAlignment(Qt::AlignCenter);
        _compoValue[i]->setGeometry(194, (23 + (26 * i)), 50, 25);
        _compoDel[i]->setGeometry(269, (23 + (26 * i)), 80, 25);
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
    QLabel      *lGazeousTemp;
    QLabel      *lSolidTemp;
    QLabel      *lHardness;
    QLabel      *lMass;

    lName = new QLabel("Name :", _winSys);
    lName->setGeometry(10, 45, 100, 15);
    _lTitle = new QLabel("Choose the paramters of the new component", _winSys);
    _lTitle->setGeometry(20, 10, 250, 15);
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
    _winSysEdi = new QPushButton("Edit component", _winSys);
    _winSysEdi->setGeometry(10, 240, 115, 30);
    _winSysEdi->hide();
    _winSysCan = new QPushButton("Cancel", _winSys);
    _winSysCan->setGeometry(135, 240, 115, 30);
    QObject::connect(_winSysAdd, SIGNAL(clicked()), this, SLOT(addCompoToSys()));
    QObject::connect(_winSysEdi, SIGNAL(clicked()), this, SLOT(ediCompoToSys()));
    QObject::connect(_winSysCan, SIGNAL(clicked()), this, SLOT(windowSysCloseAndClean()));
}

void PlanetCompoBox::windowSysAddCompo()
{
    if (_winSys->isHidden() == TRUE)
    {
        _lTitle->setText("Choose the paramters of the new component");
        _winSysAdd->show();
        _winSysEdi->hide();
        _eName->setText("");
        _eGazeousTemp->setValue(0);
        _eSolidTemp->setValue(0);
        _eHardness->setValue(0);
        _eMass->setValue(0);
        _winSys->show();
    }
}

void PlanetCompoBox::windowSysEdiCompo()
{
    std::list<Component*>::iterator it;

    if (_winSys->isHidden() == TRUE)
    {
        for (it = _parent->getSystem()->getComponentList()->begin();
             it != _parent->getSystem()->getComponentList()->end(); ++it)
            if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
            {
                _lTitle->setText("Edit the parameters of the choosen component");
                _winSysEdi->show();
                _winSysAdd->hide();
                _winSys->show();
                _eName->setText(QString((*it)->getName().c_str()));
                _eGazeousTemp->setValue((*it)->getGazeousTemp());
                _eSolidTemp->setValue((*it)->getSolidTemp());
                _eHardness->setValue((*it)->getHardness());
                _eMass->setValue((*it)->getMass());
            }
    }
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

void PlanetCompoBox::addCompoToSys()
{
    std::list<Component*>::iterator it;
    Component*                      toAdd;

    for (it = _parent->getSystem()->getComponentList()->begin();
         it != _parent->getSystem()->getComponentList()->end(); ++it)
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
    std::list<Planet*>::iterator it_pla;

    for (it = _parent->getSystem()->getComponentList()->begin();
         it != _parent->getSystem()->getComponentList()->end(); ++it)
        if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
        {
            for (it_pla = _parent->getSystem()->getPlanetList()->begin();
                 it_pla != _parent->getSystem()->getPlanetList()->end(); ++it_pla)
                (*it_pla)->getComponentMap()->erase(*it);
            _parent->getSystem()->getComponentList()->erase(it);
            _del->setEnabled(FALSE);
            _edi->setEnabled(FALSE);
            _currComponent = NULL;
            updateListCompoSys();
            updateListCompoPla();
            checkPercentPla();
            return;
        }
}

void PlanetCompoBox::ediCompoToSys()
{
    _currComponent->setName(_eName->text().toStdString().c_str());
    _currComponent->setGazeousTemp(_eGazeousTemp->value());
    _currComponent->setSolidTemp(_eSolidTemp->value());
    _currComponent->setHardness(_eHardness->value());
    _currComponent->setMass(_eMass->value());
    _winSys->hide();
}

void PlanetCompoBox::componentPlaSelected()
{
    _winPlaAdd->setEnabled(TRUE);
}

void PlanetCompoBox::componentSysSelected()
{
    std::list<Component*>::iterator it;

    for (it = _parent->getSystem()->getComponentList()->begin(); it != _parent->getSystem()->getComponentList()->end(); ++it)
        if ((*it)->getName() == _listObjects->currentItem()->text().toStdString())
            _currComponent = (*it);
    _del->setEnabled(TRUE);
    _edi->setEnabled(TRUE);
}
