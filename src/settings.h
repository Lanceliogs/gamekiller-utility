#ifndef GK_SETTINGS_H
#define GK_SETTINGS_H

#include <windows.h>

typedef struct {
    int enable_hotkey;
    int enable_sfx;
} gk_settings_t;

void gk_settings_init(gk_settings_t *settings);
int gk_settings_show_dialog(HWND hwnd_parent, gk_settings_t *settings);

#endif