#ifndef CELESTIALBOX_HPP
#define CELESTIALBOX_HPP

#include <QPushButton>
#include <QListWidget>
#include <QListView>
#include <QGroupBox>
#include <QWidget>

class MainWindow;

class CelestialBox : public QGroupBox
{

    Q_OBJECT

public:

    CelestialBox(MainWindow *parent = 0);
    ~CelestialBox();

private:

    QListWidget   *_listObjects;
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
