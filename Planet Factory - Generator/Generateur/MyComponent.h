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

    void        etat(e_etat);

    e_etat      etat(void)const;
    Component * component(void)const;
};

#endif // MYCOMPONENT_H
