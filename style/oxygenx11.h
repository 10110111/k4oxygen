#ifndef INCLUDE_ONCE_B863251D_0A4C_4B6F_9A58_2E13272D9A5A
#define INCLUDE_ONCE_B863251D_0A4C_4B6F_9A58_2E13272D9A5A

#include <QtGlobal>
#include <QGuiApplication>

#if HAVE_X11
# if QT_VERSION_CHECK(6,0,0)
#  include <X11/Xlib.h>
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
# else
#  include <X11/Xdefs.h>
#  include <QX11Info>
# endif

// Fix stupid #defines in <X11/Xlib.h>
# undef Bool
typedef int Bool;
# undef None
# undef CursorShape
enum
{
    None = 0,
    CursorShape = 0,
};

#endif

#endif
