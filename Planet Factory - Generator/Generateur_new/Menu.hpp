#ifndef MENU_HPP
#define MENU_HPP

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QSpinBox>
#include <QLabel>
#include <QtGui>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = 0);
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

#endif // MENU_HPP
