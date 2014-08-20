#ifndef PLANETCOMPOBOX_HPP
#define PLANETCOMPOBOX_HPP

#include <QSignalMapper>
#include <QColorDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QListView>
#include <QGroupBox>
#include <QSpinBox>
#include <QDialog>
#include <QWidget>
#include <QLabel>

#include "Component.hpp"

class MainWindow;

class PlanetCompoBox : public QWidget
{
    Q_OBJECT

public:
    PlanetCompoBox(MainWindow *parent = 0);
    ~PlanetCompoBox();

    void createCompoDetails(void);
    void createCompoList(void);
    void updateListCompoSys(void);
    void updateListCompoPla(void);
    void createWindowSysComponent(void);
    void createWindowPlaComponent(void);

    QLabel      *_percentWarning;
    QLabel      *_compoName[7];
    QSpinBox    *_compoValue[7];
    QPushButton *_compoDel[7];
    QPushButton *_compoAdd;

    QListWidget *_listObjects; // liste des composants du systeme
    QLineEdit   *_eName;
    QSpinBox    *_eGazeousTemp;
    QSpinBox    *_eSolidTemp;
    QSpinBox    *_eMass;

    QPushButton *_add;
    QPushButton *_del;
    QPushButton *_edi;

    QPushButton *_winSysAdd;
    QPushButton *_winSysEdi;
    QPushButton *_winSysCan;
    QPushButton *_winPlaAdd;
    QPushButton *_winPlaCan;

    QPushButton *_bColor1;
    QPushButton *_bColor2;

    QColorDialog    *_dColor1;
    QColorDialog    *_dColor2;

    QDialog     *_winSys;
    QDialog     *_winPla;

    QLabel      *_lTitle;

    QListWidget *_listCompo;

    MainWindow  *_parent;

    Component   *_currComponent;

    QLabel      *_lColorHexa1;
    QLabel      *_lColorHexa2;
    QLabel      *_lColor1;
    QLabel      *_lColor2;

private:

signals:

public slots:

    void checkPercentPla();
    void changePercentCompo(int);

    void componentPlaSelected(void);
    void componentSysSelected(void);

    void windowSysEdiCompo(void);
    void windowSysAddCompo(void);
    void windowPlaAddCompo(void);

    void windowSysCloseAndClean(void);
    void windowPlaCloseAndClean(void);

    void addCompoToSys(void);
    void ediCompoToSys(void);
    void delCompoToSys(void);
    void addCompoToPla(void);
    void delCompoToPla(int);

    void setColor1(void);
    void setColor2(void);

};

#endif // PLANETCOMPOBOX_HPP
