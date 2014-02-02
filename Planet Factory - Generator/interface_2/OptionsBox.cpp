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
    _save->setEnabled(FALSE);
    _load = new QPushButton(this);
    _load->setGeometry(45, 155, 105, 40);
    _load->setText("Load");
    _load->setEnabled(FALSE);
    _reset = new QPushButton(this);
    _reset->setGeometry(45, 205, 105, 40);
    _reset->setText("Reset");
    _reset->setEnabled(FALSE);

//    QObject::connect(_launch, SIGNAL(clicked()), _parent, SLOT(createLaunchWindow()));
//    QObject::connect(_save, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(_launch, SIGNAL(clicked()), this, SLOT(generate()));
    QObject::connect(_save, SIGNAL(clicked()), this, SLOT(saveConfSystem()));
    QObject::connect(_load, SIGNAL(clicked()), this, SLOT(loadConfSystem()));
    QObject::connect(_reset, SIGNAL(clicked()), qApp, SLOT(quit()));
}

OptionsBox::~OptionsBox()
{
}

void        OptionsBox::generate()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Chose save dir"));
    if (path.isEmpty())
      return;

    System *s = _parent->getSystem();
    s->initJson(path);
    s->endJson(path);

    //s->evo();
}


void        OptionsBox::loadConfSystem()
{
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

        //toto
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

            planete_component.append(planete_obj);
        }
        obj.insert("materials", planete_component);

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
