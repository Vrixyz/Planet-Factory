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
    void cleanAllFields(void);

    QListWidget   *_listObjects;
    QLineEdit   *_eName;
    QSpinBox    *_eGazeousTemp;
    QSpinBox    *_eSolidTemp;
    QSlider     *_eHardness;
    QSpinBox    *_eMass;

    QPushButton *_add;
    QPushButton *_del;
    QPushButton *_edi;

    QDialog     *_win;

    MainWindow  *_parent;

private:

    GroupTools  *_boxPlanet;
    GroupTools  *_boxSystem;

signals:
    
public slots:

    void cleanWindowCompoSys(void);
    void loadWindowCompoSys(void);

    void addCompo(void);
    void addCompoToSys(void);
    void delCompo(void);
    void componentSelected(QListWidgetItem *);

};

#endif // PLANETCOMPOBOX_HPP
