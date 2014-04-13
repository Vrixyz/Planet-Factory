#ifndef MAPINFO_H
#define MAPINFO_H

class MapInfo
{
public:
    MapInfo();

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
