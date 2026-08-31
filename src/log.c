#include "log.h"

#include <windows.h>
#include <stdio.h>

void log_print_last_error(void)
{
    DWORD error = GetLastError();
    char buffer[256];
    DWORD len = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, error, 0,
        buffer, sizeof(buffer), NULL
    );

    if (len == 0)
    {
        printf("[ERROR] Windows error %lu\n", (unsigned long)error);
        return;
    }
    printf("[ERROR] %s (code %lu)\n", buffer, (unsigned long)error);
}
