#include "PlanetCompoBox.hpp"
#include "MainWindow.hpp"

PlanetCompoBox::PlanetCompoBox(MainWindow *parent) : QWidget(parent)
{
    QSignalMapper* signalMapperButton;
    QSignalMapper* signalMapperSpinBox;

    _parent = parent;
    setGeometry(218, 331, 756, 243);

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
    infos->setGeometry(0, 0, 362, 24);

    _listObjects = new QListWidget(this);
    _listObjects->setGeometry(394, 0, 362, 207);

    _add = new QPushButton(this);
    _add->setGeometry(394, 212, 114, 30);
    _add->setObjectName("syscompo_add");
    _edi = new QPushButton(this);
    _edi->setGeometry(513, 212, 114, 30);
    _edi->setObjectName("syscompo_edi");
    _del = new QPushButton(this);
    _del->setGeometry(632, 212, 124, 30);
    _del->setObjectName("syscompo_del");

    _compoAdd = new QPushButton(this);
    _compoAdd->setGeometry(0, 213, 362, 30);
    _compoAdd->setObjectName("planetcompo_add");
    _compoAdd->setEnabled(FALSE);

/*    for (int i = 0; i < 7; i++)
    {
        _compoName[i] =  new QLabel("HELLO!", this);
        _compoValue[i] = new QSpinBox(this);
        _compoDel[i] = new QPushButton("Delete", this);
        QObject::connect(_compoDel[i], SIGNAL(clicked()), signalMapperButton, SLOT(map()));
        signalMapperButton->setMapping (_compoDel[i], i) ;
        QObject::connect(_compoValue[i], SIGNAL(valueChanged(int)), signalMapperSpinBox, SLOT(map()));
        signalMapperSpinBox->setMapping (_compoValue[i], i);
    }
    QObject::connect(signalMapperButton, SIGNAL(mapped(int)), this, SLOT(delCompoToPla(int))) ;
    QObject::connect(signalMapperSpinBox, SIGNAL(mapped(int)), this, SLOT(changePercentCompo(int))) ;*/

/*    createWindowSysComponent();
    createWindowPlaComponent();
    createCompoDetails();
    createCompoList();*/

}

PlanetCompoBox::~PlanetCompoBox()
{

}
