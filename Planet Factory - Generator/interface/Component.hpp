#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

class Component
{

public:

    Component();
    ~Component();

    void setName(std::string);
    void setSolidTemp(int);
    void setGazeousTemp(int);
    void setHardness(int);
    void setMass(int);

    std::string getName(void);
    int         getSolidTemp(void);
    int         getGazeousTemp(void);
    int         getHardness(void);
    int         getMass(void);

private:

    std::string _name;
    int         _gazeousTemp;
    int         _solidTemp;
    int         _hardness;
    int         _mass;

};

#endif // COMPONENT_HPP
