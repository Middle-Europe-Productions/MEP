
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
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")
namespace PLATFORM {
    /**
    * Makes the window open for alpha channel and deletes the WS_CAPTION tag. 
    * Background of a window is now transparent if m_backgroundColor is transparent.
    */
    inline bool transparent(HWND hWnd) {
        MARGINS margins = {-1};
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        return true;
    }
    inline bool blurBehind(HWND hWnd) {
        HRESULT hr = S_OK;

        // Create and populate the blur-behind structure.
        DWM_BLURBEHIND bb = { 0 };

        // Specify blur-behind and blur region.
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = true;
        bb.hRgnBlur = NULL;

        // Enable blur-behind.
        hr = DwmEnableBlurBehindWindow(hWnd, &bb);
        if (SUCCEEDED(hr))
        {
            return true;
        }
        else {
            return false;
        }
    }
    /**
    * Provides an ability to manipulate general transparency of a window.
    * @param[in] alpha : Value of a alpha channel.
    */
    inline bool transparency(HWND hWnd, unsigned char alpha)
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
        return true;
    }
    /**
    * Gives an abillity to minimalize a window on a call.
    * Usefull with the use of mep HUB
    */
    inline bool minimalize(HWND hWnd) {
        ShowWindow(hWnd, SW_MINIMIZE);
        //AnimateWindow(hWnd, 100, AW_SLIDE | AW_HIDE);
        return 0;
    }
    inline void maximalize(HWND hWnd) {
        //customWindow(hWnd);
    }
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
