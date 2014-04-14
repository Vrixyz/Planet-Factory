#ifndef OPTIONSBOX_HPP
#define OPTIONSBOX_HPP

#include <QApplication>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QWidget>

#include "Generator.h"

class MainWindow;

class OptionsBox : public QGroupBox
{

    Q_OBJECT

public:

    OptionsBox(MainWindow *parent = 0);
    ~OptionsBox();

    void    createWindowLaunch();

private:

    MainWindow  *_parent;

    QPushButton *_launch;
    QPushButton *_reset;
    QPushButton *_save;
    QPushButton *_load;

    QDialog     *_launchWindow;
    QSpinBox    *_timerSpinBox[4];
    QSpinBox    *_interSpinBox[4];

signals:
    
public slots:

    void    windowLaunchClean();
    void    loadConfSystem();
    void    saveConfSystem();
    void    windowLaunch();
    void    resetAll();
    void    generate();

};

#endif // OPTIONSBOX_HPP