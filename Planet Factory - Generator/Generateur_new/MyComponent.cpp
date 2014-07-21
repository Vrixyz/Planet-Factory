#include "MyComponent.hpp"

MyComponent::MyComponent()
    : _c(0)
{
}

MyComponent::MyComponent(Component *c, int p, e_etat e)
    : _c(c), _p(p), _etat(e)
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
