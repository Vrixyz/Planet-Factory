#ifndef MYCOMPONENT_HPP
#define MYCOMPONENT_HPP

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
    e_etat      etat(void)const;
    Component * component(void)const;
private:
    Component * _c;
    e_etat      _etat;

    void        etat(e_etat);

};

#endif // MYCOMPONENT_HPP
