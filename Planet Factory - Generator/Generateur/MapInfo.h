#ifndef MAPINFO_H
#define MAPINFO_H

#include "Component.hpp"

class MapInfo
{
public:
    MapInfo();
    MapInfo(int i, int j, MapInfo *** _map);
    /** Setter **/
    void z(int z);
    void n(int n);
    void component(Component * c);

    /** Getter **/
    int z(void)const;
    int n(void)const;
    Component * component(void) const;

private:
    int _z;
    int _n;
    Component * _component;
};

#endif // MAPINFO_H
