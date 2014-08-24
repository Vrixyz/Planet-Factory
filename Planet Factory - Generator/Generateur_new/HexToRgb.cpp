#include "HexToRgb.hpp"

HexToRgb::HexToRgb(QString color)
{
    _hexa = color.right(6);
    QString r = _hexa.left(2);
    QString g = _hexa.right(4).left(2);
    QString b = _hexa.right(2);

    bool ok;
    _r = r.toInt(&ok, 16);
    _g = g.toInt(&ok, 16);
    _b = b.toInt(&ok, 16);
}
