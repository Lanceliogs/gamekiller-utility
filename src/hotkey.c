#include "hotkey.h"

#define HOTKEY_ID  1
#define HOTKEY_MODS (MOD_CONTROL | MOD_ALT)
#define HOTKEY_VK VK_F12

BOOL hotkey_register(HWND hwnd)
{
    (void)hwnd;
    return TRUE;
}

void hotkey_unregister(HWND hwnd)
{
    (void)hwnd;
}

int hotkey_poll(HWND hwnd)
{
    (void)hwnd;
    return 0;
}