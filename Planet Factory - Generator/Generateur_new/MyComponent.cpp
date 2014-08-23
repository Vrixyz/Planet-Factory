#include "MyComponent.hpp"

MyComponent::MyComponent()
    : _c(0)
{
}

MyComponent::MyComponent(Component *c, int p, e_etat e)
    : _c(c), _p(p), _etat(e), _n(0)
{
}

//** Setter **//
void        MyComponent::percent(float p)
{
    _p = p;
}

void    MyComponent::component(Component *c)
{
    _c = c;
}

void    MyComponent::etat(e_etat e)
{
    _etat = e;
}

void    MyComponent::n(int n)
{
    _n = n;
}

void        MyComponent::x(int x)
{
    _x = x;
}

void        MyComponent::y(int y)
{
    _y = y;
}


//** Getter **//

e_etat  MyComponent::etat(void)const
{
    return _etat;
}


Component * MyComponent::component(void)const
{
    return _c;
}

float MyComponent::percent(void)const
{
    return _p;
}

int MyComponent::n(void) const
{
    return _n;
}

int MyComponent::x(void) const
{
    return _x;
}

int MyComponent::y(void) const
{
    return _y;
}
