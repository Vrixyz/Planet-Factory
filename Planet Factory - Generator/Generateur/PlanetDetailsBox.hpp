#ifndef PLANETDETAILSBOX_HPP
#define PLANETDETAILSBOX_HPP

#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>

#include "GroupTools.hpp"
#include "Planet.hpp"

class MainWindow;

class PlanetDetailsBox : public QGroupBox
{

    Q_OBJECT

public:

    PlanetDetailsBox(MainWindow *parent = 0);
    ~PlanetDetailsBox();

    void buildPosition();
    void buildPositionVector();

    void setInfosDetails(Planet*);

    QSpinBox *_ePosX;
    QSpinBox *_ePosY;
    QSpinBox *_ePosZ;
    QSpinBox *_ePosVecX;
    QSpinBox *_ePosVecY;
    QSpinBox *_ePosVecZ;

    QSpinBox *_eRadius;
    QLineEdit *_eName;
    QComboBox *_eType;

    QSpinBox *_eDistance;
    QSpinBox *_eTilt;
    QSpinBox *_eRevo;


private:

    GroupTools  *_boxPosition;
    GroupTools  *_boxPositionVector;

    QLabel *_lName;
    QLabel *_lRadius;
    QLabel *_lType;

    QLabel *_lDistance;
    QLabel *_lTilt;
    QLabel *_lRevo;

    QLabel *_lPosX;
    QLabel *_lPosY;
    QLabel *_lPosZ;
    QLabel *_lPosVecX;
    QLabel *_lPosVecY;
    QLabel *_lPosVecZ;

signals:
    
public slots:
    
};

#endif // PLANETDETAILSBOX_HPP
