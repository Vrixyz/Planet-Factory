#include "MyComponent.h"

MyComponent::MyComponent()
    : _c(0)
{
}

void    MyComponent::c(Component *c)
{
    _c = c;
}

void    MyComponent::etat(e_etat e)
{
    _etat = e;
}

e_etat  MyComponent::etat(void)const
{
    return _etat;
}


Component * MyComponent::component(void)const
{
    return _c;
}
