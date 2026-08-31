#include "hotkey.h"

#define HOTKEY_ID  1
#define HOTKEY_MODS (MOD_CONTROL | MOD_ALT)
#define HOTKEY_VK VK_F12

BOOL hotkey_register(HWND hwnd)
{
    return RegisterHotKey(hwnd, HOTKEY_ID, HOTKEY_MODS, HOTKEY_VK);
}

void hotkey_unregister(HWND hwnd)
{
    UnregisterHotKey(hwnd, HOTKEY_ID);
}
