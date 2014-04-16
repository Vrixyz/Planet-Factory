#include "MainWindow.hpp"
#include "include.hpp"

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    MainWindow      *w;

    QFile File("./res/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    a.setStyleSheet(StyleSheet);

    w = new MainWindow(0);
    //w->setWindowFlags(Qt::FramelessWindowHint);
    w->setFixedSize(1000, 700);
    w->show();

    return a.exec();
}
