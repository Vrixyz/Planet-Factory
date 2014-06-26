#include "Menu.hpp"
#include "MainWindow.hpp"
#include "GenWin.hpp"

Menu::Menu(MainWindow *parent) : QWidget(parent)
{
    setGeometry(50,330,100,210);
    show();

    _parent = parent;

    _save = new QPushButton(this);
    _save->setGeometry(0, 0, 100, 25);
    _load = new QPushButton(this);
    _load->setGeometry(0, 35, 100, 25);
    _launch = new QPushButton(this);
    _launch->setGeometry(0, 70, 100, 25);
    _reset = new QPushButton(this);
    _reset->setGeometry(0, 105, 100, 25);
    _facebook = new QPushButton(this);
    _facebook->setGeometry(13, 180, 32, 32);
    _twitter = new QPushButton(this);
    _twitter->setGeometry(55, 180, 32, 32);
    _exit = new QPushButton(_parent);
    _exit->setGeometry(980, 5, 15, 15);

    _save->setObjectName("menu_save");
    _exit->setObjectName("menu_exit");
    _load->setObjectName("menu_load");
    _launch->setObjectName("menu_launch");
    _reset->setObjectName("menu_reset");
    _facebook->setObjectName("menu_facebook");
    _twitter->setObjectName("menu_twitter");

    _launchWindow = new QDialog();
    _launchWindow->setFixedSize(300, 275);
    _launchWindow->hide();
    createWindowLaunch();

    QObject::connect(_facebook, SIGNAL(clicked()), this, SLOT(linkFacebook()));
    QObject::connect(_twitter, SIGNAL(clicked()), this, SLOT(linkTwitter()));
    QObject::connect(_launch, SIGNAL(clicked()), this, SLOT(windowLaunch()));
    QObject::connect(_exit, SIGNAL(clicked()), _parent, SLOT(close()));
    QObject::connect(_reset, SIGNAL(clicked()), this, SLOT(resetAll()));
    QObject::connect(_save, SIGNAL(clicked()), this, SLOT(saveConfSystem()));
    QObject::connect(_load, SIGNAL(clicked()), this, SLOT(loadConfSystem()));
}

Menu::~Menu()
{
}

void Menu::linkFacebook()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/planetfactoryeip?ref=hl"));
}

void Menu::linkTwitter()
{
    QDesktopServices::openUrl(QUrl("https://www.twitter.com/planet_factory"));
}

void Menu::resetAll()
{
    _parent->getSystem()->getComponentList()->clear();
    _parent->getSystem()->getPlanetList()->clear();
    _parent->getCelestial()->cleanAllFields();
    _parent->getCelestial()->updateListPlanet();
    _parent->getPlanetCompo()->updateListCompoPla();
    _parent->getPlanetCompo()->updateListCompoSys();
    _parent->getPlanetCompo()->checkPercentPla();
}

void Menu::generate()
{
    _launchWindow->hide();

    int inter = _interSpinBox[1]->value() + _interSpinBox[0]->value() * 365;
    int duree = _timerSpinBox[1]->value() + _timerSpinBox[0]->value() * 365;
    qDebug() << "duree " << duree << " inter " << inter;
    QString path = QFileDialog::getExistingDirectory(this, tr("Chose save dir"));
    if (path.isEmpty())
      return;

    System *s = _parent->getSystem();
    GenWin *gen = new GenWin(s, path, duree, inter);
    gen->launch();
}

