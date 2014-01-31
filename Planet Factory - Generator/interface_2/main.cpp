#include "MainWindow.hpp"
#include "include.hpp"

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    MainWindow      *w;

    w = new MainWindow(0);
    w->setFixedSize(1000, 700);
    w->show();

    return a.exec();
}
