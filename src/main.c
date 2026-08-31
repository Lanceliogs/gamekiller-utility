#include "app.h"
#include "proc.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("GameKiller.exe\n");
    printf("-\n");
    printf("A hotkey-triggered bullet to snipe frozen fullscreen games\n");
    printf("Ctrl+Alt+F12 will send a kill order to the current foreground application.\n");
    printf("It is like Alt+F4, but stronger!\n");

    int rc = gk_app_init();
    if (rc != 0)
        return rc;
    rc = gk_app_run();
    gk_app_free();
    return rc;
}
