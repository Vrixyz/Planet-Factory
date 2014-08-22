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
#include "Planet.hpp"
#include "System.hpp"
#include "Menu.hpp"

#ifdef __linux__
    #define TRUE true
    #define FALSE false
#endif



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PlanetDetailsBox    *getPlanetDetails(void);
    PlanetCompoBox      *getPlanetCompo(void);
    CelestialBox        *getCelestial(void);
    Menu                *getMenu(void);
    Planet              *getCurrPlanet(void);
    System              *getSystem();
    void                setSystem(System *);

    Planet              *_currPlanet;

private:

    PlanetDetailsBox    *_boxPlanetDetails;
    PlanetCompoBox      *_boxPlanetCompo;
    CelestialBox        *_boxCelestial;
    Menu                *_menu;

    System              *_system;

protected:

    void                keyPressEvent(QKeyEvent *event);

public slots:

};

#endif // MAINWINDOW_HPP
