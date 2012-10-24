#ifndef INC_WINDOW_H
#define INC_WINDOW_H

#include <windows.h>

#include "../common.h"

class Window
{
public:
    //// Window related
    // Constructor
    Window(const HINSTANCE &hInst, const HWND &hWndParent = NULL);
    virtual ~Window();


    // Put window on screen. These functions return immediately after the window
    // has been created with the HWND of the new window.
    HWND Create(const LPCTSTR &title, const int &iCmdShow = SW_SHOWNORMAL) { return Create(title, _hWndParent, iCmdShow); };
    HWND Create(const LPCTSTR &title, const HWND &hWndParent, const int &iCmdShow = SW_SHOWNORMAL);

#if 0
    // Put dialog on the screen. These functions return when the dialog has been
    // dismissed. The return value is the value passed to the EndDialog() function
    // used to terminate the dialog.
    INT_PTR Dialog(const LPCTSTR &lpTemplate) { return Dialog(lpTemplate, _hWndParent) ; };
    INT_PTR Dialog(const WORD &wResource)     { return Dialog(wResource, _hWndParent); };

    INT_PTR Dialog(const LPCTSTR &lpTemplate, const HWND &hWndParent);
    INT_PTR Dialog(const WORD &wResource,     const HWND &hWndParent) { return Dialog(MAKEINTRESOURCE(wResource), hWndParent); };
#endif

protected:
    // Data members
    HINSTANCE   _hInst;
    HWND        _hWnd;
    HWND        _hWndParent;

#if 0
    bool        _isDialog;
#endif

    //// Window message handlers
    // Client messages
    // The handlers have the following signature:
    //   virtual LRESULT OnXxx (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam)
    // and the appropriate handler is called for each WM_XXX message
    // that is received by the window proc.
#define CLIENT_HANDLER(msg)             virtual LRESULT On ## msg (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam) { return Default(uMsg, wParam, lParam); };
    CLIENT_HANDLER(Activate)
    CLIENT_HANDLER(ActivateApp)
    CLIENT_HANDLER(CancelMode)
    CLIENT_HANDLER(CaptureChanged)
    CLIENT_HANDLER(Close)
    CLIENT_HANDLER(Command)
    CLIENT_HANDLER(ContextMenu)
    CLIENT_HANDLER(Create)
    virtual LRESULT OnDestroy           (const UINT &UNUSED(uMsg), const WPARAM &UNUSED(wParam), const LPARAM &UNUSED(lParam)) { PostQuitMessage(0); return 0; };
    CLIENT_HANDLER(Enable)
    CLIENT_HANDLER(EnterIdle)
    CLIENT_HANDLER(EnterMenuLoop)
    CLIENT_HANDLER(EraseBkgnd)
    CLIENT_HANDLER(ExitMenuLoop)
    CLIENT_HANDLER(GetIcon)
    CLIENT_HANDLER(GetMinMaxInfo)
    CLIENT_HANDLER(InitMenu)
    CLIENT_HANDLER(InitMenuPopup)
    CLIENT_HANDLER(KillFocus)
    CLIENT_HANDLER(LButtonDown)
    CLIENT_HANDLER(LButtonUp)
    CLIENT_HANDLER(MButtonDown)
    CLIENT_HANDLER(MButtonUp)
    CLIENT_HANDLER(MenuSelect)
    CLIENT_HANDLER(MouseActivate)
    CLIENT_HANDLER(MouseMove)
    CLIENT_HANDLER(Move)
    CLIENT_HANDLER(NotifyFormat)
    CLIENT_HANDLER(Paint)
    CLIENT_HANDLER(ParentNotify)
    CLIENT_HANDLER(QueryNewPalette)
    CLIENT_HANDLER(QueryOpen)
    CLIENT_HANDLER(RButtonDown)
    CLIENT_HANDLER(RButtonUp)
    CLIENT_HANDLER(SetCursor)
    CLIENT_HANDLER(SetFocus)
    CLIENT_HANDLER(ShowWindow)
    CLIENT_HANDLER(Size)
    CLIENT_HANDLER(SysCommand)
    CLIENT_HANDLER(UninitMenuPopup)
    CLIENT_HANDLER(WindowPosChanged)
    CLIENT_HANDLER(WindowPosChanging)
#undef CLIENT_HANDLER

    // Non-client messages
    // The handlers have the following signature:
    //   virtual LRESULT NcXxx (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam)
    // and the appropriate handler is called for each WM_NCXXX message
    // that is received by the window proc.
#define NONCLIENT_HANDLER(msg)          virtual LRESULT Nc ## msg (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam) { return Default(uMsg, wParam, lParam); };
    NONCLIENT_HANDLER(Activate)
    NONCLIENT_HANDLER(CalcSize)
    NONCLIENT_HANDLER(Create)
    NONCLIENT_HANDLER(Destroy)
    NONCLIENT_HANDLER(HitTest)
    NONCLIENT_HANDLER(LButtonDown)
    NONCLIENT_HANDLER(MouseMove)
    NONCLIENT_HANDLER(Paint)
#undef NONCLIENT_HANDLER


#if 0
    virtual LRESULT Default             (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam) { return _isDialog ? FALSE : DefWindowProc(_hWnd, uMsg, wParam, lParam); };
#endif
    virtual LRESULT Default             (const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam) { return DefWindowProc(_hWnd, uMsg, wParam, lParam); };


private:
    // Window related
    static LRESULT CALLBACK InitialWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


    // Window class related
    static ATOM RegisterWindowClass(const HINSTANCE &hInst);

    static ATOM _windowClass;
};

#endif  // INC_WINDOW_H
