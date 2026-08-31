#ifndef GAMEKILLER_HOTKEY_H
#define GAMEKILLER_HOTKEY_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL hotkey_register(HWND hwnd);
void hotkey_unregister(HWND hwnd);

int hotkey_poll(HWND hwnd);

#endif