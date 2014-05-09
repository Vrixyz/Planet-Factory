#include "MyComponent.h"

MyComponent::MyComponent()
    : _c(0)
{
}

void    MyComponent::c(Component *c)
{
    _c = c;
}
