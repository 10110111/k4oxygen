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

#include "oxygenstyleconfigdata.h"

namespace Oxygen
{
void StyleConfigData::readConfig()
{
    OxygenConfig* const config=OxygenConfig::self();
    config->reparseConfiguration();

    const char* group="Common";

    backgroundOpacity_ = config->getOption(group,"BackgroundOpacity").toVariant<int>(255);
    opacityInternalBlackList_ = config->getOption(group,"OpacityInternalBlackList").toVariant<QStringList>(QVariant("krunner,amarok,vlc,vlc-wrapper,kscreenlocker,kscreenlocker_greet,kdenlive,nspluginviewer,smplayer,dragon,kaffeine,loopy,kwin,bangarang,djview").toStringList());
    opacityGreyList_ = config->getOption(group,"OpacityGreyList").toVariant<QStringList>(QVariant("krunner,amarok,vlc,vlc-wrapper,kscreenlocker,kpartsplugin").toStringList());
    opacityBlackList_ = config->getOption(group,"OpacityBlackList").toVariant<QStringList>();
    useBackgroundGradient_ = config->getOption(group,"UseBackgroundGradient").toVariant<bool>(true);
    backgroundPixmap_ = config->getOption(group,"BackgroundPixmap").toVariant<QString>("");

    group="Style";

    cacheEnabled_ = config->getOption(group,"CacheEnabled").toVariant<bool>(true);
    maxCacheSize_ = config->getOption(group,"MaxCacheSize").toVariant<int>(512);
    animationSteps_ = config->getOption(group,"AnimationSteps").toVariant<int>(10);
    mnemonicsMode_ = config->getOption(group,"MnemonicsMode").toVariant<MnemonicsMode>(MN_ALWAYS);
    toolTipTransparent_ = config->getOption(group,"ToolTipTransparent").toVariant<bool>(true);
    toolTipDrawStyledFrames_ = config->getOption(group,"ToolTipDrawStyledFrames").toVariant<bool>(true);
    toolBarDrawItemSeparator_ = config->getOption(group,"ToolBarDrawItemSeparator").toVariant<bool>(true);
    viewDrawTriangularExpander_ = config->getOption(group,"ViewDrawTriangularExpander").toVariant<bool>(true);
    viewTriangularExpanderSize_ = config->getOption(group,"ViewTriangularExpanderSize").toVariant<ViewTriangularExpanderSize>(TE_SMALL);
    viewDrawFocusIndicator_ = config->getOption(group,"ViewDrawFocusIndicator").toVariant<bool>(true);
    viewDrawTreeBranchLines_ = config->getOption(group,"ViewDrawTreeBranchLines").toVariant<bool>(true);
    viewInvertSortIndicator_ = config->getOption(group,"ViewInvertSortIndicator").toVariant<bool>(false);
    scrollBarWidth_ = config->getOption(group,"ScrollBarWidth").toVariant<int>(15);
    scrollBarAddLineButtons_ = config->getOption(group,"ScrollBarAddLineButtons").toVariant<int>(2);
    scrollBarSubLineButtons_ = config->getOption(group,"ScrollBarSubLineButtons").toVariant<int>(1);
    checkBoxStyle_ = config->getOption(group,"CheckBoxStyle").toVariant<CheckBoxStyle>(CS_CHECK);
    progressBarAnimated_ = config->getOption(group,"ProgressBarAnimated").toVariant<bool>(true);
    menuHighlightMode_ = config->getOption(group,"MenuHighlightMode").toVariant<MenuHighlightMode>(MM_DARK);
    tabSubtleShadow_ = config->getOption(group,"TabSubtleShadow").toVariant<bool>(false);
    tabStyle_ = config->getOption(group,"TabStyle").toVariant<TabStyle>(TS_SINGLE);
    windowDragEnabled_ = config->getOption(group,"WindowDragEnabled").toVariant<bool>(true);
    windowDragMode_ = config->getOption(group,"WindowDragMode").toVariant<WindowDragMode>(WD_FULL);
    splitterProxyEnabled_ = config->getOption(group,"SplitterProxyEnabled").toVariant<bool>(true);
    splitterProxyWidth_ = config->getOption(group,"SplitterProxyWidth").toVariant<int>(12);
    widgetExplorerEnabled_ = config->getOption(group,"WidgetExplorerEnabled").toVariant<bool>(false);
    drawWidgetRects_ = config->getOption(group,"DrawWidgetRects").toVariant<bool>(false);
    windowDragWhiteList_ = config->getOption(group,"WindowDragWhiteList").toVariant<QStringList>();
    windowDragBlackList_ = config->getOption(group,"WindowDragBlackList").toVariant<QStringList>();
    useWMMoveResize_ = config->getOption(group,"UseWMMoveResize").toVariant<bool>(true);
    animationsEnabled_ = config->getOption(group,"AnimationsEnabled").toVariant<bool>(true);
    genericAnimationsEnabled_ = config->getOption(group,"GenericAnimationsEnabled").toVariant<bool>(true);
    toolBarAnimationType_ = config->getOption(group,"ToolBarAnimationType").toVariant<ToolBarAnimationType>(TB_FADE);
    menuBarAnimationType_ = config->getOption(group,"MenuBarAnimationType").toVariant<MenuBarAnimationType>(MB_FADE);
    menuAnimationType_ = config->getOption(group,"MenuAnimationType").toVariant<MenuAnimationType>(ME_FADE);
    progressBarAnimationsEnabled_ = config->getOption(group,"ProgressBarAnimationsEnabled").toVariant<bool>(true);
    genericAnimationsDuration_ = config->getOption(group,"GenericAnimationsDuration").toVariant<int>(150);
    toolBarAnimationsDuration_ = config->getOption(group,"ToolBarAnimationsDuration").toVariant<int>(50);
    menuBarAnimationsDuration_ = config->getOption(group,"MenuBarAnimationsDuration").toVariant<int>(150);
    menuBarFollowMouseAnimationsDuration_ = config->getOption(group,"MenuBarFollowMouseAnimationsDuration").toVariant<int>(80);
    menuAnimationsDuration_ = config->getOption(group,"MenuAnimationsDuration").toVariant<int>(150);
    menuFollowMouseAnimationsDuration_ = config->getOption(group,"MenuFollowMouseAnimationsDuration").toVariant<int>(40);
    progressBarAnimationsDuration_ = config->getOption(group,"ProgressBarAnimationsDuration").toVariant<int>(250);
    progressBarBusyStepDuration_ = config->getOption(group,"ProgressBarBusyStepDuration").toVariant<int>(50);
    stackedWidgetTransitionsEnabled_ = config->getOption(group,"StackedWidgetTransitionsEnabled").toVariant<bool>(false);
    labelTransitionsEnabled_ = config->getOption(group,"LabelTransitionsEnabled").toVariant<bool>(true);
    comboBoxTransitionsEnabled_ = config->getOption(group,"ComboBoxTransitionsEnabled").toVariant<bool>(true);
    lineEditTransitionsEnabled_ = config->getOption(group,"LineEditTransitionsEnabled").toVariant<bool>(true);
    stackedWidgetTransitionsDuration_ = config->getOption(group,"StackedWidgetTransitionsDuration").toVariant<int>(150);
    labelTransitionsDuration_ = config->getOption(group,"LabelTransitionsDuration").toVariant<int>(75);
    comboBoxTransitionsDuration_ = config->getOption(group,"ComboBoxTransitionsDuration").toVariant<int>(75);
    lineEditTransitionsDuration_ = config->getOption(group,"LineEditTransitionsDuration").toVariant<int>(150);
}
}
