#include "oxygenconfig.h"
#include <QApplication>
#include <QtDBus/QtDBus>

namespace Oxygen
{

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

void KGlobalSettings::activate(ActivateOptions options)
{
    if (!activated) {
        activated = true;

        if (options & ListenForChanges) {
            QDBusConnection::sessionBus().connect( QString(), "/KGlobalSettings", "org.kde.KGlobalSettings",
                                                   "notifyChange", this, SLOT(_k_slotNotifyChange(int,int)) );
        }

//        if (options & ApplySettings) {
//            d->kdisplaySetStyle(); // implies palette setup
//            d->kdisplaySetFont();
//            d->propagateQtSettings();
//        }
    }
}

void KGlobalSettings::kdisplaySetPalette()
{
#if !defined(Q_WS_MAEMO_5) && !defined(Q_OS_WINCE) && !defined(MEEGO_EDITION_HARMATTAN)
/*    if (!kdeFullSession) {
        return;
    }*/
/* // TODO(10110111): make it work
    if (qApp->type() == QApplication::GuiClient) {
        QApplication::setPalette( q->createApplicationPalette() );
    }*/
    emit kdisplayPaletteChanged();
//    emit q->appearanceChanged();
#endif
}


void KGlobalSettings::kdisplaySetFont()
{
#if !defined(Q_WS_MAEMO_5) && !defined(Q_OS_WINCE) && !defined(MEEGO_EDITION_HARMATTAN)
/*    if (!kdeFullSession) {
        return;
    }*/

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
//    emit q->kdisplayFontChanged();
//    emit q->appearanceChanged();
#endif
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



void KSharedConfig::reparseConfiguration()
{
    // TODO(10110111): parse kdeglobals
}

KSharedConfig::KSharedConfig()
{
    // TODO(10110111): load config
}

KIconLoader* KIconLoader::global()
{
    static KIconLoader* loader=new KIconLoader();
    return loader;
}

int KIconLoader::currentSize(Group group) const
{
    // TODO(10110111): this is a stub, implement it properly (see KIconLoaderPrivate::init()
    //       and KIconLoader::currentSize in kiconloader.cpp in kdelibs)
    return SizeMedium;
}

OxygenConfig* OxygenConfig::self()
{
    static OxygenConfig* self=new OxygenConfig();
    return self;
}

void OxygenConfig::reparseConfiguration()
{
    // TODO(10110111): parse oxygenrc
    // TODO(10110111): check that shadow configuration is also loaded
}

OxygenConfig::OxygenConfig()
{
    // TODO(10110111): load config
}

}
