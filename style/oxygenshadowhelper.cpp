//////////////////////////////////////////////////////////////////////////////
// oxygenshadowhelper.h
// handle shadow pixmaps passed to window manager via X property
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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
#include "oxygenshadowcache.h"
#include "oxygenstylehelper.h"

#include <QDockWidget>
#include <QMenu>
#include <QtGui/QPainter>
#include <QToolBar>
#include <QtCore/QTextStream>
#include <QtCore/QEvent>

#if HAVE_X11
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xlib-xcb.h>
#endif

namespace Oxygen
{

    const char* const ShadowHelper::netWMShadowAtomName( "_KDE_NET_WM_SHADOW" );
    const char* const ShadowHelper::netWMForceShadowPropertyName( "_KDE_NET_WM_FORCE_SHADOW" );
    const char* const ShadowHelper::netWMSkipShadowPropertyName( "_KDE_NET_WM_SKIP_SHADOW" );

#if HAVE_X11
    static inline xcb_connection_t* getXCBConnection()
    {
        return XGetXCBConnection(QX11Info::display());
    }
    static inline void freePixmap(PixmapHandle pixmap)
    {
        xcb_free_pixmap(getXCBConnection(),pixmap);
    }
#endif

    //_____________________________________________________
    ShadowHelper::ShadowHelper( QObject* parent, StyleHelper& helper ):
        QObject( parent ),
        _helper( helper ),
        _shadowCache( new ShadowCache( helper ) ),
        _size( 0 )
        #if HAVE_X11
        ,_atom( None )
        #endif
    {
        #if HAVE_X11

        // Make a valid graphic context using a dummy pixmap
        if(_helper.x11Present())
        {
            xcb_connection_t*const xcbc=getXCBConnection();
            gc_=xcb_generate_id(xcbc);
            xcb_pixmap_t dummyPixmap = xcb_generate_id(xcbc);
            xcb_create_pixmap(xcbc, 32, dummyPixmap, QX11Info::appRootWindow(), 1, 1);
            xcb_create_gc(xcbc,gc_,dummyPixmap,0,0);
            xcb_free_pixmap(xcbc,dummyPixmap);
        }

        #endif
    }

    //_______________________________________________________
    ShadowHelper::~ShadowHelper( void )
    {

        #if HAVE_X11
        foreach(const PixmapHandle& value, _pixmaps)
            if(value)
                freePixmap(value);
        foreach(const PixmapHandle& value, _dockPixmaps)
            if(value)
                freePixmap(value);
        #endif

        delete _shadowCache;

    }

