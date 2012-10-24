#include "Window.h"
#include "resource.h"
#include "../debug.h"
#include "util.h"

#include <cassert>

#include <iostream>


ATOM Window::_windowClass(0);


Window::Window(const HINSTANCE &hInst, const HWND &hWndParent) :
    _hInst(hInst),
    _hWnd(0),
    _hWndParent(hWndParent)
#if 0
    _isDialog(false)
#endif
{
    // Register Window Class if that isn't done yet
    if (!_windowClass)
    {
        RegisterWindowClass(hInst);
    };

    assert(_windowClass);
}

Window::~Window()
{
    if (_hWnd)
    {
        PostMessage(_hWnd, WM_CLOSE, 0, 0);
    }

    _hWnd = 0;
}


HWND Window::Create(const LPCTSTR &title, const HWND &hWndParent, const int &iCmdShow)
{
    _hWndParent = hWndParent;

    // Create window
    _hWnd = CreateWindowEx(
            WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,   // Extended style
            MAKEINTATOM(_windowClass),                  // Window class
            title,                                      // Window title
            WS_OVERLAPPEDWINDOW,                        // Window style
            CW_USEDEFAULT,                              // X value
            CW_USEDEFAULT,                              // Y value
            CW_USEDEFAULT,                              // Width
            CW_USEDEFAULT,                              // Height
            _hWndParent,                                // Parent window
            NULL,                                       // Menu
            _hInst,                                     // Module instance for the window
            this);                                      // User data

    assert(_hWnd);

    ShowWindow(_hWnd, iCmdShow);
    UpdateWindow(_hWnd);

    return _hWnd;
}


#if 0
INT_PTR Window::Dialog(const LPCTSTR &lpTemplate, const HWND &hWndParent)
{
    _hWndParent = hWndParent;

    return DialogBox(_hInst, lpTemplate, _hWndParent, reinterpret_cast<DLGPROC>(Window::InitialWindowProc));
}
#endif


#include "wm_lookup.h"

