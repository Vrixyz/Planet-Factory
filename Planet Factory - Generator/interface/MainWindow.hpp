#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QSpinBox>
#include <QLabel>
#include <QtGui>

#include "PlanetDetailsBox.hpp"
#include "PlanetCompoBox.hpp"
#include "CelestialBox.hpp"
#include "OptionsBox.hpp"
#include "GroupTools.hpp"
#include "Planet.hpp"

Q_DECLARE_METATYPE(PlanetType)

class MainWindow : public QMainWindow
{

    Q_OBJECT
    
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PlanetDetailsBox    *getPlanetDetails(void);
    PlanetCompoBox      *getPlanetCompo(void);
    CelestialBox        *getCelestial(void);
    OptionsBox          *getOptions(void);

    std::list<Planet*>  *_listPlanet;

private:

    PlanetDetailsBox    *_boxPlanetDetails;
    PlanetCompoBox      *_boxPlanetCompo;
    CelestialBox        *_boxCelestial;
    OptionsBox          *_boxOptions;

    GroupTools          *_boxPositionVector;
    GroupTools          *_boxPosition;

protected:

    void                keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_HPP
