#include "oxygenoption.h"

namespace Oxygen
{

template<> QColor Option::toVariant(QColor defaultValue) const
{
    QStringList rgb=QString(_value.c_str()).split(',');
    if(rgb.size()!=3) return defaultValue;
    bool okR,okG,okB;
    unsigned red  =rgb[0].toUInt(&okR),
             green=rgb[1].toUInt(&okG),
             blue =rgb[2].toUInt(&okB);
    if(okR && okG && okB && red<256 && green<256 && blue<256)
        return QColor(red,green,blue);
    return defaultValue;
}

}
