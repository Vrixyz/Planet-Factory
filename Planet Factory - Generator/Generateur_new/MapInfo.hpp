#ifndef MAPINFO_HPP
#define MAPINFO_HPP

#include <cstdlib>
#include <list>
#include <QtDebug>

#include "Component.hpp"
#include "MyComponent.hpp"

/*enum e_etat
{
    LIQUID,
    SOLID,
    GAZ
};*/

class MapInfo
{
public:
    MapInfo();
    MapInfo(int i, int j, MapInfo *** _map);

    int         editComponent(Component *c, float percent, e_etat etat);
    float       freeSpace(void);
    void        loadN();

    /** Setter **/
    void        z(int z);
    void        n(int n);
    void        component(Component * c);
    void        components(std::map<Component*, int> * mapCompo);
    void        etat(e_etat);

    /** Getter **/
    int         z(void)const;
    int         n(void)const;
    Component * component(void) const;
    e_etat      etat(void)const;
    std::list<MyComponent*> components(void);

private:
    int _z;
    int _n;
    Component * _component;
    e_etat      _etat;
    std::list<MyComponent*> _components;
};

#endif // MAPINFO_HPP
