#include<MEPWindow/WindowCrossPlatform.h>
#if defined(MEP_WINDOWS)

#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")
namespace PLATFORM
{
    bool TOOLS::transparent(HWND hWnd)
    {
        MARGINS margins = { -1 };
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        return true;
    }
    bool TOOLS::blurBehind(HWND hWnd) 
    {
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
    bool TOOLS::transparency(HWND hWnd, unsigned char alpha)
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
        return true;
    }
    /**
    * Gives an abillity to minimalize a window on a call.
    * Usefull with the use of mep HUB
    */
    bool TOOLS::minimalize(HWND hWnd) {
        ShowWindow(hWnd, SW_MINIMIZE);
        //AnimateWindow(hWnd, 100, AW_SLIDE | AW_HIDE);
        return 0;
    }
    void TOOLS::maximalize(HWND hWnd) {
        //customWindow(hWnd);
    }
}
#endif