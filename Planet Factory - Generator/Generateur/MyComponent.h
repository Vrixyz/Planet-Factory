#ifndef MYCOMPONENT_H
#define MYCOMPONENT_H

#include "Component.hpp"

enum e_etat
{
    LIQUID,
    SOLID,
    GAZ
};

class MyComponent
{
public:
    MyComponent();
    void    c(Component * c);
private:
    Component * _c;
    e_etat      _etat;
};

#endif // MYCOMPONENT_H
