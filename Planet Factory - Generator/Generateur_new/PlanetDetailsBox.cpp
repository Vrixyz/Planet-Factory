#include "PlanetDetailsBox.hpp"
#include "MainWindow.hpp"

PlanetDetailsBox::PlanetDetailsBox(MainWindow *parent) : QWidget(parent)
{
    setGeometry(538, 42, 442, 241);

    QLabel *label_name_planettype = new QLabel(this);
    label_name_planettype->setPixmap(QPixmap(":/res/name_planettype.png"));
    label_name_planettype->setGeometry(0, 20, 435, 13);
    QLabel *label_radius_degrees = new QLabel(this);
    label_radius_degrees->setPixmap(QPixmap(":/res/radius_degrees.png"));
    label_radius_degrees->setGeometry(0, 80, 435, 13);
    QLabel *label_distance_revolution = new QLabel(this);
    label_distance_revolution->setPixmap(QPixmap(":/res/distance_revolution.png"));
    label_distance_revolution->setGeometry(0, 140, 435, 14);
    QLabel *label_censtral_star = new QLabel(this);
    label_censtral_star->setPixmap(QPixmap(":/res/central_star.png"));
    label_censtral_star->setGeometry(0, 209, 435, 11);

    _eName = new QLineEdit(this);
    _eRadius = new QSpinBox(this);
    _eType = new QComboBox(this);
    _eDistance = new QSpinBox(this);
    _eTilt = new QSpinBox(this);
    _eRevo = new QSpinBox(this);
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
    _eDistance->setMinimum(1);
    _eDistance->setMaximum(1000000);
    _eDistance->setValue(1);
    _eDistance->setAlignment(Qt::AlignHCenter);

    _eTilt->setGeometry(220, 100, 215, 25);
    _eTilt->setMinimum(1);
    _eTilt->setMaximum(1000000);
    _eTilt->setValue(1);
    _eTilt->setAlignment(Qt::AlignHCenter);

    _eRevo->setGeometry(220, 160, 215, 25);
    _eRevo->setMinimum(1);
    _eRevo->setMaximum(1000000);
    _eRevo->setValue(1);
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

    _eCentralStar->setGeometry(270, 207, 15, 15);
}

PlanetDetailsBox::~PlanetDetailsBox()
{
}

void PlanetDetailsBox::setInfosDetails(Planet* toSet)
{
    toSet->setName(_eName->text().toStdString());
    toSet->setRadius(_eRadius->value());
    toSet->setDistance(_eDistance->value());
    toSet->setTilt(_eTilt->value());
    toSet->setRevo(_eRevo->value());
    if (_eType->currentText().toStdString() == "Star")
      toSet->setType(STAR);
    else if (_eType->currentText().toStdString() == "Telluric planet")
      toSet->setType(TELLURIC);
    else if (_eType->currentText().toStdString() == "Gazeous planet")
      toSet->setType(GAZEOUS);
    else if (_eType->currentText().toStdString() == "Asteroid")
      toSet->setType(ASTEROID);
}