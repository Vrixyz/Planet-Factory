#include "PlanetDetailsBox.hpp"
#include "MainWindow.hpp"

PlanetDetailsBox::PlanetDetailsBox(MainWindow *parent) : QWidget(parent)
{
    _parent = parent;
    setGeometry(538, 22, 442, 270);

    QLabel *label_name_planettype = new QLabel(this);
    label_name_planettype->setPixmap(QPixmap(":/res/bg-planetdetails.png"));
    label_name_planettype->setGeometry(0, 0, 435, 260);

    _eName = new QLineEdit(this);
    _eRadius = new QSpinBox(this);
    _eType = new QComboBox(this);
    _eDistance = new QSpinBox(this);
    _eTilt = new QSpinBox(this);
    _eRevo = new QSpinBox(this);
    _eRota = new QSpinBox(this);
    _eCentralStar = new QRadioButton(this);

    _eName->setGeometry(0, 40, 215, 25);
    _eName->setText("");
    _eName->setAlignment(Qt::AlignHCenter);

    _eRadius->setGeometry(0, 100, 215, 25);
    _eRadius->setAlignment(Qt::AlignHCenter);
    _eRadius->setMinimum(1);
    _eRadius->setMaximum(1000000);
    _eRadius->setValue(1);

    _eDistance->setGeometry(0, 160, 215, 25);
    _eDistance->setMinimum(0);
    _eDistance->setMaximum(1000000);
    _eDistance->setValue(0);
    _eDistance->setAlignment(Qt::AlignHCenter);

    _eTilt->setGeometry(220, 100, 215, 25);
    _eTilt->setMinimum(0);
    _eTilt->setMaximum(1000000);
    _eTilt->setValue(0);
    _eTilt->setAlignment(Qt::AlignHCenter);

    _eRevo->setGeometry(220, 160, 215, 25);
    _eRevo->setMinimum(0);
    _eRevo->setMaximum(1000000);
    _eRevo->setValue(0);
    _eRevo->setAlignment(Qt::AlignHCenter);

    _eType->setGeometry(220, 40, 215, 25);
    _eType->addItem("Star");
    _eType->addItem("Telluric planet");
    _eType->addItem("Gazeous planet");
    _eType->addItem("Asteroid");
    _eType->setEditable(true);
    _eType->lineEdit()->setReadOnly(true);
    _eType->lineEdit()->setAlignment(Qt::AlignHCenter);
    for (int i = 0; i < _eType->count(); ++i)
        _eType->setItemData(i, Qt::AlignHCenter, Qt::TextAlignmentRole);

    _eCentralStar->setGeometry(385, 201, 15, 15);
    if (parent->getCurrPlanet() != NULL)
        _eCentralStar->setEnabled(FALSE);

    _eRota->setGeometry(0, 220, 215, 25);
    _eRota->setMinimum(0);
    _eRota->setMaximum(1000000);
    _eRota->setValue(0);
    _eRota->setAlignment(Qt::AlignHCenter);
}

PlanetDetailsBox::~PlanetDetailsBox()
{
}

void PlanetDetailsBox::setInfosDetails(Planet* toSet)
{
    toSet->setName(_eName->text());
    toSet->setRadius(_eRadius->value());
    toSet->setDistance(_eDistance->value());
    toSet->setTilt(_eTilt->value());
    toSet->setRevo(_eRevo->value());
    toSet->setRota(_eRota->value());
    if (_eType->currentText().toStdString() == "Star")
      toSet->setType(STAR);
    else if (_eType->currentText().toStdString() == "Telluric planet")
      toSet->setType(TELLURIC);
    else if (_eType->currentText().toStdString() == "Gazeous planet")
      toSet->setType(GAZEOUS);
    else if (_eType->currentText().toStdString() == "Asteroid")
      toSet->setType(ASTEROID);
}
