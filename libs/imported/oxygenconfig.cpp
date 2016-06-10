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

#include "oxygenconfig.h"
#include <QApplication>
#include <QtDBus/QtDBus>
#include <QProcess>
#include <QDir>
#include <QProcessEnvironment>
#include "kcolorscheme.h"
#if QT_VERSION >= 0x50000
#include <QGuiApplication>
#endif

namespace Oxygen
{

QString userConfigDir()
{
    // There's no better way in Qt4. Although Qt5 has QStandardPaths, we'll do in one way for both Qt4 and Qt5.
    return QProcessEnvironment::systemEnvironment().value("XDG_CONFIG_HOME",QDir::homePath()+"/.config");
}

QStringList getConfigPaths()
{
    QProcess process;
    QStringList args; args << "--path" << "config";
    process.start("kde4-config",args);
    if(process.waitForFinished() && process.exitCode()==0)
        return QString::fromUtf8(process.readAllStandardOutput()).trimmed().split(':');

    // Resort to user config dir
    QString dirName=userConfigDir()+"/k4oxygen";
    if(QDir(dirName).exists()) return QStringList(dirName);
    return QStringList();
}

namespace KGlobal
{
KSharedConfigPtr kdeglobals;
KSharedConfigPtr config()
{
    return kdeglobals ? kdeglobals : kdeglobals=new KSharedConfig();
}
}


qreal KGlobalSettings::contrastF(const KSharedConfigPtr& config)
{
    KConfigGroup g( config, "KDE" );
    return 0.1 * g.readEntry( "contrast", 7 );
}

bool KGlobalSettings::showIconsOnPushButtons()
{
    KConfigGroup g( KGlobal::config(), "KDE" );
    return g.readEntry("ShowIconsOnPushButtons",
                       KDE_DEFAULT_ICON_ON_PUSHBUTTON);
}

int KGlobalSettings::dndEventDelay()
{
    KConfigGroup g( KGlobal::config(), "General" );
    return g.readEntry("StartDragDist", QApplication::startDragDistance());
}

KGlobalSettings::KGlobalSettings()
    : activated(false)
{
}

KGlobalSettings* KGlobalSettings::self()
{
    static KGlobalSettings* self=new KGlobalSettings;
    return self;
}

// Taken from kglobalsettings.cpp in kdelibs
void KGlobalSettings::activate(ActivateOptions options)
{
    if (!activated) {
        activated = true;

        if (options & ListenForChanges) {
            QDBusConnection::sessionBus().connect( QString(), "/KGlobalSettings", "org.kde.KGlobalSettings",
                                                   "notifyChange", this, SLOT(_k_slotNotifyChange(int,int)) );
        }

        if (options & ApplySettings) {
            kdisplaySetPalette(); // XXX(10110111): originally: "d->kdisplaySetStyle(); // implies palette setup"
            kdisplaySetFont();
//            d->propagateQtSettings();
        }
    }
}

// Taken from KDE's KGlobalSettings::Private::createNewApplicationPalette() with caching removed
QPalette KGlobalSettings::createApplicationPalette()
{
    KSharedConfigPtr config=KGlobal::config();

    QPalette palette;

    QPalette::ColorGroup states[3] = { QPalette::Active, QPalette::Inactive,
                                       QPalette::Disabled };

    // TT thinks tooltips shouldn't use active, so we use our active colors for all states
    KColorScheme schemeTooltip(QPalette::Active, KColorScheme::Tooltip, config);

    for ( int i = 0; i < 3 ; i++ ) {
        QPalette::ColorGroup state = states[i];
        KColorScheme schemeView(state, KColorScheme::View, config);
        KColorScheme schemeWindow(state, KColorScheme::Window, config);
        KColorScheme schemeButton(state, KColorScheme::Button, config);
        KColorScheme schemeSelection(state, KColorScheme::Selection, config);

        palette.setBrush( state, QPalette::WindowText, schemeWindow.foreground() );
        palette.setBrush( state, QPalette::Window, schemeWindow.background() );
        palette.setBrush( state, QPalette::Base, schemeView.background() );
        palette.setBrush( state, QPalette::Text, schemeView.foreground() );
        palette.setBrush( state, QPalette::Button, schemeButton.background() );
        palette.setBrush( state, QPalette::ButtonText, schemeButton.foreground() );
        palette.setBrush( state, QPalette::Highlight, schemeSelection.background() );
        palette.setBrush( state, QPalette::HighlightedText, schemeSelection.foreground() );
        palette.setBrush( state, QPalette::ToolTipBase, schemeTooltip.background() );
        palette.setBrush( state, QPalette::ToolTipText, schemeTooltip.foreground() );

        palette.setColor( state, QPalette::Light, schemeWindow.shade( KColorScheme::LightShade ) );
        palette.setColor( state, QPalette::Midlight, schemeWindow.shade( KColorScheme::MidlightShade ) );
        palette.setColor( state, QPalette::Mid, schemeWindow.shade( KColorScheme::MidShade ) );
        palette.setColor( state, QPalette::Dark, schemeWindow.shade( KColorScheme::DarkShade ) );
        palette.setColor( state, QPalette::Shadow, schemeWindow.shade( KColorScheme::ShadowShade ) );

        palette.setBrush( state, QPalette::AlternateBase, schemeView.background( KColorScheme::AlternateBackground) );
        palette.setBrush( state, QPalette::Link, schemeView.foreground( KColorScheme::LinkText ) );
        palette.setBrush( state, QPalette::LinkVisited, schemeView.foreground( KColorScheme::VisitedText ) );
    }

    return palette;

}

void KGlobalSettings::kdisplaySetPalette()
{
#if QT_VERSION >= 0x50000
    if(qobject_cast<QGuiApplication*>(qApp)) {
#else
    if (qApp->type() == QApplication::GuiClient) {
#endif
        QApplication::setPalette( createApplicationPalette() );
    }
    emit kdisplayPaletteChanged();
}


void KGlobalSettings::kdisplaySetFont()
{
/* // TODO(10110111): make it work
    if (qApp->type() == QApplication::GuiClient) {
        KGlobalSettingsData* data = KGlobalSettingsData::self();

        QApplication::setFont( data->font(KGlobalSettingsData::GeneralFont) );
        const QFont menuFont = data->font( KGlobalSettingsData::MenuFont );
        QApplication::setFont( menuFont, "QMenuBar" );
        QApplication::setFont( menuFont, "QMenu" );
        QApplication::setFont( menuFont, "KPopupTitle" );
        QApplication::setFont( data->font(KGlobalSettingsData::ToolbarFont), "QToolBar" );
    }*/
}


void KGlobalSettings::_k_slotNotifyChange(int changeType, int arg)
{
    switch(changeType) {
/*    case StyleChanged:
        if (activated) {
            KGlobal::config()->reparseConfiguration();
            kdisplaySetStyle();
        }
        break;
*/
/*    case ToolbarStyleChanged:
        KGlobal::config()->reparseConfiguration();
        emit q->toolbarAppearanceChanged(arg);
        break;
*/
    case PaletteChanged:
        if (activated) {
            KGlobal::config()->reparseConfiguration();
//            paletteCreated = false;
            kdisplaySetPalette();
        }
        break;
/* // TODO(10110111): make this work
    case FontChanged:
        KGlobal::config()->reparseConfiguration();
        KGlobalSettingsData::self()->dropFontSettingsCache();
        if (activated) {
            kdisplaySetFont();
        }
        break;
*/
    case SettingsChanged: {
        KGlobal::config()->reparseConfiguration();
/*        SettingsCategory category = static_cast<SettingsCategory>(arg);
        if (category == SETTINGS_QT) {
            if (activated) {
                propagateQtSettings();
            }
        } else {
            switch (category) {
                case SETTINGS_STYLE:
                    reloadStyleSettings();
                    break;
                case SETTINGS_MOUSE:
                    KGlobalSettingsData::self()->dropMouseSettingsCache();
                    break;
                case SETTINGS_LOCALE:
                    KGlobal::locale()->reparseConfiguration();
                    break;
                default:
                    break;
            }
            emit q->settingsChanged(category);
        }*/
        break;
    }
/* // FIXME(10110111): do we want to implement this?
    case IconChanged:
        QPixmapCache::clear();
        KGlobal::config()->reparseConfiguration();
        emit q->iconChanged(arg);
        break;
*/

/*    case CursorChanged:
        applyCursorTheme();
        break;

    case BlockShortcuts:
        // FIXME KAccel port
        //KGlobalAccel::blockShortcuts(arg);
        emit q->blockShortcuts(arg); // see kwin
        break;

    case NaturalSortingChanged:
        emit q->naturalSortingChanged();
        break;

    default:
        kWarning(240) << "Unknown type of change in KGlobalSettings::slotNotifyChange: " << changeType;*/
    }
}


ConfigBase::ConfigBase(const char* fileName)
    : fileName(fileName)
{
    reparseConfiguration();
}

void ConfigBase::reparseConfiguration()
{
    clear();
    static const QStringList paths=getConfigPaths();
    for(int i=paths.size()-1;i>=0;--i)
    {
        const QString filePath = paths[i]+"/"+fileName;
        merge(OptionMap(filePath.toUtf8().constData()));
        // FIXME: do we want to monitor the file for changes (see oxygen-gtk's
        //      monitorFile()), or is it sufficient to rely on DBus events?
    }
}

// -------------------- KSharedConfig impl --------------------------

KSharedConfig::KSharedConfig()
    : ConfigBase("kdeglobals")
{
    KGlobalSettings::self()->activate(KGlobalSettings::ApplySettings);
}

// -------------------- OxygenConfig impl ---------------------------

OxygenConfig* OxygenConfig::self()
{
    static OxygenConfig* self=new OxygenConfig();
    return self;
}

OxygenConfig::OxygenConfig()
    : ConfigBase("oxygenrc")
{}

// -------------------- KIconLoader impl ----------------------------

KIconLoader* KIconLoader::global()
{
    static KIconLoader* loader=new KIconLoader();
    return loader;
}

KIconLoader::KIconLoader()
{
    // Code similar to KIconLoaderPrivate::init() in kiconloader.cpp in kdelibs
    static const char* const groups[LastGroup]={
                                                "Desktop",
                                                "Toolbar",
                                                "MainToolbar",
                                                "Small",
                                                "Panel",
                                                "Dialog"
                                               };
    // defaults from from KIconTheme::KIconTheme() in kicontheme.cpp in kdelibs
    static const int defaultSizes[LastGroup]={32,22,22,16,32,32};
    for(int i=FirstGroup;i<LastGroup;++i)
    {
        KConfigGroup g( KGlobal::config(), groups[i]+std::string("Icons") );
        sizes[i]=g.readEntry("Size",defaultSizes[i]);
    }
}

int KIconLoader::currentSize(Group group) const
{
    if(group<0 || group>=LastGroup) return -1;
    return sizes[group];
}

}
