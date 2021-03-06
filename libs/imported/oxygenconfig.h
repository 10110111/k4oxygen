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

#ifndef OXYGEN_CONFIG_H_20160604
#define OXYGEN_CONFIG_H_20160604

#include <QtCore/QtGlobal>
#include <QtCore/QObject>
#include <QtCore/QString>
#include "oxygenoptionmap.h"

// From kglobalsettings.h
#define KDE_DEFAULT_SINGLECLICK true
#define KDE_DEFAULT_SMOOTHSCROLL true
#define KDE_DEFAULT_INSERTTEAROFFHANDLES 0
#define KDE_DEFAULT_AUTOSELECTDELAY -1
#define KDE_DEFAULT_CHANGECURSOR true
#define KDE_DEFAULT_LARGE_CURSOR false
#define KDE_DEFAULT_WHEEL_ZOOM false
#ifdef Q_WS_MAEMO_5
#define KDE_DEFAULT_ICON_ON_PUSHBUTTON false
#else
#define KDE_DEFAULT_ICON_ON_PUSHBUTTON true
#endif
#define KDE_DEFAULT_OPAQUE_RESIZE true
#define KDE_DEFAULT_BUTTON_LAYOUT 0
#define KDE_DEFAULT_SHADE_SORT_COLUMN true
#define KDE_DEFAULT_ALLOW_DEFAULT_BACKGROUND_IMAGES true
#define KDE_DEFAULT_NATURAL_SORTING true


namespace Oxygen
{

class ConfigBase;
class KSharedConfig;
typedef KSharedConfig* KSharedConfigPtr;
typedef KSharedConfig const* KSharedConfigConstPtr;

class KConfigGroup
{
    ConfigBase const* config;
    std::string group;
public:
    KConfigGroup(ConfigBase const* config, const char* group) : config(config), group(group){}
    KConfigGroup(ConfigBase const* config, std::string const& group) : config(config), group(group){}
    KConfigGroup(ConfigBase const* config, QString const& group) : config(config),
                                                                         group(qPrintable(group)){}
    template<typename T>
    T readEntry(std::string const& key, T const& defaultValue) const;
};

class KDE_EXPORT ConfigBase : public OptionMap
{
protected:
    QString fileName;
    ConfigBase(const char* fileName);
public:
    virtual void reparseConfiguration();
    KConfigGroup group(std::string const& groupName) const
    { return KConfigGroup(this, groupName); }
};

class KDE_EXPORT KSharedConfig : public ConfigBase
{
public:
    KSharedConfig();
    virtual void reparseConfiguration();
};

template<typename T>
T KConfigGroup::readEntry(std::string const& key, T const& defaultValue) const
{
    return config->getOption(group,key).template toVariant<T>(defaultValue);
}

namespace KGlobal
{
KDE_EXPORT KSharedConfigPtr config();
}

// Most methods in KGlobalSettings are just copy-pasted from kglobalsettings.cpp with their comments
class KDE_EXPORT KGlobalSettings : public QObject
{
    Q_OBJECT
public:
    /**
     * Returns a threshold in pixels for drag & drop operations.
     * As long as the mouse movement has not exceeded this number
     * of pixels in either X or Y direction no drag operation may
     * be started. This prevents spurious drags when the user intended
     * to click on something but moved the mouse a bit while doing so.
     *
     * For this to work you must save the position of the mouse (oldPos)
     * in the QWidget::mousePressEvent().
     * When the position of the mouse (newPos)
     * in a QWidget::mouseMoveEvent() exceeds this threshold
     * you may start a drag
     * which should originate from oldPos.
     *
     * Example code:
     * \code
     * void KColorCells::mousePressEvent( QMouseEvent *e )
     * {
     *    mOldPos = e->pos();
     * }
     *
     * void KColorCells::mouseMoveEvent( QMouseEvent *e )
     * {
     *    if( !(e->state() && LeftButton)) return;
     *
     *    int delay = KGlobalSettings::dndEventDelay();
     *    QPoint newPos = e->pos();
     *    if(newPos.x() > mOldPos.x()+delay || newPos.x() < mOldPos.x()-delay ||
     *       newPos.y() > mOldPos.y()+delay || newPos.y() < mOldPos.y()-delay)
     *    {
     *       // Drag color object
     *       int cell = posToCell(mOldPos); // Find color at mOldPos
     *       if ((cell != -1) && colors[cell].isValid())
     *       {
     *          KColorDrag *d = KColorDrag::makeDrag( colors[cell], this);
     *          d->dragCopy();
     *       }
     *    }
     * }
     * \endcode
     * @return the threshold for drag & drop in pixels
     */

    static int dndEventDelay();

    /**
     * This function determines if the user wishes to see icons on the
     * push buttons.
     *
     * @return Returns true if user wants to show icons.
     */

    static bool showIconsOnPushButtons();
    /**
     * Returns the contrast for borders as a floating point value.
     * @param config pointer to the config from which to read the contrast
     * setting (the default is to use KGlobal::config())
     * @return the contrast (between 0.0 for minimum and 1.0 for maximum
     *         contrast)
     */
    static qreal contrastF(const KSharedConfigPtr &config=KGlobal::config());

    static QPalette createApplicationPalette();

    static KGlobalSettings* self();
    KGlobalSettings();
    /**
     * Specifies options passed to activate().
     *
     * @since 4.6
     */
    enum ActivateOption {
        ApplySettings = 0x1, ///< Make all globally applicable settings take effect.
        ListenForChanges = 0x2 ///< Listen for changes to the settings.
    };
    Q_DECLARE_FLAGS(ActivateOptions, ActivateOption)
    void activate(ActivateOptions options);

    /**
     * An identifier for change signals.
     * \see emitChange
     */
    enum ChangeType { PaletteChanged = 0, FontChanged, StyleChanged,
                      SettingsChanged, IconChanged, CursorChanged,
                      ToolbarStyleChanged, ClipboardConfigChanged,
                      BlockShortcuts, NaturalSortingChanged };
Q_SIGNALS:
    void kdisplayPaletteChanged() const;
private Q_SLOTS:
    void _k_slotNotifyChange(int,int);
private:
    void kdisplaySetPalette();
    void kdisplaySetFont();

    bool activated;
};

class KDE_EXPORT KIconLoader
{
public:
    /**
     * These are the standard sizes for icons.
     */
    enum StdSizes {
        /// small icons for menu entries
        SizeSmall=16,
        /// slightly larger small icons for toolbars, panels, etc
        SizeSmallMedium=22,
        /// medium sized icons for the desktop
        SizeMedium=32,
        /// large sized icons for the panel
        SizeLarge=48,
        /// huge sized icons for iconviews
        SizeHuge=64,
        /// enormous sized icons for iconviews
        SizeEnormous=128
    };
    /**
     * The group of the icon.
     */
    enum Group {
        /// No group
        NoGroup=-1,
        /// Desktop icons
        Desktop=0,
        /// First group
        FirstGroup=0,
        /// Toolbar icons
        Toolbar,
        /// Main toolbar icons
        MainToolbar,
        /// Small icons, e.g. for buttons
        Small,
        /// Panel (Plasma Taskbar) icons
        Panel,
        /// Icons for use in dialog titles, page lists, etc
        Dialog,
        /// Last group
        LastGroup,
        /// User icons
        User
    };
    static KIconLoader* global();
    KIconLoader();
    int currentSize(Group group) const;
private:
    int sizes[LastGroup];
};

class KDE_EXPORT OxygenConfig : public ConfigBase
{
public:
    OxygenConfig();
    static OxygenConfig* self();
};

}

#endif