void Menu::createWindowLaunch(void)
{
    QLabel      *title;
    QLabel      *timer;
    QLabel      *inter;
    QLabel      *timerSub;
    QLabel      *interSub;
    QPushButton *cancel;
    QPushButton *generate;

    title = new QLabel("GENERER LE SYSTEME", _launchWindow);
    title->setGeometry(0, 10, 300, 25);
    title->setAlignment(Qt::AlignCenter);
    timer = new QLabel("Durée totale de la génération :", _launchWindow);
    timer->setGeometry(0, 40, 300, 25);
    timer->setAlignment(Qt::AlignCenter);
    timerSub = new QLabel(" Years       Days", _launchWindow);
    timerSub->setGeometry(65, 60, 300, 25);
    inter = new QLabel("Interval de génération :", _launchWindow);
    inter->setGeometry(0, 130, 300, 25);
    inter->setAlignment(Qt::AlignCenter);
    interSub = new QLabel(" Years       Days", _launchWindow);
    interSub->setGeometry(65, 150, 300, 25);
    generate = new QPushButton("Generate", _launchWindow);
    generate->setGeometry(45, 220, 100, 40);
    cancel = new QPushButton("Cancel", _launchWindow);
    cancel->setGeometry(155, 220, 100, 40);
    for (int i = 0; i < 2; i++)
    {
        _interSpinBox[i] = new QSpinBox(_launchWindow);
        _timerSpinBox[i] = new QSpinBox(_launchWindow);
        _interSpinBox[i]->setGeometry(60 + (i * 50), 175, 45, 25);
        _timerSpinBox[i]->setGeometry(60 + (i * 50), 85, 45, 25);
        _interSpinBox[i]->setMinimum(0);
        _interSpinBox[i]->setMaximum(1000);
        _timerSpinBox[i]->setMinimum(0);
        _timerSpinBox[i]->setMaximum(1000);
        _interSpinBox[i]->show();
        _timerSpinBox[i]->show();
    }
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(windowLaunchClean()));
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(generate()));
}

void Menu::windowLaunch(void)
{
    if (_launchWindow->isHidden() == TRUE)
        _launchWindow->show();
}

void Menu::windowLaunchClean(void)
{
    if (_launchWindow->isHidden() == FALSE)
        _launchWindow->hide();
}

void        Menu::loadConfSystem()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Load File"),"",tr("PlaneteFactory (*.pf)"));
    if (path.isEmpty())
      return;

    QString settings;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(settings.toUtf8());

    if (json.isNull())
    {
        qDebug() << "NULL";
        return;
    }
    if (json.isObject())
    {
        _parent->setSystem(new System(json.object()));
        _parent->getPlanetCompo()->updateListCompoSys();
        _parent->getCelestial()->updateListPlanet();
        _parent->_currPlanet = NULL;
    }
    else
    {
        qDebug() << "Fichier Json non compatible";
        return;
    }
}

void        Menu::saveConfSystem()
{
    //Init of iterator
    std::list<Component*>::iterator itc_sys;
    std::map<Component*, int>::iterator itc_pla;
    std::list<Planet*>::iterator itp;


    //Choose a file to save
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("PlaneteFactory (*.pf)"));
    if (path.isEmpty())
      return;

    //First get the system
    System *s = _parent->getSystem();

    //On cree l'array component
    QJsonArray component;
    for (itc_sys = s->getComponentList()->begin(); itc_sys != s->getComponentList()->end(); ++itc_sys)
    {
        QJsonObject obj;
        QString name = (*itc_sys)->getName().c_str();

        obj.insert("name", name);
        obj.insert("solid", (*itc_sys)->getSolidTemp());
        obj.insert("gas", (*itc_sys)->getGazeousTemp());
        obj.insert("mass", (*itc_sys)->getMass());
        obj.insert("hardness", (*itc_sys)->getHardness());

        component.append(obj);
    }

    //Create array of all planet
    QJsonArray planete;
    for (itp = s->getPlanetList()->begin(); itp != s->getPlanetList()->end(); ++itp)
    {
        QJsonObject obj;
        QString name = (*itp)->getName().c_str();

        obj.insert("name", name);
        //      obj.insert("type", (*itc)->getSolidTemp());
        obj.insert("radius", (*itp)->getRadius());
        obj.insert("tilt", (*itp)->getTilt());
        obj.insert("distance", (*itp)->getDistance());
        obj.insert("period", (*itp)->getRevo());

        //On cree l'array component de la planete
        QJsonArray planete_component;
        for (itc_pla = (*itp)->getComponentMap()->begin(); itc_pla != (*itp)->getComponentMap()->end(); ++itc_pla)
        {
            QJsonObject planete_obj;

            QString name = itc_pla->first->getName().c_str();
            planete_obj.insert("name", name);
            planete_obj.insert("percent", itc_pla->second);
            planete_component.append(planete_obj);
        }
        obj.insert("composant", planete_component);
        planete.append(obj);
    }

    QJsonObject save;
    save.insert("materials", component);
    save.insert("astres", planete);

    QJsonDocument json;
    json.setObject(save);

    QFile file;
    file.setFileName(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(json.toJson());
    file.close();
}
