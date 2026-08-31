#ifndef GAMEKILLER_PROC_H
#define GAMEKILLER_PROC_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/* PID and HWND stuff */
DWORD proc_get_pid();
DWORD proc_get_foreground_pid(HWND *out_hwnd);

/* Basic process exists utility */
BOOL proc_exists(HANDLE process);

/* WM_CLOSE message and terminate */
int proc_gracefully_close(HWND h, DWORD pid);
int proc_terminate_process(int pid);

#endif