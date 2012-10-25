#include "Gui.h"

#include "../common.h"
#include "../debug.h"

#include "../GpxTool.h"

#include "util.h"

#include <cassert>
#include <string>
#include <vector>

#include <commctrl.h>
#include <commdlg.h>

#include "resource.h"

// Singleton implementation
Gui *Gui::_instance = 0;


// Methods
bool Gui::Setup(const HINSTANCE &hInst, const int &iCmdShow)
{
    assert(_instance == 0);

    // Ensure common control DLL is loaded
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_BAR_CLASSES;

    if (!InitCommonControlsEx(&icex))
    {
        return false;
    }



    try
    {
        _instance = new Gui(hInst, iCmdShow);
    }
    catch (std::string &e)
    {
        MessageBox(NULL,
                utf8tows(e).c_str(),
                L"GPX Tool",
                MB_OK | MB_ICONERROR);

        _instance = 0;
        return false; // TODO: throw?
    }

    return true;
}


void Gui::Cleanup()
{
}


void Gui::DoOpenGpx()
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    TCHAR filename[4096] = { 0 };

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = _hWnd;
    ofn.lpstrFilter =   L"GPX files (*.gpx)\0"  "*.gpx\0"
                         "Text files (*.txt)\0" "*.txt\0"
                         "All files (*.*)\0"    "*.*\0"
                         "\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = 4096;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = OFN_ALLOWMULTISELECT
        | OFN_EXPLORER
        | OFN_FILEMUSTEXIST
        | OFN_HIDEREADONLY
        | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = L"gpx";
    ofn.FlagsEx = 0;

    if (!GetOpenFileName(&ofn))
    {
        DEBUG("No file opened");
        return;
    }

    std::vector<std::string> filenames;
    DEBUG("User requested file(s):");
    for (PTCHAR pt = filename; *pt != 0; )
    {
        DEBUG("- '" << pt << "'");
        filenames.push_back(wstoutf8(pt));
        pt += wcslen(pt) + 1;
    }

    if (filenames.size() > 1)
    {
        // More than 1 file selected: the first entry is the path, the
        // following entries are filenames.
        // Prepend the path to all filenames and remove the path entry.
        for(std::vector<std::string>::iterator it = ++filenames.begin(); it != filenames.end(); ++it)
        {
            *it = filenames[0] + "\\" + *it;
        }
        filenames.erase(filenames.begin());
    }

    DEBUG("Filenames translated to:");
    for (std::vector<std::string>::const_iterator it = filenames.begin(); it != filenames.end(); ++it)
    {
        DEBUG("- '" << *it << "'");
    }

    GpxTool::ReadGpxFiles(filenames);

}


int Gui::MainLoop()
{
    assert(_instance != 0);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT Gui::OnCommand(const UINT &UNUSED(uMsg), const WPARAM &wParam, const LPARAM &UNUSED(lParam))
{
    switch (LOWORD(wParam))
    {
        case ID_FILE_OPEN:
            DoOpenGpx();
            break;
        case ID_FILE_EXIT:
            PostMessage(_hWnd, WM_CLOSE, 0, 0);
            break;
        case ID_HELP_ABOUT:
        {
            int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), _hWnd, AboutDlgProc);
            if(ret == IDOK){
                MessageBox(_hWnd, L"Dialog exited with IDOK.", L"Notice", MB_OK | MB_ICONINFORMATION);
            }
            else if(ret == IDCANCEL){
                MessageBox(_hWnd, L"Dialog exited with IDCANCEL.", L"Notice", MB_OK | MB_ICONINFORMATION);
            }
            else if(ret == -1){
                MessageBox(_hWnd, L"Dialog failed!", L"Error", MB_OK | MB_ICONINFORMATION);
            }
        }
        break;
        default:
            DEBUG("Unhandled command " << LOWORD(wParam));
    }

    return 0;
}

LRESULT Gui::OnPaint(const UINT &UNUSED(uMsg), const WPARAM &UNUSED(wParam), const LPARAM &UNUSED(lParam))
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    hdc = BeginPaint(_hWnd, &ps);
    ::GetClientRect(_hWnd, &rect);
    DrawText(hdc,
            TEXT("Hello, Windows!"),
            -1, &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ::EndPaint(_hWnd, &ps);

    return 0;
}

LRESULT Gui::OnSize(const UINT &UNUSED(uMsg), const WPARAM &UNUSED(wParam), const LPARAM &UNUSED(lParam))
{
    SendMessage(_statusBar, WM_SIZE, 0, 0);

    RECT rcClient, rcStatus;
    GetClientRect(_hWnd, &rcClient);
    GetWindowRect(_statusBar, &rcStatus);

    return 0;
}


INT_PTR CALLBACK Gui::AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM UNUSED(lParam))
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
            }
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

Gui::Gui(const HINSTANCE &hInst, const int &iCmdShow) :
    Window(hInst),
    _statusBar(0)
{
    this->Create(L"GPX tool", iCmdShow);

    RECT clientRect;
    GetClientRect(_hWnd, &clientRect);

    _statusBar = CreateWindowEx(0,
            STATUSCLASSNAME,
            L"",
            WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
            0,
            clientRect.bottom - clientRect.top - 20,
            clientRect.right - clientRect.left,
            20,
            _hWnd,
            NULL,
            hInst,
            NULL);
}
