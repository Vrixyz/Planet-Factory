#ifndef PLANETCOMPOBOX_HPP
#define PLANETCOMPOBOX_HPP

#include <QSignalMapper>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QListView>
#include <QGroupBox>
#include <QSpinBox>
#include <QDialog>
#include <QWidget>
#include <QLabel>

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
    QSlider     *_eHardness;
    QSpinBox    *_eMass;

    QPushButton *_add;
    QPushButton *_del;
    QPushButton *_edi;

    QPushButton *_winSysAdd;
    QPushButton *_winSysCan;
    QPushButton *_winPlaAdd;
    QPushButton *_winPlaCan;

    QDialog     *_winSys;
    QDialog     *_winPla;

    QListWidget *_listCompo;

    MainWindow  *_parent;

private:

signals:

public slots:

    void checkPercentPla();
    void changePercentCompo(int);

    void componentPlaSelected(void);
    void componentSysSelected(void);

    void windowSysEditCompo(void);
    void windowSysAddCompo(void);
    void windowPlaAddCompo(void);

    void windowSysCloseAndClean(void);
    void windowPlaCloseAndClean(void);

    void addCompoToSys(void);
    void delCompoToSys(void);
    void addCompoToPla(void);
    void delCompoToPla(int);

};

#endif // PLANETCOMPOBOX_HPP
