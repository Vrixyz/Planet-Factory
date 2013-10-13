#ifndef PLANETCOMPOBOX_HPP
#define PLANETCOMPOBOX_HPP

#include <QPushButton>
#include <QGroupBox>
#include <QWidget>

#include "GroupTools.hpp"

class PlanetCompoBox : public QGroupBox
{

    Q_OBJECT

public:

    PlanetCompoBox(QWidget *parent = 0);
    ~PlanetCompoBox();

private:

    GroupTools   *_boxDetails;
    GroupTools   *_boxList;

signals:
    
public slots:
    
};

#endif // PLANETCOMPOBOX_HPP
