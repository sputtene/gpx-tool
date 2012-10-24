#ifndef INC_GUI_H
#define INC_GUI_H

#include <windows.h>
#include "../UserInterface.h"
#include "Window.h"

class Gui : public UserInterface, public Window
{
public:
    // Methods for this user interface
    static bool Setup(const HINSTANCE &hInst, const int &iCmdShow);
    static void Cleanup();

    // Implementation of UserInterface interface
    int MainLoop();

    // Commands
    void DoOpenGpx();


    // Singleton implementation
    static Gui* Instance() { return _instance; }

protected:
    // Window message handlers
    virtual LRESULT OnCommand(const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam);
    virtual LRESULT OnPaint(const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam);
    virtual LRESULT OnSize(const UINT &uMsg, const WPARAM &wParam, const LPARAM &lParam);


private:
    // Window data
    HWND _statusBar;


    // Implementation methods
    static BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    // Singleton implementation
    static Gui *_instance;

    Gui(const HINSTANCE &hInst, const int &iCmdShow);
};

#endif  // INC_GUI_H
