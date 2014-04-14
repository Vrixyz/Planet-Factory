#include "PlanetDetailsBox.hpp"
#include "MainWindow.hpp"

PlanetDetailsBox::PlanetDetailsBox(MainWindow *parent) : QGroupBox(parent)
{
    setGeometry(305, 105, 690, 295);
    setTitle("Planet Detail");

/*
    _boxPosition = new GroupTools(parent);
    _boxPosition->setGeometry(315, 180, 330, 210);
    _boxPosition->setTitle("Position");

    _boxPositionVector = new GroupTools(parent);
    _boxPositionVector->setGeometry(655, 180, 330, 210);
    _boxPositionVector->setTitle("Position Vector");
*/

    _lName = new QLabel("Name :", this);
    _lRadius = new QLabel("Radius (km) :", this);
    _lType = new QLabel("Planet Type :", this);
    _lDistance = new QLabel("Distance (AU) :", this);
    _lTilt = new QLabel("Tilt (°) :", this);
    _lRevo = new QLabel("Period of revolution (days) :", this);

    _eName = new QLineEdit(this);
    _eRadius = new QSpinBox(this);
    _eType = new QComboBox(this);
    _eDistance = new QSpinBox(this);
    _eTilt = new QSpinBox(this);
    _eRevo = new QSpinBox(this);

    _lName->setGeometry(60, 43, 100, 15);
    _lRadius->setGeometry(60, 143, 100, 15);
    _lDistance->setGeometry(60, 243, 100, 15);
    _lType->setGeometry(330, 43, 150, 15);
    _lTilt->setGeometry(330, 143, 100, 15);
    _lRevo->setGeometry(330, 243, 150, 15);

    _eName->setGeometry(150, 35, 100, 30);
    _eName->setText("");
    _eRadius->setGeometry(150, 135, 100, 30);
    _eRadius->setMinimum(1);
    _eRadius->setMaximum(1000000);
    _eRadius->setValue(1);
    _eDistance->setGeometry(150, 235, 100, 30);
    _eDistance->setMinimum(1);
    _eDistance->setMaximum(1000000);
    _eDistance->setValue(1);
    _eTilt->setGeometry(502, 135, 100, 30);
    _eTilt->setMinimum(1);
    _eTilt->setMaximum(1000000);
    _eTilt->setValue(1);
    _eRevo->setGeometry(502, 235, 100, 30);
    _eRevo->setMinimum(1);
    _eRevo->setMaximum(1000000);
    _eRevo->setValue(1);

    _eType->setGeometry(474, 35, 130, 30);
    _eType->addItem("Star");
    _eType->addItem("Telluric planet");
    _eType->addItem("Gazeous planet");
    _eType->addItem("Asteroid");

//    buildPosition();
//    buildPositionVector();
}

PlanetDetailsBox::~PlanetDetailsBox()
{
}

void PlanetDetailsBox::buildPosition()
{
    _ePosX = new QSpinBox(_boxPosition);
    _ePosY = new QSpinBox(_boxPosition);
    _ePosZ = new QSpinBox(_boxPosition);
    _lPosX = new QLabel("X :", _boxPosition);
    _lPosY = new QLabel("Y :", _boxPosition);
    _lPosZ = new QLabel("Z :", _boxPosition);

    _ePosX->setGeometry(60, 53, 100, 25);
    _ePosX->setMinimum(-100000);
    _ePosX->setMaximum(100000);
    _ePosY->setGeometry(60, 103, 100, 25);
    _ePosY->setMinimum(-100000);
    _ePosY->setMaximum(100000);
    _ePosZ->setGeometry(60, 153, 100, 25);
    _ePosZ->setMinimum(-100000);
    _ePosZ->setMaximum(100000);

    _lPosX->setGeometry(30, 58, 20, 15);
    _lPosY->setGeometry(30, 108, 20, 15);
    _lPosZ->setGeometry(30, 158, 20, 15);
}

void PlanetDetailsBox::buildPositionVector()
{
    _ePosVecX = new QSpinBox(_boxPositionVector);
    _ePosVecY = new QSpinBox(_boxPositionVector);
    _ePosVecZ = new QSpinBox(_boxPositionVector);
    _lPosVecX = new QLabel("X :", _boxPositionVector);
    _lPosVecY = new QLabel("Y :", _boxPositionVector);
    _lPosVecZ = new QLabel("Z :", _boxPositionVector);

    _ePosVecX->setGeometry(60, 53, 100, 25);
    _ePosVecX->setMinimum(-100000);
    _ePosVecX->setMaximum(100000);
    _ePosVecY->setGeometry(60, 103, 100, 25);
    _ePosVecY->setMinimum(-100000);
    _ePosVecY->setMaximum(100000);
    _ePosVecZ->setGeometry(60, 153, 100, 25);
    _ePosVecZ->setMinimum(-100000);
    _ePosVecZ->setMaximum(100000);

    _lPosVecX->setGeometry(30, 58, 20, 15);
    _lPosVecY->setGeometry(30, 108, 20, 15);
    _lPosVecZ->setGeometry(30, 158, 20, 15);
}

void PlanetDetailsBox::setInfosDetails(Planet* toSet)
{
    toSet->setName(_eName->text().toStdString());
    toSet->setRadius(_eRadius->value());
    toSet->setDistance(_eDistance->value());
    toSet->setTilt(_eTilt->value());
    toSet->setRevo(_eRevo->value());
//    toSet->setPosition(_ePosX->value(), _ePosY->value(), _ePosZ->value());
//    toSet->setPositionVec(_ePosVecX->value(), _ePosVecY->value(), _ePosVecZ->value());
    if (_eType->currentText().toStdString() == "Star")
      toSet->setType(STAR);
    else if (_eType->currentText().toStdString() == "Telluric planet")
      toSet->setType(TELLURIC);
    else if (_eType->currentText().toStdString() == "Gazeous planet")
      toSet->setType(GAZEOUS);
    else if (_eType->currentText().toStdString() == "Asteroid")
      toSet->setType(ASTEROID);
}