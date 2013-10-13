#ifndef OPTIONSBOX_HPP
#define OPTIONSBOX_HPP

#include <QGroupBox>
#include <QPushButton>
#include <QWidget>

class OptionsBox : public QGroupBox
{

    Q_OBJECT

public:

    OptionsBox(QWidget *parent = 0);
    ~OptionsBox();

private:

    QPushButton *_launch;
    QPushButton *_reset;
    QPushButton *_save;
    QPushButton *_load;

signals:
    
public slots:
    
};

#endif // OPTIONSBOX_HPP
