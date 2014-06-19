#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "MainWindow.hpp"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
private:
    QPushButton* _save;
    QPushButton* _load;
    QPushButton* _reset;
    QPushButton* _launch;
    QPushButton* _facebook;
    QPushButton* _twitter;
signals:

public slots:
    void linkFacebook();
    void linkTwitter();
};

#endif // MENU_H
