#ifndef HEXTORGB_HPP
#define HEXTORGB_HPP

#include <QString>
class HexToRgb
{
public:
    HexToRgb(QString hexa);
    int r() {return _r;}
    int g() {return _g;}
    int b() {return _b;}
private:
    QString _hexa;
    int     _r;
    int     _g;
    int     _b;

};

#endif // HEXTORGB_HPP
