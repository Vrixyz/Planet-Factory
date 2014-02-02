#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

class Component
{

public:

    Component();
    Component(const std::string &);
    Component(std::string, int, int, int, int, const std::string &);
    ~Component();

    void setName(std::string);
    void setSolidTemp(int);
    void setGazeousTemp(int);
    void setHardness(int);
    void setPercent(int);
    void setMass(int);
    void path(const std::string &);

    std::string getName(void);
    int         getSolidTemp(void);
    int         getGazeousTemp(void);
    int         getHardness(void);
    int         getPercent(void);
    int         getMass(void);
    const std::string & path(void);

private:

    std::string _name;
    int         _gazeousTemp;
    int         _solidTemp;
    int         _hardness;
    int         _percent;
    int         _mass;
    std::string _path;

};

#endif // COMPONENT_HPP
