#ifndef MAPINFO_H
#define MAPINFO_H

#include "Component.hpp"

enum e_etat
{
    LIQUID,
    SOLID,
    GAZ
};

class MapInfo
{
public:
    MapInfo();
    MapInfo(int i, int j, MapInfo *** _map);
    /** Setter **/
    void z(int z);
    void n(int n);
    void component(Component * c);
    void        etat(e_etat);

    /** Getter **/
    int z(void)const;
    int n(void)const;
    Component * component(void) const;
    e_etat      etat(void)const;

private:
    int _z;
    int _n;
    Component * _component;
    e_etat      _etat;
};

#endif // MAPINFO_H
