#ifndef GAMEKILLER_TRAY_H
#define GAMEKILLER_TRAY_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL tray_init(HWND hwnd, HINSTANCE instance);
void tray_remove(void);
void tray_show_menu(HWND hwnd);

#endif