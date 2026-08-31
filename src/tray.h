#ifndef GAMEKILLER_TRAY_H
#define GAMEKILLER_TRAY_H

#include <windows.h>

BOOL gk_tray_init(HWND hwnd, HINSTANCE instance);
void gk_tray_remove(void);
void gk_tray_show_menu(HWND hwnd);

#endif