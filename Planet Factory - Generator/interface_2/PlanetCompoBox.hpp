#ifndef PLANETCOMPOBOX_HPP
#define PLANETCOMPOBOX_HPP

#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QWidget>
#include <QSlider>
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
    void createWindowComponent(void);
    void updateListCompoSys(void);

    QListWidget *_listObjects;
    QLineEdit   *_eName;
    QSpinBox    *_eGazeousTemp;
    QSpinBox    *_eSolidTemp;
    QSlider     *_eHardness;
    QSpinBox    *_eMass;

    QPushButton *_add;
    QPushButton *_del;
    QPushButton *_edi;
    QPushButton *_winAdd;
    QPushButton *_winCan;

    QDialog     *_win;

    MainWindow  *_parent;

private:

    GroupTools  *_boxPlanet;
    GroupTools  *_boxSystem;

signals:
    
public slots:

    void componentSelected();

    void windowEditCompo(void);
    void windowAddCompo(void);
    void windowCloseAndClean(void);

    void addCompoToSys(void);
    void delCompoToSys(void);

};

#endif // PLANETCOMPOBOX_HPP
