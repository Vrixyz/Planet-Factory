#ifndef CELESTIALBOX_HPP
#define CELESTIALBOX_HPP

#include <QPushButton>
#include <QListWidget>
#include <QListView>
#include <QGroupBox>
#include <QWidget>

#include "Planet.hpp"

class MainWindow;

class CelestialBox : public QGroupBox
{

    Q_OBJECT

public:

    CelestialBox(MainWindow *parent = 0);
    ~CelestialBox();

    void cleanAllFields();
    void updateListPlanet();

private:

    QListWidget *_listObjects;
    QPushButton *_add;
    QPushButton *_del;

    MainWindow  *_parent;
    
signals:
    
public slots:

    void        addObject();
    void        delObject();
    void        planetSelected(QListWidgetItem *);

};

#endif // CELESTIALBOX_HPP
