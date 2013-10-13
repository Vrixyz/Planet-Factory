#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

class Component
{

public:

    Component();
    ~Component();

    std::string getName(void);
    int         getSolidTemp(void);
    int         getHardness(void);
    int         getGazTemp(void);
    int         getPercent(void);
    int         getMass(void);

    void        setName(std::string);
    void        setSolidTemp(int);
    void        setHardness(int);
    void        setPercent(int);
    void        setGazTemp(int);
    void        setMass(int);

private:

    std::string _name;
    int         _solidTemp;
    int         _gazTemp;
    int         _mass;
    int         _hardness;
    int         _percent;

};

#endif // COMPONENT_HPP
