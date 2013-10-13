#ifndef CELESTIALBOX_HPP
#define CELESTIALBOX_HPP

#include <QPushButton>
#include <QListView>
#include <QGroupBox>
#include <QWidget>

class CelestialBox : public QGroupBox
{

    Q_OBJECT

public:

    CelestialBox(QWidget *parent = 0);
    ~CelestialBox();

private:

    QListView    *_listObjects;
    QPushButton  *_add;
    QPushButton  *_del;
    
signals:
    
public slots:
    
};

#endif // CELESTIALBOX_HPP
