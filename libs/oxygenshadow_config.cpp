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
