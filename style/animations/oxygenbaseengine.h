#ifndef oxygenbaseengine_h
#define oxygenbaseengine_h

//////////////////////////////////////////////////////////////////////////////
// oxygenbaseengine.h
// base engine
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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

#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QPointer>

namespace Oxygen
{

    //! base class for all animation engines
    /*! it is used to store configuration values used by all animations stored in the engine */
    class BaseEngine: public QObject
    {

        Q_OBJECT

        public:

        typedef QPointer<BaseEngine> Pointer;

        //! constructor
        explicit BaseEngine( QObject* parent ):
            QObject( parent ),
            _enabled( true ),
            _duration( 200 )
        {}

        //! destructor
        virtual ~BaseEngine( void )
        {}

        //! enability
        virtual void setEnabled( bool value )
        { _enabled = value; }

        //! enability
        virtual bool enabled( void ) const
        { return _enabled; }

        //! duration
        virtual void setDuration( int value )
        { _duration = value; }

        //! duration
        virtual int duration( void ) const
        { return _duration; }

        //! unregister widget
        virtual bool unregisterWidget( QObject* object ) = 0;

        //! list of widgets
        typedef QSet<QWidget*> WidgetList;

        //! returns registered widgets
        virtual WidgetList registeredWidgets( void ) const
        { return WidgetList(); }

        private:

        //! engine enability
        bool _enabled;

        //! animation duration
        int _duration;

    };

}

#endif
