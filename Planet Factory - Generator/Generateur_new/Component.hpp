#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <QJsonObject>

class Component
{

public:

    Component();
    Component(QJsonObject);
    Component(const QString &);
    Component(Component *c);
    Component(QString, int, int, int, const QString &);
    ~Component();

    void setName(QString);
    void setSolidTemp(int);
    void setGazeousTemp(int);
    void setMass(int);
    void path(const QString &);
    void setColor1(QString);
    void setColor2(QString);

    QString getName(void);
    int         getSolidTemp(void);
    int         getGazeousTemp(void);
    int         getMass(void);
    const QString & path(void);
    QString getColor1(void);
    QString getColor2(void);

private:

    QString _name;
    QString _color1;
    QString _color2;
    int         _gazeousTemp;
    int         _solidTemp;
    int         _mass;
    QString _path;

};

#endif // COMPONENT_HPP
