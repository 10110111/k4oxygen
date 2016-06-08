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

#include "oxygenshadow_config.h"

namespace Oxygen
{

void ActiveShadowConfiguration::readConfig()
{
    static const char* group="ActiveShadow";
    OxygenConfig* const config=OxygenConfig::self();
    enabled_=config->getOption(group,"Enabled").toVariant<bool>(true);
    shadowSize_=config->getOption(group,"ShadowSize").toVariant<int>(40);
    verticalOffset_=config->getOption(group,"VerticalOffset").toVariant<double>(0);
    innerColor_=config->getOption(group,"InnerColor").toVariant<QColor>(QColor(112,239,255));
    outerColor_=config->getOption(group,"OuterColor").toVariant<QColor>(QColor(84,167,240));
    useOuterColor_=config->getOption(group,"UseOuterColor").toVariant<bool>(true);
}

void InactiveShadowConfiguration::readConfig()
{
    static const char* group="InactiveShadow";
    OxygenConfig* const config=OxygenConfig::self();
    enabled_=config->getOption(group,"Enabled").toVariant<bool>(true);
    shadowSize_=config->getOption(group,"ShadowSize").toVariant<int>(40);
    verticalOffset_=config->getOption(group,"VerticalOffset").toVariant<double>(0.2);
    innerColor_=config->getOption(group,"InnerColor").toVariant<QColor>(QColor(0,0,0));
    outerColor_=config->getOption(group,"OuterColor").toVariant<QColor>(QColor(0,0,0));
    useOuterColor_=config->getOption(group,"UseOuterColor").toVariant<bool>(false);
}

}
