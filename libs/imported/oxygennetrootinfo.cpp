#include "oxygennetrootinfo.h"
#include <cassert>

static Atom net_wm_moveresize;
const unsigned long netwm_sendevent_mask = (SubstructureRedirectMask|
                         SubstructureNotifyMask);

namespace Oxygen
{
// Taken from netwm.cpp
void NETRootInfo::moveResizeRequest(Window window, int x_root, int y_root,
                    Direction direction)
{

#ifdef    NETWMDEBUG
    fprintf(stderr,
        "NETRootInfo::moveResizeRequest: requesting resize/move for 0x%lx (%d, %d, %d)\n",
        window, x_root, y_root, direction);
#endif

    XEvent e;

    e.xclient.type = ClientMessage;
    e.xclient.message_type = net_wm_moveresize;
    e.xclient.display = display;
    e.xclient.window = window,
    e.xclient.format = 32;
    e.xclient.data.l[0] = x_root;
    e.xclient.data.l[1] = y_root;
    e.xclient.data.l[2] = direction;
    e.xclient.data.l[3] = 0l;
    e.xclient.data.l[4] = 0l;

    XSendEvent(display, root, False, netwm_sendevent_mask, &e);
}

bool NETRootInfo::staticInit()
{
    return (net_wm_moveresize=XInternAtom(display,"_NET_WM_MOVERESIZE",False));
}

NETRootInfo::NETRootInfo(Display* display, unsigned long prop, int screen)
    : display(display),
      root(RootWindow(display,screen))
{
    assert(prop==WMMoveResize); (void)prop;
    static const bool _ = (staticInit(),true); (void)_;
}

}
