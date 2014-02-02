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

    QObject::connect(_launch, SIGNAL(clicked()), _parent, SLOT(createLaunchWindow()));
    QObject::connect(_save, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(_load, SIGNAL(clicked()), this, SLOT(loadConfSystem()));
    QObject::connect(_reset, SIGNAL(clicked()), qApp, SLOT(quit()));
}

OptionsBox::~OptionsBox()
{
}

void        OptionsBox::loadConfSystem()
{
}
