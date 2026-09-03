#include "settings.h"

void gk_settings_init(gk_app_setings_t *settings)
{
    settings->enable_hotkey = 1;
    settings->enable_sfx = 1;
}

int gk_settings_show_dialog(gk_app_setings_t *settings)
{
    (void)settings;
    return 0;
}