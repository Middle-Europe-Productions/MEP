
////////////////////////////////////////////////////////////
//
//	WinddowCrossPlatform.h created with the use of SFML
//	MEP - Middle Europe Productions
//  Work in progress. 
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
//
//
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>
#if defined (SFML_SYSTEM_WINDOWS)
#include <windows.h>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")
namespace PLATFORM {
    //Makes the window open in transparent mode.
    //Background of a window is now transparent.
    inline bool transparent(HWND hWnd) {
        MARGINS margins;
        margins.cxLeftWidth = -1;

        SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        return true;
    }

    //Provides an ability to manipulate general transparency of a window.
    inline bool transparency(HWND hWnd, unsigned char alpha)
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
        return true;
    }

    //Gives an abillity to minimalize a window on a call.
    //Usefull with the use of mep HUB
    inline bool minimalize(HWND hWnd) {
        return ShowWindow(hWnd, SW_MINIMIZE);
    }
}
#elif defined (SFML_SYSTEM_LINUX)
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>
namespace PLATFORM {
    inline bool transparent(Window wnd) {
        return false;
    }

    inline bool transparency(Window wnd, unsigned char alpha)
    {
        Display* display = XOpenDisplay(NULL);
        unsigned long opacity = (0xffffffff / 0xff) * alpha;
        Atom property = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", false);
        if (property != None)
        {
            XChangeProperty(display, wnd, property, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&opacity, 1);
            XFlush(display);
            XCloseDisplay(display);
            return true;
        }
        else
        {
            XCloseDisplay(display);
            return false;
        }
    }

    inline bool minimalize(Window wnd) {
        return false;
    }
}
#undef None // None conflicts with SFML
#elif defined (SFML_SYSTEM_MACOS)
    inline bool PLATFORM::transparent(sf::WindowHandle handle);
    inline bool PLATFORM::transparency(sf::WindowHandle handle, unsigned char alpha);
    inline bool PLATFORM::minimalize(sf::WindowHandle handle);
#else
    bool setShape(sf::WindowHandle handle)
    {
        return false;
    }

    bool setTransparency(sf::WindowHandle handle, unsigned char alpha)
    {
        return false;
    }
#endif