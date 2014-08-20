#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <QJsonObject>

class Component
{

public:

    Component();
    Component(QJsonObject);
    Component(const std::string &);
    Component(Component *c);
    Component(std::string, int, int, int, const std::string &);
    ~Component();

    void setName(std::string);
    void setSolidTemp(int);
    void setGazeousTemp(int);
    void setMass(int);
    void path(const std::string &);
    void setColor1(std::string);
    void setColor2(std::string);

    std::string getName(void);
    int         getSolidTemp(void);
    int         getGazeousTemp(void);
    int         getMass(void);
    const std::string & path(void);
    std::string getColor1(void);
    std::string getColor2(void);

private:

    std::string _name;
    std::string _color1;
    std::string _color2;
    int         _gazeousTemp;
    int         _solidTemp;
    int         _mass;
    std::string _path;

};

#endif // COMPONENT_HPP
