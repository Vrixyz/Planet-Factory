#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>

class HeightMap
{
public:
    HeightMap(int radius);
    //Create heightmap picture
    int exportHeighMap(const std::string & name, const std::string & path);
    //Update map
    int changeAlt(int x, int y, int z);

    /**Getter **/
    int ** map(void)const;
private:
    int ** _map;

};

#endif // HEIGHTMAP_H
