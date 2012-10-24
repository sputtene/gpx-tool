/***
 * Generated with the following command:
 *      cat /usr/i686-w64-mingw32/include/winuser.h \
 *          | sed -n -e 's/^[^ ]* \([^ ]*\) \([^ ]*\)/\2 \1/' -e '/ WM_/p' \
 *          | sed -e 's/\([^ ]*\) \([^ ]*\)/wm_lookup\[\1\] = "\2";/' \
 *          > wm_lookup.h
 ***/

#ifndef INC_WM_LOOKUP_H
#define INC_WM_LOOKUP_H


#include <map>
#include <string>

static std::string _WM_LOOKUP(unsigned int msg)
{
    static std::map<unsigned int, std::string> lookup = std::map<unsigned int, std::string>();

    if (!lookup.count(0))
    {
        lookup[0x0000] = "WM_NULL";
        lookup[0x0001] = "WM_CREATE";
        lookup[0x0002] = "WM_DESTROY";
        lookup[0x0003] = "WM_MOVE";
        lookup[0x0005] = "WM_SIZE";
        lookup[0x0006] = "WM_ACTIVATE";
        lookup[0x0007] = "WM_SETFOCUS";
        lookup[0x0008] = "WM_KILLFOCUS";
        lookup[0x000A] = "WM_ENABLE";
        lookup[0x000B] = "WM_SETREDRAW";
        lookup[0x000C] = "WM_SETTEXT";
        lookup[0x000D] = "WM_GETTEXT";
        lookup[0x000E] = "WM_GETTEXTLENGTH";
        lookup[0x000F] = "WM_PAINT";
        lookup[0x0010] = "WM_CLOSE";
        lookup[0x0011] = "WM_QUERYENDSESSION";
        lookup[0x0013] = "WM_QUERYOPEN";
        lookup[0x0016] = "WM_ENDSESSION";
        lookup[0x0012] = "WM_QUIT";
        lookup[0x0014] = "WM_ERASEBKGND";
        lookup[0x0015] = "WM_SYSCOLORCHANGE";
        lookup[0x0018] = "WM_SHOWWINDOW";
        lookup[0x001A] = "WM_WININICHANGE";
        //lookup[WM_WININICHANGE] = "WM_SETTINGCHANGE";
        lookup[0x001B] = "WM_DEVMODECHANGE";
        lookup[0x001C] = "WM_ACTIVATEAPP";
        lookup[0x001D] = "WM_FONTCHANGE";
        lookup[0x001E] = "WM_TIMECHANGE";
        lookup[0x001F] = "WM_CANCELMODE";
        lookup[0x0020] = "WM_SETCURSOR";
        lookup[0x0021] = "WM_MOUSEACTIVATE";
        lookup[0x0022] = "WM_CHILDACTIVATE";
        lookup[0x0023] = "WM_QUEUESYNC";
        lookup[0x0024] = "WM_GETMINMAXINFO";
        lookup[0x0026] = "WM_PAINTICON";
        lookup[0x0027] = "WM_ICONERASEBKGND";
        lookup[0x0028] = "WM_NEXTDLGCTL";
        lookup[0x002A] = "WM_SPOOLERSTATUS";
        lookup[0x002B] = "WM_DRAWITEM";
        lookup[0x002C] = "WM_MEASUREITEM";
        lookup[0x002D] = "WM_DELETEITEM";
        lookup[0x002E] = "WM_VKEYTOITEM";
        lookup[0x002F] = "WM_CHARTOITEM";
        lookup[0x0030] = "WM_SETFONT";
        lookup[0x0031] = "WM_GETFONT";
        lookup[0x0032] = "WM_SETHOTKEY";
        lookup[0x0033] = "WM_GETHOTKEY";
        lookup[0x0037] = "WM_QUERYDRAGICON";
        lookup[0x0039] = "WM_COMPAREITEM";
        lookup[0x003D] = "WM_GETOBJECT";
        lookup[0x0041] = "WM_COMPACTING";
        lookup[0x0044] = "WM_COMMNOTIFY";
        lookup[0x0046] = "WM_WINDOWPOSCHANGING";
        lookup[0x0047] = "WM_WINDOWPOSCHANGED";
        lookup[0x0048] = "WM_POWER";
        lookup[0x004A] = "WM_COPYDATA";
        lookup[0x004B] = "WM_CANCELJOURNAL";
        lookup[0x004E] = "WM_NOTIFY";
        lookup[0x0050] = "WM_INPUTLANGCHANGEREQUEST";
        lookup[0x0051] = "WM_INPUTLANGCHANGE";
        lookup[0x0052] = "WM_TCARD";
        lookup[0x0053] = "WM_HELP";
        lookup[0x0054] = "WM_USERCHANGED";
        lookup[0x0055] = "WM_NOTIFYFORMAT";
        lookup[0x007B] = "WM_CONTEXTMENU";
        lookup[0x007C] = "WM_STYLECHANGING";
        lookup[0x007D] = "WM_STYLECHANGED";
        lookup[0x007E] = "WM_DISPLAYCHANGE";
        lookup[0x007F] = "WM_GETICON";
        lookup[0x0080] = "WM_SETICON";
        lookup[0x0081] = "WM_NCCREATE";
        lookup[0x0082] = "WM_NCDESTROY";
        lookup[0x0083] = "WM_NCCALCSIZE";
        lookup[0x0084] = "WM_NCHITTEST";
        lookup[0x0085] = "WM_NCPAINT";
        lookup[0x0086] = "WM_NCACTIVATE";
        lookup[0x0087] = "WM_GETDLGCODE";
        lookup[0x0088] = "WM_SYNCPAINT";
        lookup[0x00A0] = "WM_NCMOUSEMOVE";
        lookup[0x00A1] = "WM_NCLBUTTONDOWN";
        lookup[0x00A2] = "WM_NCLBUTTONUP";
        lookup[0x00A3] = "WM_NCLBUTTONDBLCLK";
        lookup[0x00A4] = "WM_NCRBUTTONDOWN";
        lookup[0x00A5] = "WM_NCRBUTTONUP";
        lookup[0x00A6] = "WM_NCRBUTTONDBLCLK";
        lookup[0x00A7] = "WM_NCMBUTTONDOWN";
        lookup[0x00A8] = "WM_NCMBUTTONUP";
        lookup[0x00A9] = "WM_NCMBUTTONDBLCLK";
        lookup[0x00AB] = "WM_NCXBUTTONDOWN";
        lookup[0x00AC] = "WM_NCXBUTTONUP";
        lookup[0x00AD] = "WM_NCXBUTTONDBLCLK";
        lookup[0x00FF] = "WM_INPUT";
        lookup[0x0100] = "WM_KEYFIRST";
        lookup[0x0100] = "WM_KEYDOWN";
        lookup[0x0101] = "WM_KEYUP";
        lookup[0x0102] = "WM_CHAR";
        lookup[0x0103] = "WM_DEADCHAR";
        lookup[0x0104] = "WM_SYSKEYDOWN";
        lookup[0x0105] = "WM_SYSKEYUP";
        lookup[0x0106] = "WM_SYSCHAR";
        lookup[0x0107] = "WM_SYSDEADCHAR";
        lookup[0x0109] = "WM_UNICHAR";
        lookup[0x0109] = "WM_KEYLAST";
        lookup[0x010D] = "WM_IME_STARTCOMPOSITION";
        lookup[0x010E] = "WM_IME_ENDCOMPOSITION";
        lookup[0x010F] = "WM_IME_COMPOSITION";
        lookup[0x010F] = "WM_IME_KEYLAST";
        lookup[0x0110] = "WM_INITDIALOG";
        lookup[0x0111] = "WM_COMMAND";
        lookup[0x0112] = "WM_SYSCOMMAND";
        lookup[0x0113] = "WM_TIMER";
        lookup[0x0114] = "WM_HSCROLL";
        lookup[0x0115] = "WM_VSCROLL";
        lookup[0x0116] = "WM_INITMENU";
        lookup[0x0117] = "WM_INITMENUPOPUP";
        lookup[0x011F] = "WM_MENUSELECT";
        lookup[0x0119] = "WM_GESTURE";
        lookup[0x011A] = "WM_GESTURENOTIFY";
        lookup[0x0120] = "WM_MENUCHAR";
        lookup[0x0121] = "WM_ENTERIDLE";
        lookup[0x0122] = "WM_MENURBUTTONUP";
        lookup[0x0123] = "WM_MENUDRAG";
        lookup[0x0124] = "WM_MENUGETOBJECT";
        lookup[0x0125] = "WM_UNINITMENUPOPUP";
        lookup[0x0126] = "WM_MENUCOMMAND";
        lookup[0x0127] = "WM_CHANGEUISTATE";
        lookup[0x0128] = "WM_UPDATEUISTATE";
        lookup[0x0129] = "WM_QUERYUISTATE";
        lookup[0x0132] = "WM_CTLCOLORMSGBOX";
        lookup[0x0133] = "WM_CTLCOLOREDIT";
        lookup[0x0134] = "WM_CTLCOLORLISTBOX";
        lookup[0x0135] = "WM_CTLCOLORBTN";
        lookup[0x0136] = "WM_CTLCOLORDLG";
        lookup[0x0137] = "WM_CTLCOLORSCROLLBAR";
        lookup[0x0138] = "WM_CTLCOLORSTATIC";
        lookup[0x0200] = "WM_MOUSEFIRST";
        lookup[0x0200] = "WM_MOUSEMOVE";
        lookup[0x0201] = "WM_LBUTTONDOWN";
        lookup[0x0202] = "WM_LBUTTONUP";
        lookup[0x0203] = "WM_LBUTTONDBLCLK";
        lookup[0x0204] = "WM_RBUTTONDOWN";
        lookup[0x0205] = "WM_RBUTTONUP";
        lookup[0x0206] = "WM_RBUTTONDBLCLK";
        lookup[0x0207] = "WM_MBUTTONDOWN";
        lookup[0x0208] = "WM_MBUTTONUP";
        lookup[0x0209] = "WM_MBUTTONDBLCLK";
        lookup[0x020A] = "WM_MOUSEWHEEL";
        lookup[0x020B] = "WM_XBUTTONDOWN";
        lookup[0x020C] = "WM_XBUTTONUP";
        lookup[0x020D] = "WM_XBUTTONDBLCLK";
        lookup[0x020D] = "WM_MOUSELAST";
        lookup[0x020E] = "WM_MOUSEHWHEEL";
        lookup[0x0210] = "WM_PARENTNOTIFY";
        lookup[0x0211] = "WM_ENTERMENULOOP";
        lookup[0x0212] = "WM_EXITMENULOOP";
        lookup[0x0213] = "WM_NEXTMENU";
        lookup[0x0214] = "WM_SIZING";
        lookup[0x0215] = "WM_CAPTURECHANGED";
        lookup[0x0216] = "WM_MOVING";
        lookup[0x0218] = "WM_POWERBROADCAST";
        lookup[0x0219] = "WM_DEVICECHANGE";
        lookup[0x0220] = "WM_MDICREATE";
        lookup[0x0221] = "WM_MDIDESTROY";
        lookup[0x0222] = "WM_MDIACTIVATE";
        lookup[0x0223] = "WM_MDIRESTORE";
        lookup[0x0224] = "WM_MDINEXT";
        lookup[0x0225] = "WM_MDIMAXIMIZE";
        lookup[0x0226] = "WM_MDITILE";
        lookup[0x0227] = "WM_MDICASCADE";
        lookup[0x0228] = "WM_MDIICONARRANGE";
        lookup[0x0229] = "WM_MDIGETACTIVE";
        lookup[0x0230] = "WM_MDISETMENU";
        lookup[0x0231] = "WM_ENTERSIZEMOVE";
        lookup[0x0232] = "WM_EXITSIZEMOVE";
        lookup[0x0233] = "WM_DROPFILES";
        lookup[0x0234] = "WM_MDIREFRESHMENU";
        lookup[0x0281] = "WM_IME_SETCONTEXT";
        lookup[0x0282] = "WM_IME_NOTIFY";
        lookup[0x0283] = "WM_IME_CONTROL";
        lookup[0x0284] = "WM_IME_COMPOSITIONFULL";
        lookup[0x0285] = "WM_IME_SELECT";
        lookup[0x0286] = "WM_IME_CHAR";
        lookup[0x0288] = "WM_IME_REQUEST";
        lookup[0x0290] = "WM_IME_KEYDOWN";
        lookup[0x0291] = "WM_IME_KEYUP";
        lookup[0x02A1] = "WM_MOUSEHOVER";
        lookup[0x02A3] = "WM_MOUSELEAVE";
        lookup[0x02A0] = "WM_NCMOUSEHOVER";
        lookup[0x02A2] = "WM_NCMOUSELEAVE";
        lookup[0x02B1] = "WM_WTSSESSION_CHANGE";
        lookup[0x02c0] = "WM_TABLET_FIRST";
        lookup[0x02df] = "WM_TABLET_LAST";
        lookup[0x0300] = "WM_CUT";
        lookup[0x0301] = "WM_COPY";
        lookup[0x0302] = "WM_PASTE";
        lookup[0x0303] = "WM_CLEAR";
        lookup[0x0304] = "WM_UNDO";
        lookup[0x0305] = "WM_RENDERFORMAT";
        lookup[0x0306] = "WM_RENDERALLFORMATS";
        lookup[0x0307] = "WM_DESTROYCLIPBOARD";
        lookup[0x0308] = "WM_DRAWCLIPBOARD";
        lookup[0x0309] = "WM_PAINTCLIPBOARD";
        lookup[0x030A] = "WM_VSCROLLCLIPBOARD";
        lookup[0x030B] = "WM_SIZECLIPBOARD";
        lookup[0x030C] = "WM_ASKCBFORMATNAME";
        lookup[0x030D] = "WM_CHANGECBCHAIN";
        lookup[0x030E] = "WM_HSCROLLCLIPBOARD";
        lookup[0x030F] = "WM_QUERYNEWPALETTE";
        lookup[0x0310] = "WM_PALETTEISCHANGING";
        lookup[0x0311] = "WM_PALETTECHANGED";
        lookup[0x0312] = "WM_HOTKEY";
        lookup[0x0317] = "WM_PRINT";
        lookup[0x0318] = "WM_PRINTCLIENT";
        lookup[0x0319] = "WM_APPCOMMAND";
        lookup[0x031A] = "WM_THEMECHANGED";
        lookup[0x0358] = "WM_HANDHELDFIRST";
        lookup[0x035F] = "WM_HANDHELDLAST";
        lookup[0x0360] = "WM_AFXFIRST";
        lookup[0x037F] = "WM_AFXLAST";
        lookup[0x0380] = "WM_PENWINFIRST";
        lookup[0x038F] = "WM_PENWINLAST";
        lookup[0x8000] = "WM_APP";
        lookup[0x0400] = "WM_USER";
        lookup[576] = "WM_TOUCHMOVE";
        lookup[577] = "WM_TOUCHDOWN";
        lookup[578] = "WM_TOUCHUP";
    }

    return lookup[msg];
}

#endif  // INC_WM_LOOKUP_H
