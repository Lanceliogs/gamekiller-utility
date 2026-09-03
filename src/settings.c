#include "settings.h"
#include "resources.h"
#include "log.h"

static INT_PTR CALLBACK s_dialog_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    gk_settings_t *settings;

    switch (umsg)
    {
        case WM_INITDIALOG:
        {
            /* Store settings into user data for later messages */
            settings = (gk_settings_t *)lparam;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)settings);
            
            // Center dialog on screen
            RECT rc;
            GetWindowRect(hwnd, &rc);

            int width  = rc.right - rc.left;
            int height = rc.bottom - rc.top;

            int screen_width  = GetSystemMetrics(SM_CXSCREEN);
            int screen_height = GetSystemMetrics(SM_CYSCREEN);

            int x = (screen_width - width) / 2;
            int y = (screen_height - height) / 2;

            SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            /* Set checkboxes using settings */
            CheckDlgButton(hwnd, IDC_SOUND_FX, settings->enable_sfx ? BST_CHECKED : BST_UNCHECKED);
            CheckDlgButton(hwnd, IDC_HOTKEY, settings->enable_hotkey ? BST_CHECKED : BST_UNCHECKED);
            return TRUE;
        }

        case WM_COMMAND:
        {
            settings = (gk_settings_t *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            switch (LOWORD(wparam))
            {
                case IDC_CLOSE:
                {
                    settings->enable_sfx = IsDlgButtonChecked(hwnd, IDC_SOUND_FX) == BST_CHECKED;
                    settings->enable_hotkey = IsDlgButtonChecked(hwnd, IDC_HOTKEY) == BST_CHECKED;
                    EndDialog(hwnd, IDOK);
                    return TRUE;
                }
            }
            break;
        }

        case WM_CLOSE:
        {
            EndDialog(hwnd, IDCANCEL);
            return TRUE;
        }
    }
    return FALSE;
}


void gk_settings_init(gk_settings_t *settings)
{
    settings->enable_hotkey = 1;
    settings->enable_sfx = 1;
}


int gk_settings_show_dialog(HWND hwnd_parent, gk_settings_t *settings)
{
    gk_log_info("Opening settings dialog...");
    HINSTANCE instance = GetModuleHandle(NULL);
    INT_PTR result = DialogBoxParam(instance, MAKEINTRESOURCE(IDD_SETTINGS), hwnd_parent, s_dialog_proc, (LPARAM)settings);
    if (result == -1)
    {
        gk_log_error("Failed to create settings dialog");
        return -1;
    }
    return (int)result;
}