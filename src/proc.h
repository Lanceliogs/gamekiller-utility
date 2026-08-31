#ifndef GAMEKILLER_PROC_H
#define GAMEKILLER_PROC_H

#include <windows.h>

/* PID and HWND stuff */
DWORD gk_proc_get_pid(void);
DWORD gk_proc_get_foreground_pid(HWND *out_hwnd);

/* Basic process exists utility */
BOOL gk_proc_exists(HANDLE process);

/* WM_CLOSE message and terminate */
int gk_proc_gracefully_close(HWND h, DWORD pid);
int gk_proc_terminate_process(int pid);

#endif