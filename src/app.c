#include "app.h"
#include "proc.h"
#include "hotkey.h"
#include "tray.h"
#include "log.h"

#include <stdio.h>

// Virtual window handle so we can receive hotkey messages
static HWND s_hwnd = NULL;

static void s_close_foreground_proc(void)
{
    HWND hwnd;

    DWORD self_pid = proc_get_pid();
    DWORD pid = proc_get_foreground_pid(&hwnd);

    if (self_pid == pid)
    {
        printf("The app should not kill itself. Aborted!\n");
        return;
    }

    if (proc_gracefully_close(hwnd, pid) == 0)
    {
        printf("The window (PID=%ld) was gracefully closed!\n", pid);
        return;
    }
    
    printf("The window (PID=%ld) was not gracefully closed. Using lethal force now.", pid);
    if (proc_terminate_process(pid))
    {
        printf("Kill confirmed (PID=%ld)\n", pid);
        return;
    }

    printf("The target window (PID=%ld) cannot be killed.", pid);
    log_print_last_error();
}

// Window messages callback function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_HOTKEY: {
            int hotkeyId = (int)wParam;
            printf("Hotkey pressed! ID: %d\n", hotkeyId);
            
            if (hotkeyId == 1) {
                printf("[Ctrl+Alt+F12] Kill order received. Trying to close the foreground process...\n");
                s_close_foreground_proc();
            }
            return 0;
        }
        case WM_DESTROY:
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static int s_create_virtual_window(void)
{
    if (s_hwnd != NULL) {
        printf("Window was already created");
        return 1;
    }

    const char *CLASS_NAME = "HotkeyMessageOnlyWindow";

    // 2. Register the Window Class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        printf("Failed to register window class.");
        return 2;
    }

    // 3. Create the Message-Only Window
    s_hwnd = CreateWindow(
        CLASS_NAME,             // Window class
        "GameKillerWindow",    // Window text
        0,                      // Window style (not applicable for message-only)
        0, 0, 0, 0,             // Size and position (ignored)
        HWND_MESSAGE,           // MAGIC HAPPENS HERE: Makes it a message-only window
        NULL,                   // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL                    // Additional application data
    );

    if (s_hwnd == NULL) {
        printf("Failed to create message-only window.");
        return 3;
    }

    return 0;
}

void s_destroy_virtual_window(void)
{
    DestroyWindow(s_hwnd);
    s_hwnd = NULL;
}

int app_init(void)
{
    if (s_create_virtual_window() != 0)
        return -1;
    if (!hotkey_register(s_hwnd))
        return -2;
    return 0;
}

int app_run(void)
{
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void app_free(void)
{
    hotkey_unregister(s_hwnd);
    s_destroy_virtual_window();
}

