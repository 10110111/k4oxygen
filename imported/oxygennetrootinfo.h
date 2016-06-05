#ifndef OXYGEN_NETWM_20160605
#define OXYGEN_NETWM_20160605

#include <X11/Xlib.h>
#include "oxygenmacros.h"

namespace Oxygen
{
// See netwm_def.h for enums
struct NET
{
    enum Property {
    WMMoveResize          = 1<<14,
    };

    /**
       Direction for WMMoveResize.

       When a client wants the Window Manager to start a WMMoveResize, it should
       specify one of:

       @li TopLeft
       @li Top
       @li TopRight
       @li Right
       @li BottomRight
       @li Bottom
       @li BottomLeft
       @li Left
       @li Move (for movement only)
       @li KeyboardSize (resizing via keyboard)
       @li KeyboardMove (movement via keyboard)
    **/

    enum Direction {
    TopLeft      = 0,
    Top          = 1,
    TopRight     = 2,
    Right        = 3,
    BottomRight  = 4,
    Bottom       = 5,
    BottomLeft   = 6,
    Left         = 7,
    Move         = 8,  // movement only
    KeyboardSize = 9,  // size via keyboard
    KeyboardMove = 10, // move via keyboard
    MoveResizeCancel = 11 // to ask the WM to stop moving a window
    };

};
class KDE_EXPORT NETRootInfo : public NET
{
    Display* display;
    Window root;
    bool staticInit();
public:
    NETRootInfo(Display* display, unsigned long prop, int screen=-1);
    void moveResizeRequest(Window window, int x_root, int y_root, Direction direction);
};

}

#endif