LRESULT CALLBACK Window::InitialWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //TRACE("Handling hWnd " << hWnd << ", uMsg " << uMsg << ": " << _WM_LOOKUP(uMsg));

    if (uMsg == WM_NCCREATE)
    {
        LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        assert(createStruct->lpCreateParams);

        reinterpret_cast<Window*>(createStruct->lpCreateParams)->_hWnd = hWnd;

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC,  reinterpret_cast<LONG_PTR>(&Window::WindowProc));

        return WindowProc(hWnd, uMsg, wParam, lParam);
    }

    DEBUG("Default handler for hWnd " << hWnd << ": " << _WM_LOOKUP(uMsg) << "(" << uMsg << ")");
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //TRACE("Handling hWnd " << hWnd << ", uMsg " << uMsg << ": " << _WM_LOOKUP(uMsg));
    Window *thisWindow  = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    assert(thisWindow);


    switch(uMsg)
    {
        // Client messages
#define CLIENT_HANDLER(msg,                 hnd)                case WM_ ## msg : return thisWindow->On ## hnd (uMsg, wParam, lParam);
        CLIENT_HANDLER(ACTIVATE,            Activate);
        CLIENT_HANDLER(ACTIVATEAPP,         ActivateApp);
        CLIENT_HANDLER(CANCELMODE,          CancelMode);
        CLIENT_HANDLER(CAPTURECHANGED,      CaptureChanged);
        CLIENT_HANDLER(CLOSE,               Close);
        CLIENT_HANDLER(COMMAND,             Command);
        CLIENT_HANDLER(CONTEXTMENU,         ContextMenu);
        CLIENT_HANDLER(CREATE,              Create);
        CLIENT_HANDLER(DESTROY,             Destroy);
        CLIENT_HANDLER(ENABLE,              Enable);
        CLIENT_HANDLER(ENTERIDLE,           EnterIdle);
        CLIENT_HANDLER(ENTERMENULOOP,       EnterMenuLoop);
        CLIENT_HANDLER(ERASEBKGND,          EraseBkgnd);
        CLIENT_HANDLER(EXITMENULOOP,        ExitMenuLoop);
        CLIENT_HANDLER(GETICON,             GetIcon);
        CLIENT_HANDLER(GETMINMAXINFO,       GetMinMaxInfo);
        CLIENT_HANDLER(INITMENU,            InitMenu);
        CLIENT_HANDLER(INITMENUPOPUP,       InitMenuPopup);
        CLIENT_HANDLER(KILLFOCUS,           KillFocus);
        CLIENT_HANDLER(LBUTTONDOWN,         LButtonDown);
        CLIENT_HANDLER(LBUTTONUP,           LButtonUp);
        CLIENT_HANDLER(MBUTTONDOWN,         MButtonDown);
        CLIENT_HANDLER(MBUTTONUP,           MButtonUp);
        CLIENT_HANDLER(MENUSELECT,          MenuSelect);
        CLIENT_HANDLER(MOUSEACTIVATE,       MouseActivate);
        CLIENT_HANDLER(MOUSEMOVE,           MouseMove);
        CLIENT_HANDLER(MOVE,                Move);
        CLIENT_HANDLER(NOTIFYFORMAT,        NotifyFormat);
        CLIENT_HANDLER(PAINT,               Paint);
        CLIENT_HANDLER(PARENTNOTIFY,        ParentNotify);
        CLIENT_HANDLER(QUERYNEWPALETTE,     QueryNewPalette);
        CLIENT_HANDLER(QUERYOPEN,           QueryOpen);
        CLIENT_HANDLER(RBUTTONDOWN,         RButtonDown);
        CLIENT_HANDLER(RBUTTONUP,           RButtonUp);
        CLIENT_HANDLER(SETCURSOR,           SetCursor);
        CLIENT_HANDLER(SETFOCUS,            SetFocus);
        CLIENT_HANDLER(SHOWWINDOW,          ShowWindow);
        CLIENT_HANDLER(SIZE,                Size);
        CLIENT_HANDLER(SYSCOMMAND,          SysCommand);
        CLIENT_HANDLER(UNINITMENUPOPUP,     UninitMenuPopup);
        CLIENT_HANDLER(WINDOWPOSCHANGED,    WindowPosChanged);
        CLIENT_HANDLER(WINDOWPOSCHANGING,   WindowPosChanging);
#undef CLIENT_HANDLER

        // Non-client messages
#define NONCLIENT_HANDLER(msg,          hnd)                    case WM_NC ## msg : return thisWindow->Nc ## hnd (uMsg, wParam, lParam);
        NONCLIENT_HANDLER(ACTIVATE,     Activate);
        NONCLIENT_HANDLER(CALCSIZE,     CalcSize);
        NONCLIENT_HANDLER(CREATE,       Create);
        NONCLIENT_HANDLER(DESTROY,      Destroy);
        NONCLIENT_HANDLER(HITTEST,      HitTest);
        NONCLIENT_HANDLER(LBUTTONDOWN,  LButtonDown);
        NONCLIENT_HANDLER(MOUSEMOVE,    MouseMove);
        NONCLIENT_HANDLER(PAINT,        Paint);
#undef NONCLIENT_HANDLER


        default:
            DEBUG("Default handler for hWnd " << hWnd << ": " << _WM_LOOKUP(uMsg) << "(" << uMsg << ")");
            return thisWindow->Default(uMsg, wParam, lParam);
    }
}


ATOM Window::RegisterWindowClass(const HINSTANCE &hInst)
{
    assert(_windowClass == 0);

    // Setup window class
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = Window::InitialWindowProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInst;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
    wcex.lpszClassName  = L"GPX Tool";
    wcex.hIconSm        = NULL;

    _windowClass = RegisterClassEx(&wcex);
    if (!_windowClass)
    {
        throw "Could not register window class";
    }

    return _windowClass;
}
