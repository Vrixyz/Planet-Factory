#include "OptionsBox.hpp"
#include "MainWindow.hpp"

OptionsBox::OptionsBox(MainWindow *parent) : QGroupBox(parent), _parent(parent)
{
    setGeometry(5, 405, 195, 290);
    setTitle("Options");

    _launch = new QPushButton(this);
    _launch->setGeometry(45, 55, 105, 40);
    _launch->setText("Launch");
    _save = new QPushButton(this);
    _save->setGeometry(45, 105, 105, 40);
    _save->setText("Save");
    _save->setEnabled(TRUE);
    _load = new QPushButton(this);
    _load->setGeometry(45, 155, 105, 40);
    _load->setText("Load");
    _load->setEnabled(TRUE);
    _reset = new QPushButton(this);
    _reset->setGeometry(45, 205, 105, 40);
    _reset->setText("Reset");
    _reset->setEnabled(FALSE);

    _launchWindow = new QDialog();
    _launchWindow->setFixedSize(300, 275);
    _launchWindow->hide();
    createWindowLaunch();

    QObject::connect(_launch, SIGNAL(clicked()), this, SLOT(windowLaunch()));
    QObject::connect(_save, SIGNAL(clicked()), this, SLOT(saveConfSystem()));
    QObject::connect(_load, SIGNAL(clicked()), this, SLOT(loadConfSystem()));
    QObject::connect(_reset, SIGNAL(clicked()), qApp, SLOT(quit()));
}

OptionsBox::~OptionsBox()
{
}

void OptionsBox::generate()
{
    _launchWindow->hide();
    QString path = QFileDialog::getExistingDirectory(this, tr("Chose save dir"));
    if (path.isEmpty())
      return;

    System *s = _parent->getSystem();
    s->initJson(path);
    s->endJson(path);

    //s->evo();
}

void OptionsBox::createWindowLaunch(void)
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
    timerSub = new QLabel(" Years       Months     Weeks       Days", _launchWindow);
    timerSub->setGeometry(65, 60, 300, 25);
    inter = new QLabel("Interval de génération :", _launchWindow);
    inter->setGeometry(0, 130, 300, 25);
    inter->setAlignment(Qt::AlignCenter);
    interSub = new QLabel(" Years       Months     Weeks       Days", _launchWindow);
    interSub->setGeometry(65, 150, 300, 25);
    generate = new QPushButton("Generate", _launchWindow);
    generate->setGeometry(45, 220, 100, 40);
    cancel = new QPushButton("Cancel", _launchWindow);
    cancel->setGeometry(155, 220, 100, 40);
    for (int i = 0; i < 4; i++)
    {
        _interSpinBox[i] = new QSpinBox(_launchWindow);
        _timerSpinBox[i] = new QSpinBox(_launchWindow);
        _interSpinBox[i]->setGeometry(60 + (i * 50), 85, 45, 25);
        _timerSpinBox[i]->setGeometry(60 + (i * 50), 175, 45, 25);
        _interSpinBox[i]->show();
        _timerSpinBox[i]->show();
    }
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(windowLaunchClean()));
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(generate()));
}

void OptionsBox::windowLaunch(void)
{
    if (_launchWindow->isHidden() == TRUE)
        _launchWindow->show();
}

void OptionsBox::windowLaunchClean(void)
{
    if (_launchWindow->isHidden() == FALSE)
        _launchWindow->hide();
}

void        OptionsBox::loadConfSystem()
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

    if(json.isNull())
    {
        qDebug() << "NULL";
        return;
    }
    if(json.isObject())
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

void        OptionsBox::saveConfSystem()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("PlaneteFactory (*.pf)"));
    if (path.isEmpty())
      return;

    System *s = _parent->getSystem();
    std::list<Component*>::iterator itc_sys;
    std::map<Component*, int>::iterator itc_pla;
    std::list<Planet*>::iterator itp;

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

    //On cree l'array planete
    QJsonArray planete;
    for (itp = s->getPlanetList()->begin(); itp != s->getPlanetList()->end(); ++itp)
    {
        QJsonObject obj;

        QString name = (*itp)->getName().c_str();
        obj.insert("name", name);
//        obj.insert("type", (*itc)->getSolidTemp());
        obj.insert("radius", (*itp)->getRadius());

        int *vec = (*itp)->getPositionVec();
        QJsonObject vector;
        vector.insert("x", vec[0]);
        vector.insert("y", vec[1]);
        vector.insert("z", vec[2]);
        obj.insert("vec", vector);

        int *pos = (*itp)->getPosition();
        QJsonObject position;
        position.insert("x", pos[0]);
        position.insert("y", pos[1]);
        position.insert("z", pos[2]);
        obj.insert("pos", position);

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
