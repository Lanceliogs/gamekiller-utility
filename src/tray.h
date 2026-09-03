#ifndef GAMEKILLER_TRAY_H
#define GAMEKILLER_TRAY_H

#include "resources.h"
#include <windows.h>


#define GK_WM_TRAYICON (WM_APP + 1)

#define GK_IDM_SETTINGS 1
#define GK_IDM_EXIT 2

BOOL gk_tray_init(HWND hwnd);
void gk_tray_free(void);
void gk_tray_show_menu(HWND hwnd);

#endif