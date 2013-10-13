#include "OptionsBox.hpp"

OptionsBox::OptionsBox(QWidget *parent) : QGroupBox(parent)
{
    setGeometry(5, 405, 195, 290);
    setTitle("Options");

    _launch = new QPushButton(this);
    _launch->setGeometry(45, 55, 105, 40);
    _launch->setText("Launch");
    _reset = new QPushButton(this);
    _reset->setGeometry(45, 205, 105, 40);
    _reset->setText("Reset");
    _save = new QPushButton(this);
    _save->setGeometry(45, 105, 105, 40);
    _save->setText("Save");
    _load = new QPushButton(this);
    _load->setGeometry(45, 155, 105, 40);
    _load->setText("Load");
}

OptionsBox::~OptionsBox()
{
}
