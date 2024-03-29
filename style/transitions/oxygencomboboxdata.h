#ifndef oxygencombobox_datah
#define oxygencombobox_datah

//////////////////////////////////////////////////////////////////////////////
// oxygencomboboxdata.h
// data container for QComboBox transition
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

#include "oxygentransitiondata.h"

#include <QtCore/QString>
#include <QtCore/QBasicTimer>
#include <QtCore/QTimerEvent>
#include <QComboBox>
#include <QLineEdit>

namespace Oxygen
{

    //! generic data
    class ComboBoxData: public TransitionData
    {

        Q_OBJECT

        public:

        //! constructor
        ComboBoxData( QObject*, QComboBox*, int );

        //! destructor
        virtual ~ComboBoxData( void )
        {}

        //! event filter
        virtual bool eventFilter( QObject*, QEvent* );

        protected:

        //! timer event
        virtual void timerEvent( QTimerEvent* );

        //! target rect
        /*! return rect corresponding to the area to be updated when animating */
        QRect targetRect( void ) const
        { return _target ? _target.data()->rect().adjusted( 5, 5, -5, -5 ):QRect(); }

        protected slots:

        //! triggered when item is activated in combobox
        virtual void  indexChanged( void );

        //! initialize animation
        virtual bool initializeAnimation( void );

        //! animate
        virtual bool animate( void );

        //! called when target is destroyed
        virtual void targetDestroyed( void );

        private:

        //! needed to start animations out of parent paintEvent
        QBasicTimer _timer;

        //! target
        QPointer<QComboBox> _target;

    };

}

#endif
