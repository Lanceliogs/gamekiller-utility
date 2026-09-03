#ifndef GK_SETTINGS_H
#define GK_SETTINGS_H

typedef struct {
    int enable_hotkey;
    int enable_sfx;
} gk_app_setings_t;

void gk_settings_init(gk_app_setings_t *settings);
int gk_settings_show_dialog(gk_app_setings_t *settings);

#endif