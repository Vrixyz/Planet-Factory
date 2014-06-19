#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QSpinBox>
#include <QLabel>
#include <QtGui>
#include <QFileDialog>

class Menu;

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Menu *_menu;

protected:

public slots:

};

#endif // MAINWINDOW_HPP
