#include "PlanetDetailsBox.hpp"

PlanetDetailsBox::PlanetDetailsBox(QWidget *parent) : QGroupBox(parent)
{
    setGeometry(305, 105, 690, 295);
    setTitle("Planet Detail");

    _boxPosition = new GroupTools(parent);
    _boxPosition->setGeometry(315, 180, 330, 210);
    _boxPosition->setTitle("Position");

    _boxPositionVector = new GroupTools(parent);
    _boxPositionVector->setGeometry(655, 180, 330, 210);
    _boxPositionVector->setTitle("Position Vector");

    lRadius = new QLabel("Radius (km) :", this);
    lType = new QLabel("Planet Type :", this);
    lName = new QLabel("Name :", this);
    eRadius = new QLineEdit(this);
    eType = new QComboBox(this);
    eName = new QLineEdit(this);

    lType->setGeometry(462, 43, 150, 15);
    lRadius->setGeometry(211, 43, 100, 15);
    lName->setGeometry(10, 43, 100, 15);

    eName->setGeometry(63, 35, 100, 30);
    eName->setText("Planet A");
    eRadius->setGeometry(302, 35, 100, 30);
    eRadius->setText("42000");
    eType->setGeometry(557, 35, 130, 30);
    eType->addItem("Star");
    eType->addItem("Telluric planet");
    eType->addItem("Gazeous planet");
    eType->addItem("Asteroid");

    buildPosition();
    buildPositionVector();
}

PlanetDetailsBox::~PlanetDetailsBox()
{
}

void PlanetDetailsBox::buildPosition()
{
    ePosX = new QSpinBox(_boxPosition);
    ePosY = new QSpinBox(_boxPosition);
    ePosZ = new QSpinBox(_boxPosition);
    lPosX = new QLabel("X :", _boxPosition);
    lPosY = new QLabel("Y :", _boxPosition);
    lPosZ = new QLabel("Z :", _boxPosition);

    ePosX->setGeometry(60, 53, 70, 25);
    ePosY->setGeometry(60, 103, 70, 25);
    ePosZ->setGeometry(60, 153, 70, 25);
    lPosX->setGeometry(30, 58, 70, 15);
    lPosY->setGeometry(30, 108, 70, 15);
    lPosZ->setGeometry(30, 158, 70, 15);
}

void PlanetDetailsBox::buildPositionVector()
{
    ePosVecX = new QSpinBox(_boxPositionVector);
    ePosVecY = new QSpinBox(_boxPositionVector);
    ePosVecZ = new QSpinBox(_boxPositionVector);
    lPosVecX = new QLabel("X :", _boxPositionVector);
    lPosVecY = new QLabel("Y :", _boxPositionVector);
    lPosVecZ = new QLabel("Z :", _boxPositionVector);

    ePosVecX->setGeometry(60, 53, 70, 25);
    ePosVecY->setGeometry(60, 103, 70, 25);
    ePosVecZ->setGeometry(60, 153, 70, 25);
    lPosVecX->setGeometry(30, 58, 70, 15);
    lPosVecY->setGeometry(30, 103, 70, 15);
    lPosVecZ->setGeometry(30, 153, 70, 15);
}
