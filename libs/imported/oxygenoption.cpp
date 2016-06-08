/* This file is part of the K4Oxygen project
 * Copyright (C) 2016 Ruslan Kabatsayev <b7.10110111@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

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
