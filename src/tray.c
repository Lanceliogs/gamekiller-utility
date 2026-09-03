#include "resources.h"
#include "tray.h"
#include "log.h"

#include <shellapi.h>

#define TRAY_ICON_ID 1

static NOTIFYICONDATA s_nid = {0};

BOOL gk_tray_init(HWND hwnd)
{
    HICON hicon = LoadIcon(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_ICON_GK)
    );

    s_nid.cbSize = sizeof(s_nid);
    s_nid.hWnd = hwnd;
    s_nid.uID = TRAY_ICON_ID;
    s_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    s_nid.uCallbackMessage = GK_WM_TRAYICON;
    s_nid.hIcon = hicon;
    strcpy(s_nid.szTip, "GameKiller");

    if (Shell_NotifyIcon(NIM_ADD, &s_nid))
        return TRUE;
    
    gk_log_error("Could not init shell notify icon");
    gk_log_last_error();
    return FALSE;
}

void gk_tray_free(void)
{
    Shell_NotifyIcon(NIM_DELETE, &s_nid);
    memset(&s_nid, 0, sizeof(s_nid));
}

void gk_tray_show_menu(HWND hwnd)
{
    (void)hwnd;
    HMENU menu = CreatePopupMenu();
    AppendMenu(
        menu,
        MF_STRING,
        GK_IDM_VERSION,
        "GameKiller - v0.1"
    );
    AppendMenu(
        menu,
        MF_STRING,
        GK_IDM_EXIT,
        "Exit"
    );

    POINT point;
    GetCursorPos(&point);
    SetForegroundWindow(hwnd);
    TrackPopupMenu(menu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
}