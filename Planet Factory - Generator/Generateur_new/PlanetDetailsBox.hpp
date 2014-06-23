#ifndef PLANETDETAILSBOX_HPP
#define PLANETDETAILSBOX_HPP

#include <QRadioButton>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QListView>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QDialog>
#include <QWidget>
#include <QLabel>

class MainWindow;

class PlanetDetailsBox : public QWidget
{

    Q_OBJECT

public:

    PlanetDetailsBox(MainWindow *parent = 0);
    ~PlanetDetailsBox();

/*
    void buildPosition();
    void buildPositionVector();

    void setInfosDetails(Planet*);
*/

    QSpinBox *_eRadius;
    QLineEdit *_eName;
    QComboBox *_eType;

    QSpinBox *_eDistance;
    QSpinBox *_eTilt;
    QSpinBox *_eRevo;

    QRadioButton *_eCentralStar;

private:

signals:

public slots:

};

#endif // PLANETDETAILSBOX_HPP
