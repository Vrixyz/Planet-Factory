#ifndef PLANETDETAILSBOX_HPP
#define PLANETDETAILSBOX_HPP

#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>

#include "GroupTools.hpp"

class PlanetDetailsBox : public QGroupBox
{

    Q_OBJECT

public:

    PlanetDetailsBox(QWidget *parent = 0);
    ~PlanetDetailsBox();

    void buildPosition();
    void buildPositionVector();

private:

    GroupTools  *_boxPosition;
    GroupTools  *_boxPositionVector;

    QLabel *lName;
    QLabel *lRadius;
    QLabel *lType;
    QLabel *lPosX;
    QLabel *lPosY;
    QLabel *lPosZ;
    QLabel *lPosVecX;
    QLabel *lPosVecY;
    QLabel *lPosVecZ;

    QSpinBox *ePosX;
    QSpinBox *ePosY;
    QSpinBox *ePosZ;
    QSpinBox *ePosVecX;
    QSpinBox *ePosVecY;
    QSpinBox *ePosVecZ;

    QLineEdit *eRadius;
    QLineEdit *eName;
    QComboBox *eType;

signals:
    
public slots:
    
};

#endif // PLANETDETAILSBOX_HPP
