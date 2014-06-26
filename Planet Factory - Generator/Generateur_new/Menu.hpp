#ifndef MENU_HPP
#define MENU_HPP

#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QSpinBox>
#include <QLabel>
#include <QtGui>

#include "Generator.hpp"

class MainWindow;

class Menu : public QWidget
{

    Q_OBJECT

public:

    Menu(MainWindow *parent = 0);
    ~Menu();

    void    createWindowLaunch();

private:

    QPushButton* _save;
    QPushButton* _load;
    QPushButton* _reset;
    QPushButton* _launch;
    QPushButton* _facebook;
    QPushButton* _twitter;

    QDialog     *_launchWindow;
    QSpinBox    *_timerSpinBox[4];
    QSpinBox    *_interSpinBox[4];

    MainWindow  *_parent;

signals:

public slots:

    void linkFacebook();
    void linkTwitter();

    void    windowLaunchClean();
    void    loadConfSystem();
    void    saveConfSystem();
    void    windowLaunch();
    void    resetAll();
    void    generate();

};

#endif // MENU_HPP
