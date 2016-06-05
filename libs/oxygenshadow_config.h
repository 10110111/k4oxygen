#ifndef OXYGEN_SHADOW_CONFIG_H_20160605
#define OXYGEN_SHADOW_CONFIG_H_20160605

#include "oxygenconfig.h"
#include <QtGui/QColor>

namespace Oxygen
{
class ActiveShadowConfiguration
{
    bool enabled_;
    int shadowSize_;
    double verticalOffset_;
    QColor innerColor_;
    QColor outerColor_;
    bool useOuterColor_;
public:
    static ActiveShadowConfiguration* self()
    {
        static ActiveShadowConfiguration* self=new ActiveShadowConfiguration();
        return self;
    }
    ActiveShadowConfiguration() { readConfig(); }
    void readConfig();
/*
  <group name="ActiveShadow">

    <entry name="Enabled" type = "Bool">
       <default>true</default>
    </entry>

    <entry name="ShadowSize" type = "Int">
       <default>40</default>
    </entry>

    <entry name="VerticalOffset" type = "Double">
       <default>0</default>
    </entry>

    <entry name="InnerColor" type = "Color">
       <default>112,239,255</default>
    </entry>

    <entry name="OuterColor" type = "Color">
       <default>84,167,240</default>
    </entry>

    <entry name="UseOuterColor" type = "Bool">
       <default>true</default>
    </entry>

  </group>
*/
    static bool enabled() { return self()->enabled_; }
    static int shadowSize() { return self()->shadowSize_; }
    static double verticalOffset() { return self()->verticalOffset_; }
    static QColor innerColor() { return self()->innerColor_; }
    static QColor outerColor() { return self()->outerColor_; }
    static bool useOuterColor() { return self()->useOuterColor_; }

    static void setShadowSize(int) {} // TODO(10110111): implement, this is a stub
};
class InactiveShadowConfiguration
{
    bool enabled_;
    int shadowSize_;
    double verticalOffset_;
    QColor innerColor_;
    QColor outerColor_;
    bool useOuterColor_;
public:
    static InactiveShadowConfiguration* self()
    {
        static InactiveShadowConfiguration* self=new InactiveShadowConfiguration();
        return self;
    }
    InactiveShadowConfiguration() { readConfig(); }
    void readConfig();
/*
  <group name="InactiveShadow">

    <entry name="Enabled" type = "Bool">
       <default>true</default>
    </entry>

    <entry name="ShadowSize" type = "Int">
       <default>40</default>
    </entry>

    <entry name="VerticalOffset" type = "Double">
       <default>0.2</default>
    </entry>

    <entry name="InnerColor" type = "Color">
       <default>0, 0, 0</default>
    </entry>

    <entry name="OuterColor" type = "Color">
       <default>0, 0, 0</default>
    </entry>

    <entry name="UseOuterColor" type = "Bool">
       <default>false</default>
    </entry>

  </group>
*/
    static bool enabled() { return self()->enabled_; }
    static int shadowSize() { return self()->shadowSize_; }
    static double verticalOffset() { return self()->verticalOffset_; }
    static QColor innerColor() { return self()->innerColor_; }
    static QColor outerColor() { return self()->outerColor_; }
    static bool useOuterColor() { return self()->useOuterColor_; }

    static void setShadowSize(int) {} // TODO(10110111): implement, this is a stub
};
}

#endif
