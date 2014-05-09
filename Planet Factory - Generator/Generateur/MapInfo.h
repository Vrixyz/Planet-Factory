#ifndef MAPINFO_H
#define MAPINFO_H

#include "MyComponent.h"

class MapInfo
{
public:
    MapInfo();
    MapInfo(int i, int j, MapInfo *** _map);
    /** Setter **/
    void z(int z);
    void n(int n);
    void component(MyComponent * c);

    /** Getter **/
    int z(void)const;
    int n(void)const;
    MyComponent * component(void) const;

private:
    int _z;
    int _n;
    MyComponent * _component;
};

#endif // MAPINFO_H
