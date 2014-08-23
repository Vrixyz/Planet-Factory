#ifndef MYCOMPONENT_HPP
#define MYCOMPONENT_HPP

#include "Component.hpp"

enum e_etat
{
    SOLID,
    LIQUID,
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
    void        percent(float p);
    void        n(int);
    void        x(int);
    void        y(int);

    //** Getter **//
    e_etat      etat(void)const;
    Component * component(void)const;
    float       percent(void)const;
    int         n(void)const;
    int         x(void)const;
    int         y(void)const;
private:
    Component * _c;
    float       _p;
    e_etat      _etat;
    int         _n;
    int         _x;
    int         _y;


};

#endif // MYCOMPONENT_HPP
