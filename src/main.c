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
    printf("\n\n");
    DWORD self_pid = proc_get_pid();
    printf("SELF PID: %ld\n", self_pid);

    HWND h;
    DWORD fg_pid = proc_get_foreground_pid(&h);
    printf("FOREGROUND PID: %ld\n", fg_pid);

    return 0;
}