    //______________________________________________
    void ShadowHelper::reset( void )
    {
        #if HAVE_X11
        if(_helper.x11Present())
        {
            // round pixmaps
            foreach( const PixmapHandle& value, _pixmaps  ) freePixmap(value);
            foreach( const PixmapHandle& value, _dockPixmaps  ) freePixmap(value);
        }
        #endif

        _pixmaps.clear();
        _dockPixmaps.clear();

        _tiles = TileSet();
        _dockTiles = TileSet();

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
        shadowCache().readConfig();

        // reset
        reset();

        // retrieve shadow pixmap
        _size = shadowCache().shadowSize();

        QPixmap pixmap( shadowCache().pixmap( ShadowCache::Key() ) );
        if( !pixmap.isNull() )
        {
            QPainter painter( &pixmap );

            // add transparency
            painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            painter.fillRect( pixmap.rect(), QColor( 0, 0, 0, 150 ) );
        }

        // recreate tileset
        _tiles = TileSet( pixmap, pixmap.width()/2, pixmap.height()/2, 1, 1 );

        if( !pixmap.isNull() )
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
    bool ShadowHelper::isDockWidget( QWidget* widget ) const
    { return qobject_cast<QDockWidget*>( widget ); }

    //_______________________________________________________
    bool ShadowHelper::isToolBar( QWidget* widget ) const
    { return qobject_cast<QToolBar*>( widget ) || widget->inherits( "Q3ToolBar" ); }

    //_______________________________________________________
    bool ShadowHelper::acceptWidget( QWidget* widget ) const
    {

        // flags
        if( widget->property( netWMSkipShadowPropertyName ).toBool() ) return false;
        if( widget->property( netWMForceShadowPropertyName ).toBool() ) return true;

        // menus
        if( isMenu( widget ) ) return true;

        // combobox dropdown lists
        if( widget->inherits( "QComboBoxPrivateContainer" ) ) return true;

        // tooltips
        if( isToolTip( widget ) && !widget->inherits( "Plasma::ToolTip" ) )
        { return true; }

        // detached widgets
        if( isDockWidget( widget ) || isToolBar( widget ) )
        { return true; }

        // reject
        return false;
    }

    //______________________________________________
    const QVector<PixmapHandle>& ShadowHelper::createPixmapHandles( bool isDockWidget )
    {

        /*!
        shadow atom and property specification available at
        http://community.kde.org/KWin/Shadow
        */

        // create atom
        #if HAVE_X11
        if(!_atom && _helper.x11Present())
            _atom = XInternAtom( QX11Info::display(), netWMShadowAtomName, False);
        #endif

        // make sure size is valid
        if( _size <= 0 ) return _pixmaps;

        // make sure pixmaps are not already initialized
        if( isDockWidget )
        {
            // make sure pixmaps are not already initialized
            if( _dockPixmaps.empty() && _dockTiles.isValid() )
            {

                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 1 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 2 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 5 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 8 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 7 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 6 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 3 ) ) );
                _dockPixmaps.push_back( createPixmap( _dockTiles.pixmap( 0 ) ) );

            }

        } else if( _pixmaps.empty() && _tiles.isValid() ) {

            _pixmaps.push_back( createPixmap( _tiles.pixmap( 1 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 2 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 5 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 8 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 7 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 6 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 3 ) ) );
            _pixmaps.push_back( createPixmap( _tiles.pixmap( 0 ) ) );

        }

        // return relevant list of pixmap handles
        return isDockWidget ? _dockPixmaps:_pixmaps;

    }

    //______________________________________________
    PixmapHandle ShadowHelper::createPixmap( const QPixmap& source ) const
    {

        // do nothing for invalid pixmaps
        if( source.isNull() ) return 0;

        /*
        in some cases, pixmap handle is invalid. This is the case notably
        when Qt uses to RasterEngine. In this case, we create an X11 Pixmap
        explicitly and draw the source pixmap on it.
        */

        #if HAVE_X11
        if(!_helper.x11Present()) return 0;

        const int width( source.width() );
        const int height( source.height() );

        xcb_connection_t*const xcbc=getXCBConnection();
        // create X11 pixmap
        xcb_pixmap_t pixmap = xcb_generate_id(xcbc);
        xcb_create_pixmap(xcbc, 32, pixmap, QX11Info::appRootWindow(), width, height);

        // Create image from QPixmap and push it to pixmap
        QImage image=source.toImage();
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        const int sizeInBytes = image.sizeInBytes();
#else
        const int sizeInBytes = image.byteCount();
#endif
        xcb_put_image(xcbc,XCB_IMAGE_FORMAT_Z_PIXMAP,pixmap,gc_,
                        image.width(),image.height(),0,0,
                        0,32,sizeInBytes,image.constBits());

        return pixmap;
        #else
        return 0;
        #endif

    }

    //_______________________________________________________
    bool ShadowHelper::installX11Shadows( QWidget* widget )
    {

        // check widget and shadow
        if( !widget ) return false;

        #if HAVE_X11
        if(!_helper.x11Present()) return false;
        #ifndef QT_NO_XRENDER

        // TODO: also check for NET_WM_SUPPORTED atom, before installing shadow

        /*
        From bespin code. Supposibly prevent playing with some 'pseudo-widgets'
        that have winId matching some other -random- window
        */
        /* edited by 10110111 to match QWidget::winId()'s logic for
           determination whether it needs to create a new window Id, as well as
           the opposite condition in ArgbHelper::setupTransparency() */
        if( !widget->testAttribute(Qt::WA_WState_Created) || !widget->internalWinId() )
        { return false; }

        // create pixmap handles if needed
        const bool isDockWidget( this->isDockWidget( widget ) || this->isToolBar( widget ) );
        const QVector<PixmapHandle>& pixmaps( createPixmapHandles( isDockWidget ) );
        if( pixmaps.size() != numPixmaps ) return false;

        // create data
        // add pixmap handles
        QVector<unsigned long> data;
        foreach( const PixmapHandle& value, pixmaps )
        { data.push_back( value ); }

        // add padding
        /*
        in most cases all 4 paddings are identical, since offsets are handled when generating the pixmaps.
        There is one extra pixel needed with respect to actual shadow size, to deal with how
        menu backgrounds are rendered.
        Some special care is needed for QBalloonTip, since the later have an arrow
        */

        if( isToolTip( widget ) )
        {
            if( widget->inherits( "QBalloonTip" ) )
            {

                // balloon tip needs special margins to deal with the arrow
                int top = 0;
                int bottom = 0;
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
                const auto margins = widget->contentsMargins();
                top = margins.top();
                bottom = margins.bottom();
#else
                widget->getContentsMargins(NULL, &top, NULL, &bottom );
#endif

                // also need to decrement default size further due to extra hard coded round corner
                const int size = _size - 2;

                // it seems arrow can be either to the top or the bottom. Adjust margins accordingly
                if( top > bottom ) data << size - (top - bottom) << size << size << size;
                else data << size << size << size - (bottom - top) << size;

            } else {
                data << _size << _size << _size << _size;
            }

        } else if( isToolBar( widget ) ) {

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

        #if HAVE_X11
        if( !( widget && widget->testAttribute(Qt::WA_WState_Created) ) ) return;
        if(_helper.x11Present())
            XDeleteProperty(QX11Info::display(), widget->winId(), _atom);
        #endif

    }

    //_______________________________________________________
    void ShadowHelper::uninstallX11Shadows( WId id ) const
    {

        #if HAVE_X11
        if(_helper.x11Present())
            XDeleteProperty(QX11Info::display(), id, _atom);
        #endif

    }

}
