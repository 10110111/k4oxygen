#ifndef OXYGEN_STYLE_CONFIG_DATA_H_20160605
#define OXYGEN_STYLE_CONFIG_DATA_H_20160605

#include "oxygenconfig.h"
#include "oxygentypehelper.h"
#include <QtCore/QStringList>
#include <QObject>

namespace Oxygen
{
class StyleConfigData : public QObject
{
    Q_OBJECT
    Q_ENUMS(MnemonicsMode)
    Q_ENUMS(ViewTriangularExpanderSize)
    Q_ENUMS(CheckBoxStyle)
    Q_ENUMS(MenuHighlightMode)
    Q_ENUMS(TabStyle)
    Q_ENUMS(WindowDragMode)
    Q_ENUMS(ToolBarAnimationType)
    Q_ENUMS(MenuBarAnimationType)
    Q_ENUMS(MenuAnimationType)
public:
    enum MnemonicsMode
    {
        MN_NEVER,
        MN_AUTO,
        MN_ALWAYS,
    };
    enum ViewTriangularExpanderSize
    {
        TE_TINY,
        TE_SMALL,
        TE_NORMAL,
    };
    enum CheckBoxStyle
    {
        CS_CHECK,
        CS_X,
    };
    enum MenuHighlightMode
    {
        MM_DARK,
        MM_SUBTLE,
        MM_STRONG,
    };
    enum TabStyle
    {
        TS_SINGLE,
        TS_PLAIN,
    };
    enum WindowDragMode
    {
        WD_MINIMAL,
        WD_FULL,
    };
    enum ToolBarAnimationType
    {
        TB_NONE,
        TB_FADE,
        TB_FOLLOW_MOUSE,
    };
    enum MenuBarAnimationType
    {
        MB_NONE,
        MB_FADE,
        MB_FOLLOW_MOUSE,
    };
    enum MenuAnimationType
    {
        ME_NONE,
        ME_FADE,
        ME_FOLLOW_MOUSE,
    };
private:
    int backgroundOpacity_;
    QStringList opacityInternalBlackList_;
    QStringList opacityGreyList_;
    QStringList opacityBlackList_;
    bool useBackgroundGradient_;
    QString backgroundPixmap_;
    bool cacheEnabled_;
    int maxCacheSize_;
    int animationSteps_;
    MnemonicsMode mnemonicsMode_;
    bool toolTipTransparent_;
    bool toolTipDrawStyledFrames_;
    bool toolBarDrawItemSeparator_;
    bool viewDrawTriangularExpander_;
    ViewTriangularExpanderSize viewTriangularExpanderSize_;
    bool viewDrawFocusIndicator_;
    bool viewDrawTreeBranchLines_;
    bool viewInvertSortIndicator_;
    int scrollBarWidth_;
    int scrollBarAddLineButtons_;
    int scrollBarSubLineButtons_;
    CheckBoxStyle checkBoxStyle_;
    bool progressBarAnimated_;
    MenuHighlightMode menuHighlightMode_;
    bool tabSubtleShadow_;
    TabStyle tabStyle_;
    bool windowDragEnabled_;
    WindowDragMode windowDragMode_;
    bool splitterProxyEnabled_;
    int splitterProxyWidth_;
    bool widgetExplorerEnabled_;
    bool drawWidgetRects_;
    QStringList windowDragWhiteList_;
    QStringList windowDragBlackList_;
    bool useWMMoveResize_;
    bool animationsEnabled_;
    bool genericAnimationsEnabled_;
    ToolBarAnimationType toolBarAnimationType_;
    MenuBarAnimationType menuBarAnimationType_;
    MenuAnimationType menuAnimationType_;
    bool progressBarAnimationsEnabled_;
    int genericAnimationsDuration_;
    int toolBarAnimationsDuration_;
    int menuBarAnimationsDuration_;
    int menuBarFollowMouseAnimationsDuration_;
    int menuAnimationsDuration_;
    int menuFollowMouseAnimationsDuration_;
    int progressBarAnimationsDuration_;
    int progressBarBusyStepDuration_;
    bool stackedWidgetTransitionsEnabled_;
    bool labelTransitionsEnabled_;
    bool comboBoxTransitionsEnabled_;
    bool lineEditTransitionsEnabled_;
    int stackedWidgetTransitionsDuration_;
    int labelTransitionsDuration_;
    int comboBoxTransitionsDuration_;
    int lineEditTransitionsDuration_;
public:
    static StyleConfigData* self()
    {
        static StyleConfigData* self=new StyleConfigData();
        return self;
    }
    StyleConfigData() { readConfig(); }
    void readConfig();

