#ifndef PLANETCOMPOBOX_HPP
#define PLANETCOMPOBOX_HPP

#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QWidget>
#include <QLabel>

#include "GroupTools.hpp"
#include "Component.hpp"

class MainWindow;

class PlanetCompoBox : public QGroupBox
{

    Q_OBJECT

public:

    PlanetCompoBox(MainWindow *parent = 0);
    ~PlanetCompoBox();

    void createCompoDetails(void);
    void createCompoList(void);

    QLineEdit   *_eName;
    QSpinBox    *_eGazeousTemp;
    QSpinBox    *_eSolidTemp;
    QSpinBox    *_eHardness;

private:

    GroupTools  *_boxDetails;
    GroupTools  *_boxList;

    QLabel      *_lName;
    QLabel      *_lGazeousTemp;
    QLabel      *_lSolidTemp;
    QLabel      *_lHardness;
    QLabel      *_lMass;

signals:
    
public slots:
    
};

#endif // PLANETCOMPOBOX_HPP
