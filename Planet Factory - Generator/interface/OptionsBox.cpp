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
    _load = new QPushButton(this);
    _load->setGeometry(45, 155, 105, 40);
    _load->setText("Load");
    _reset = new QPushButton(this);
    _reset->setGeometry(45, 205, 105, 40);
    _reset->setText("Reset");

    QObject::connect(_launch, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(_save, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(_load, SIGNAL(clicked()), this, SLOT(loadConfSystem()));
    QObject::connect(_reset, SIGNAL(clicked()), qApp, SLOT(quit()));
}

OptionsBox::~OptionsBox()
{
}

void        OptionsBox::loadConfSystem()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.pf)"));
    jsonFileManager json(path.toStdString());
    SolarSystem solar = json.parse<SolarSystem>(J_SYSTEM);
    _parent->setSystem(solar);
    std::cout << "date : " << solar.date() << std::endl;
    std::cout << "nbAstres : " << solar.nbAstre() << std::endl;
    std::cout << "nbMaterials : " << solar.nbMaterial() << std::endl;
}
