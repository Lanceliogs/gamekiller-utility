#include "proc.h"

#define PROC_POLL_INTERVAL_MS 50
#define PROC_GRACEFUL_CLOSE_TIMEOUT_MS 1500

DWORD proc_get_pid()
{
    return GetCurrentProcessId();
}

DWORD proc_get_foreground_pid(HWND *out_hwnd)
{
    HWND hwnd;
    DWORD pid = 0;
    hwnd = GetForegroundWindow();
    if (!hwnd)
        return 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (out_hwnd)
        *out_hwnd = hwnd;
    return pid;
}

BOOL proc_exists(HANDLE process)
{
    DWORD exit_code;
    if (!GetExitCodeProcess(process, &exit_code))
        return FALSE;
    return exit_code == STILL_ACTIVE;
}

int proc_gracefully_close(HWND h, DWORD pid)
{
    BOOL success = PostMessage(h, WM_CLOSE, 0, 0);
    if (!success)
        return -1;

    HANDLE hdl = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION, 0, pid);
    int elapsed = 0;
    int rc = -2;
    while (elapsed < PROC_GRACEFUL_CLOSE_TIMEOUT_MS)
    {
        if (!proc_exists(hdl))
        {
            rc = 0;
            break;
        }
        Sleep(PROC_POLL_INTERVAL_MS);
        elapsed += PROC_POLL_INTERVAL_MS;
    }
    CloseHandle(hdl);
    return rc;
}

int proc_terminate_process(int pid)
{
    HANDLE h = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION, 0, pid);
    BOOL success = TerminateProcess(h, 0);
    CloseHandle(h);
    if (!success)
        return -1;
    return 0; 
}