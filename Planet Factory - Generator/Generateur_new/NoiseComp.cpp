#include "NoiseComp.hpp"
#include <QtDebug>

NoiseComp::NoiseComp(Component *c, double range_s, double range_e)
{
    _c = c;
    _range_s = range_s;
    _range_e = range_e;


    qDebug() << "Composant: " << c->getName() << " from:" << range_s << " to: " << range_e;
}

bool NoiseComp::contain(double val)
{
    if (val > _range_s && val < _range_e)
        return true;
    return false;
}

Component* NoiseComp::component()
{
    return _c;
}