    // getters
    static int backgroundOpacity() { return self()->backgroundOpacity_; }
    static QStringList opacityInternalBlackList() { return self()->opacityInternalBlackList_; }
    static QStringList opacityGreyList() { return self()->opacityGreyList_; }
    static QStringList opacityBlackList() { return self()->opacityBlackList_; }
    static bool useBackgroundGradient() { return self()->useBackgroundGradient_; }
    static QString backgroundPixmap() { return self()->backgroundPixmap_; }
    static bool cacheEnabled() { return self()->cacheEnabled_; }
    static int maxCacheSize() { return self()->maxCacheSize_; }
    static int animationSteps() { return self()->animationSteps_; }
    static MnemonicsMode mnemonicsMode() { return self()->mnemonicsMode_; }
    static bool toolTipTransparent() { return self()->toolTipTransparent_; }
    static bool toolTipDrawStyledFrames() { return self()->toolTipDrawStyledFrames_; }
    static bool toolBarDrawItemSeparator() { return self()->toolBarDrawItemSeparator_; }
    static bool viewDrawTriangularExpander() { return self()->viewDrawTriangularExpander_; }
    static ViewTriangularExpanderSize viewTriangularExpanderSize() { return self()->viewTriangularExpanderSize_; }
    static bool viewDrawFocusIndicator() { return self()->viewDrawFocusIndicator_; }
    static bool viewDrawTreeBranchLines() { return self()->viewDrawTreeBranchLines_; }
    static bool viewInvertSortIndicator() { return self()->viewInvertSortIndicator_; }
    static int scrollBarWidth() { return self()->scrollBarWidth_; }
    static int scrollBarAddLineButtons() { return self()->scrollBarAddLineButtons_; }
    static int scrollBarSubLineButtons() { return self()->scrollBarSubLineButtons_; }
    static CheckBoxStyle checkBoxStyle() { return self()->checkBoxStyle_; }
    static bool progressBarAnimated() { return self()->progressBarAnimated_; }
    static MenuHighlightMode menuHighlightMode() { return self()->menuHighlightMode_; }
    static bool tabSubtleShadow() { return self()->tabSubtleShadow_; }
    static TabStyle tabStyle() { return self()->tabStyle_; }
    static bool windowDragEnabled() { return self()->windowDragEnabled_; }
    static WindowDragMode windowDragMode() { return self()->windowDragMode_; }
    static bool splitterProxyEnabled() { return self()->splitterProxyEnabled_; }
    static int splitterProxyWidth() { return self()->splitterProxyWidth_; }
    static bool widgetExplorerEnabled() { return self()->widgetExplorerEnabled_; }
    static bool drawWidgetRects() { return self()->drawWidgetRects_; }
    static QStringList windowDragWhiteList() { return self()->windowDragWhiteList_; }
    static QStringList windowDragBlackList() { return self()->windowDragBlackList_; }
    static bool useWMMoveResize() { return self()->useWMMoveResize_; }
    static bool animationsEnabled() { return self()->animationsEnabled_; }
    static bool genericAnimationsEnabled() { return self()->genericAnimationsEnabled_; }
    static ToolBarAnimationType toolBarAnimationType() { return self()->toolBarAnimationType_; }
    static MenuBarAnimationType menuBarAnimationType() { return self()->menuBarAnimationType_; }
    static MenuAnimationType menuAnimationType() { return self()->menuAnimationType_; }
    static bool progressBarAnimationsEnabled() { return self()->progressBarAnimationsEnabled_; }
    static int genericAnimationsDuration() { return self()->genericAnimationsDuration_; }
    static int toolBarAnimationsDuration() { return self()->toolBarAnimationsDuration_; }
    static int menuBarAnimationsDuration() { return self()->menuBarAnimationsDuration_; }
    static int menuBarFollowMouseAnimationsDuration() { return self()->menuBarFollowMouseAnimationsDuration_; }
    static int menuAnimationsDuration() { return self()->menuAnimationsDuration_; }
    static int menuFollowMouseAnimationsDuration() { return self()->menuFollowMouseAnimationsDuration_; }
    static int progressBarAnimationsDuration() { return self()->progressBarAnimationsDuration_; }
    static int progressBarBusyStepDuration() { return self()->progressBarBusyStepDuration_; }
    static bool stackedWidgetTransitionsEnabled() { return self()->stackedWidgetTransitionsEnabled_; }
    static bool labelTransitionsEnabled() { return self()->labelTransitionsEnabled_; }
    static bool comboBoxTransitionsEnabled() { return self()->comboBoxTransitionsEnabled_; }
    static bool lineEditTransitionsEnabled() { return self()->lineEditTransitionsEnabled_; }
    static int stackedWidgetTransitionsDuration() { return self()->stackedWidgetTransitionsDuration_; }
    static int labelTransitionsDuration() { return self()->labelTransitionsDuration_; }
    static int comboBoxTransitionsDuration() { return self()->comboBoxTransitionsDuration_; }
    static int lineEditTransitionsDuration() { return self()->lineEditTransitionsDuration_; }
};

DECLARE_ENUM(StyleConfigData,MnemonicsMode);
DECLARE_ENUM(StyleConfigData,ViewTriangularExpanderSize);
DECLARE_ENUM(StyleConfigData,CheckBoxStyle);
DECLARE_ENUM(StyleConfigData,MenuHighlightMode);
DECLARE_ENUM(StyleConfigData,TabStyle);
DECLARE_ENUM(StyleConfigData,WindowDragMode);
DECLARE_ENUM(StyleConfigData,ToolBarAnimationType);
DECLARE_ENUM(StyleConfigData,MenuBarAnimationType);
DECLARE_ENUM(StyleConfigData,MenuAnimationType);
}

Q_DECLARE_METATYPE(Oxygen::StyleConfigData::MnemonicsMode)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::ViewTriangularExpanderSize)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::CheckBoxStyle)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::MenuHighlightMode)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::TabStyle)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::WindowDragMode)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::ToolBarAnimationType)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::MenuBarAnimationType)
Q_DECLARE_METATYPE(Oxygen::StyleConfigData::MenuAnimationType)

#endif
