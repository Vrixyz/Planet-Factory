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

class MainWindow : public QMainWindow
{

    Q_OBJECT
    
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    PlanetDetailsBox  *_boxPlanetDetails;
    PlanetCompoBox  *_boxPlanetCompo;
    CelestialBox    *_boxCelestial;
    OptionsBox      *_boxOptions;
    GroupTools      *_boxPosition;

    GroupTools *_boxPositionVector;
};

#endif // MAINWINDOW_HPP
