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

private:

    GroupTools  *_boxPosition;
    GroupTools  *_boxPositionVector;

    QLabel *_lName;
    QLabel *_lRadius;
    QLabel *_lType;
    QLabel *_lPosX;
    QLabel *_lPosY;
    QLabel *_lPosZ;
    QLabel *_lPosVecX;
    QLabel *_lPosVecY;
    QLabel *_lPosVecZ;

    QSpinBox *_ePosX;
    QSpinBox *_ePosY;
    QSpinBox *_ePosZ;
    QSpinBox *_ePosVecX;
    QSpinBox *_ePosVecY;
    QSpinBox *_ePosVecZ;

    QSpinBox *_eRadius;
    QLineEdit *_eName;
    QComboBox *_eType;

signals:
    
public slots:
    
};

#endif // PLANETDETAILSBOX_HPP
