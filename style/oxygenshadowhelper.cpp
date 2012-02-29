//////////////////////////////////////////////////////////////////////////////
// oxygenshadowhelper.h
// handle shadow pixmaps passed to window manager via X property
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo@oxygen-icons.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "oxygenshadowhelper.h"
#include "oxygenshadowhelper.moc"
#include "oxygenshadowcache.h"
#include "oxygenstylehelper.h"

#include <KConfig>

#include <QtGui/QDockWidget>
#include <QtGui/QMenu>
#include <QtGui/QPainter>
#include <QtGui/QToolBar>
#include <QtCore/QTextStream>
#include <QtCore/QEvent>

#ifdef Q_WS_X11
#include <QtGui/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#endif

namespace Oxygen
{

    const char* const ShadowHelper::netWMShadowAtomName( "_KDE_NET_WM_SHADOW" );
    const char* const ShadowHelper::netWMForceShadowPropertyName( "_KDE_NET_WM_FORCE_SHADOW" );
    const char* const ShadowHelper::netWMSkipShadowPropertyName( "_KDE_NET_WM_SKIP_SHADOW" );

    //_____________________________________________________
    ShadowHelper::ShadowHelper( QObject* parent, StyleHelper& helper ):
        QObject( parent ),
        _helper( helper ),
        _shadowCache( new ShadowCache( helper ) ),
        _size( 0 )
        #ifdef Q_WS_X11
        ,_atom( None )
        #endif
    {}

    //_______________________________________________________
    ShadowHelper::~ShadowHelper( void )
    { delete _shadowCache; }

    //______________________________________________
    void ShadowHelper::reset( void )
    {
        _tiles = TileSet_x11();
        _dockTiles = TileSet_x11();

        // reset size
        _size = 0;
    }

    //_______________________________________________________
    bool ShadowHelper::registerWidget( QWidget* widget, bool force )
    {

        // make sure widget is not already registered
        if( _widgets.contains( widget ) ) return false;

        // check if widget qualifies
        if( !( force || acceptWidget( widget ) ) )
        { return false; }

        // store in map and add destroy signal connection
        widget->removeEventFilter( this );
        widget->installEventFilter( this );
        _widgets.insert( widget, 0 );

        /*
        need to install shadow directly when widget "created" state is already set
        since WinID changed is never called when this is the case
        */
        if( widget->testAttribute(Qt::WA_WState_Created) && installX11Shadows( widget ) )
        {  _widgets.insert( widget, widget->winId() ); }

        connect( widget, SIGNAL(destroyed(QObject*)), SLOT(objectDeleted(QObject*)) );

        return true;

    }

    //_______________________________________________________
    void ShadowHelper::unregisterWidget( QWidget* widget )
    {
        if( _widgets.remove( widget ) )
        { uninstallX11Shadows( widget ); }
    }

    //_______________________________________________________
    void ShadowHelper::reloadConfig( void )
    {

        // shadow cache
        KConfig config( "oxygenrc" );
        if( !shadowCache().readConfig( config ) ) return;

        // reset
        reset();

        // retrieve shadow pixmap
        _size = shadowCache().shadowSize();

        QPixmap pixmap( shadowCache().pixmap( ShadowCache::Key() ) );
        {
            QPainter painter( &pixmap );

            // add transparency
            painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            painter.fillRect( pixmap.rect(), QColor( 0, 0, 0, 150 ) );
        }

        // recreate tileset
        _tiles = TileSet( pixmap, pixmap.width()/2, pixmap.height()/2, 1, 1 );

        {
            QPainter painter( &pixmap );

            // add round corners
            const QRect cornerRect( (pixmap.width()-10)/2, (pixmap.height()-10)/2, 10, 10 );
            _helper.roundCorner( QPalette().color( QPalette::Window ) )->render( cornerRect, &painter );
        }

        // recreate tileset
        _dockTiles = TileSet( pixmap, pixmap.width()/2, pixmap.height()/2, 1, 1 );

        // update property for registered widgets
        for( QMap<QWidget*,WId>::const_iterator iter = _widgets.constBegin(); iter != _widgets.constEnd(); ++iter )
        { installX11Shadows( iter.key() ); }

    }

    //_______________________________________________________
    bool ShadowHelper::eventFilter( QObject* object, QEvent* event )
    {

        // check event type
        if( event->type() != QEvent::WinIdChange ) return false;

        // cast widget
        QWidget* widget( static_cast<QWidget*>( object ) );

        // install shadows and update winId
        if( installX11Shadows( widget ) )
        { _widgets.insert( widget, widget->winId() ); }

        return false;

    }

