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
    MyComponent(Component *c, int p, e_etat e);

    //** Setter **//
    void        component(Component * c);
    void        etat(e_etat);
    void        percent(int p);

    //** Getter **//
    e_etat      etat(void)const;
    Component * component(void)const;
    int       percent(void)const;
private:
    Component * _c;
    int       _p;
    e_etat      _etat;


};

#endif // MYCOMPONENT_HPP
