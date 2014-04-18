#ifndef MAPINFO_H
#define MAPINFO_H

class MapInfo
{
public:
    MapInfo();
    MapInfo(int i, int j, MapInfo *** _map);
    /** Setter **/
    void z(int z);
    void n(int n);

    /** Getter **/
    int z(void)const;
    int n(void)const;

private:
    int _z;
    int _n;
};

#endif // MAPINFO_H
