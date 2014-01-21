#ifndef OPTIONSBOX_HPP
#define OPTIONSBOX_HPP

#include <QApplication>
#include <QPushButton>
#include <QGroupBox>
#include <QWidget>

class MainWindow;

class OptionsBox : public QGroupBox
{

    Q_OBJECT

public:

    OptionsBox(MainWindow *parent = 0);
    ~OptionsBox();

private:
    MainWindow  *_parent;
    QPushButton *_launch;
    QPushButton *_reset;
    QPushButton *_save;
    QPushButton *_load;

signals:
    
public slots:
    void         loadConfSystem();
};

#endif // OPTIONSBOX_HPP