    //_______________________________________________________
    void ShadowHelper::objectDeleted( QObject* object )
    { _widgets.remove( static_cast<QWidget*>( object ) ); }

    //_______________________________________________________
    bool ShadowHelper::isMenu( QWidget* widget ) const
    { return qobject_cast<QMenu*>( widget ); }

    //_______________________________________________________
    bool ShadowHelper::isToolTip( QWidget* widget ) const
    { return widget->inherits( "QTipLabel" ) || (widget->windowFlags() & Qt::WindowType_Mask) == Qt::ToolTip; }

    //_______________________________________________________
    bool ShadowHelper::acceptWidget( QWidget* widget ) const
    {

        if( widget->property( netWMSkipShadowPropertyName ).toBool() ) return false;
        if( widget->property( netWMForceShadowPropertyName ).toBool() ) return true;

        // menus
        if( qobject_cast<QMenu*>( widget ) ) return true;

        // combobox dropdown lists
        if( widget->inherits( "QComboBoxPrivateContainer" ) ) return true;

        // tooltips
        if( (widget->inherits( "QTipLabel" ) || (widget->windowFlags() & Qt::WindowType_Mask) == Qt::ToolTip ) &&
            !widget->inherits( "Plasma::ToolTip" ) )
        { return true; }

        // detached widgets
        if( qobject_cast<QToolBar*>( widget ) || qobject_cast<QDockWidget*>( widget ) )
        { return true; }

        // reject
        return false;
    }

    //_______________________________________________________
    bool ShadowHelper::installX11Shadows( QWidget* widget )
    {

        // check widget and shadow size
        if( _size <= 0 || !widget ) return false;

        #ifdef Q_WS_X11
        #ifndef QT_NO_XRENDER

        // create atom
        if( !_atom ) _atom = XInternAtom( QX11Info::display(), netWMShadowAtomName, False);

        // TODO: also check for NET_WM_SUPPORTED atom, before installing shadow

        /*
        From bespin code. Supposibly prevent playing with some 'pseudo-widgets'
        that have winId matching some other -random- window
        */
        if( !(widget->testAttribute(Qt::WA_WState_Created) || widget->internalWinId() ))
        { return false; }

        // create data
        // add pixmap handles
        QVector<unsigned long> data;
        if( qobject_cast<QDockWidget*>( widget ) )
        {

            data << _dockTiles.x11Pixmap( 1 )
                << _dockTiles.x11Pixmap( 2 )
                << _dockTiles.x11Pixmap( 5 )
                << _dockTiles.x11Pixmap( 8 )
                << _dockTiles.x11Pixmap( 7 )
                << _dockTiles.x11Pixmap( 6 )
                << _dockTiles.x11Pixmap( 3 )
                << _dockTiles.x11Pixmap( 0 );

        } else {

            data << _tiles.x11Pixmap( 1 )
                << _tiles.x11Pixmap( 2 )
                << _tiles.x11Pixmap( 5 )
                << _tiles.x11Pixmap( 8 )
                << _tiles.x11Pixmap( 7 )
                << _tiles.x11Pixmap( 6 )
                << _tiles.x11Pixmap( 3 )
                << _tiles.x11Pixmap( 0 );

        }

        // add padding
        /*
        all 4 paddings are identical, since offsets are handled when generating the pixmaps.
        there is one extra pixel needed with respect to actual shadow size, to deal with how
        menu backgrounds are rendered
        */
        if( isToolTip( widget ) )
        {

            data << _size << _size << _size << _size;

        } else {

            data << _size - 1 << _size - 1 << _size - 1 << _size - 1;

        }

        XChangeProperty(
            QX11Info::display(), widget->winId(), _atom, XA_CARDINAL, 32, PropModeReplace,
            reinterpret_cast<const unsigned char *>(data.constData()), data.size() );

        return true;

        #endif
        #endif

        return false;

    }

    //_______________________________________________________
    void ShadowHelper::uninstallX11Shadows( QWidget* widget ) const
    {

        #ifdef Q_WS_X11
        if( !( widget && widget->testAttribute(Qt::WA_WState_Created) ) ) return;
        XDeleteProperty(QX11Info::display(), widget->winId(), _atom);
        #endif

    }

}
