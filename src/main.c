#include "app.h"
#include "proc.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("*\\o/* GAMEKILLER.exe *\\o/*\n");
    printf("-\n");
    printf("A hotkey-triggered bullet to snipe frozen fullscreen games\n");
    printf("Ctrl+Alt+F12 will send a kill order to the current foreground application.\n");
    printf("-\n");
    printf("It is like Alt+F4, but stronger. It will start by sending a WM_CLOSE message\n");
    printf("to the foreground window. If it is not frozen, it might receive the message\n");
    printf("and close.\n");
    printf("-\n");
    printf("If it does not close, then we terminate the process directly.\n");
    printf("-\n");
    printf("Ctrl+C in this console will interrupt the program.\n");
    printf("----------\n");

    int rc = gk_app_init();
    if (rc != 0)
        return rc;
    rc = gk_app_run();
    gk_app_free();
    return rc;
}
