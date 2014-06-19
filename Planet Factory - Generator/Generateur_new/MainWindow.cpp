#include "MainWindow.hpp"
#include "Menu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _menu = new Menu(this);
    _menu->setGeometry(50,330,100,210);
    _menu->show();
}

MainWindow::~MainWindow()
{
}
