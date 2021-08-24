
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
#ifndef MEP_WINDOW_CROSS_PLATFORM_H
#define MEP_WINDOW_CROSS_PLATFORM_H

#include <SFML/Graphics.hpp>
#include <MEPWindow/OSSetUp.h>
#if defined (MEP_WINDOWS)
#include <windows.h>
namespace PLATFORM {
    class TOOLS
    {
    public:
        TOOLS() = delete;
        TOOLS(const TOOLS&) = delete;
        TOOLS(TOOLS&&) = delete;
        ~TOOLS() = delete;
        /**
        * Makes the window open for alpha channel and deletes the WS_CAPTION tag.
        * Background of a window is now transparent if m_backgroundColor is transparent.
        */
        static bool transparent(HWND hWnd);
        static bool blurBehind(HWND hWnd);
        /**
        * Provides an ability to manipulate general transparency of a window.
        * @param[in] alpha : Value of a alpha channel.
        */
        static bool transparency(HWND hWnd, unsigned char alpha);
        /**
        * Gives an abillity to minimalize a window on a call.
        * Usefull with the use of mep HUB
        */
        static bool minimalize(HWND hWnd);
        static void maximalize(HWND hWnd);
    };
}
#elif defined (MEP_LINUX)

#include <X11/Xlib.h>
#include <X11/Xatom.h>


#undef Status

namespace PLATFORM {
    inline bool transparent(sf::WindowHandle) {
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

    inline bool minimalize(Window win) {
    	// function for minimze your app
    	XWindowAttributes attr = { 0 };
    	Display* display = XOpenDisplay(NULL);
	XGetWindowAttributes (display, win, &attr);
	int s = XScreenNumberOfScreen (attr.screen);
	XIconifyWindow(display, win, s);
        XCloseDisplay(display);
        return true;
    }
    inline void maximalize(sf::WindowHandle) {
    
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

#endif /*MEP_WINDOW_CROSS_PLATFORM_H*/
