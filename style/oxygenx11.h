#ifndef INCLUDE_ONCE_B863251D_0A4C_4B6F_9A58_2E13272D9A5A
#define INCLUDE_ONCE_B863251D_0A4C_4B6F_9A58_2E13272D9A5A

#include <QtGlobal>

#if HAVE_X11 && QT_VERSION >= QT_VERSION_CHECK(6,0,0)

# include <QGuiApplication>
# include <X11/Xlib.h>
class QX11Info
{
public:
    static Display* display()
    {
        const auto x11app = qGuiApp->nativeInterface<QNativeInterface::QX11Application>();
        if(!x11app) return nullptr;
        return reinterpret_cast<Display*>(x11app->display());
    }
    static Window appRootWindow() { return DefaultRootWindow(display()); }
};

# ifndef Q_WS_X11
#  define Q_WS_X11
# endif
#include "fixx11h.h"

#else

# include <QX11Info>
# include <X11/Xdefs.h>

#endif

#endif
