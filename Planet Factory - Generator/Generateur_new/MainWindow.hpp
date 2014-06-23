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
#include "Menu.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Menu *_menu;
    CelestialBox *_celestialBox;
    PlanetCompoBox *_planetCompoBox;
    PlanetDetailsBox *_planetDetailsBox;

protected:

public slots:

};

#endif // MAINWINDOW_HPP
