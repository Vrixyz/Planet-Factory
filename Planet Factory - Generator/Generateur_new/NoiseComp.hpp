#ifndef NOISECOMP_H
#define NOISECOMP_H

#include "Component.hpp"

class NoiseComp
{
public:
    NoiseComp(Component *c, double range_s, double range_e);
    bool contain(double val);
    Component* component();
private:
    Component*  _c;
    double      _range_s;
    double      _range_e;
};

#endif // NOISECOMP_H
