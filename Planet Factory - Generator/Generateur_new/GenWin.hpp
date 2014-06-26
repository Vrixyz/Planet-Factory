#ifndef GENWIN_H
#define GENWIN_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QScrollArea>
#include "Move.hpp"
#include "System.hpp"
#include "Terrain.hpp"

class GenWin : public QWidget
{
    Q_OBJECT
public:
    explicit    GenWin(System *s, QString path, int time, int inter, QWidget *parent = 0);
    void        launch();
    void        step1();
    void        step2();
    void        step3();
    void        connectTerrain();
    void        appendInfo(QString);
signals:

public slots:
    void step2prog();
    void step3prog();

private:
    QProgressBar        *_progressGlobal;
    QLabel              *_GlobalText;
    QProgressBar        *_progressCurrent;
    QLabel              *_CurrentText;
    QScrollArea         *_textArea;
    QLabel              *_textInfo;


    std::list<Terrain*> *_terrains;
    Move                *_move;
    System              *_system;
    QString             _path;
    int                 _iteration;
    int                 _time;
    int                 _inter;
    int                 _nb_thread;
    int                 _thread_term;
};



#endif // GENWIN_H
