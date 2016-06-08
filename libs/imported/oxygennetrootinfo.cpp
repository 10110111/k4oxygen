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
