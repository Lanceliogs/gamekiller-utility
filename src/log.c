#include "log.h"

#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

static gk_log_level_t s_current_level = GK_LOG_INFO;

static const char* s_log_silent_str = "SILENT";
static const char* s_log_debug_str = "DEBUG";
static const char* s_log_info_str = "INFO";
static const char* s_log_warn_str = "WARN";
static const char* s_log_error_str = "ERROR";

void gk_log_init(gk_log_level_t level)
{
    s_current_level = level;
}

void gk_log_set_level(gk_log_level_t level)
{
    s_current_level = level;
}

gk_log_level_t gk_log_get_level(void)
{
    return s_current_level;
}

int gk_log_level_from_string(const char *str, gk_log_level_t *out)
{
    if (strcasecmp(str, s_log_silent_str) == 0)
    {
        *out = GK_LOG_SILENT;
        return 0;     
    }
    if (strcasecmp(str, s_log_debug_str) == 0)
    {
        *out = GK_LOG_DEBUG;
        return 0;     
    }
    if (strcasecmp(str, s_log_info_str) == 0)
    {
        *out = GK_LOG_INFO;
        return 0;     
    }
    if (strcasecmp(str, s_log_warn_str) == 0)
    {
        *out = GK_LOG_WARN;
        return 0;     
    }
    if (strcasecmp(str, s_log_error_str) == 0)
    {
        *out = GK_LOG_ERROR;
        return 0;     
    }
    return -1;
}

const char *gk_log_level_to_string(gk_log_level_t level)
{
    switch (level)
    {
        case GK_LOG_SILENT: return s_log_silent_str;
        case GK_LOG_DEBUG: return s_log_debug_str;
        case GK_LOG_INFO: return s_log_info_str;
        case GK_LOG_WARN: return s_log_warn_str;
        case GK_LOG_ERROR: return s_log_error_str;
        default: return "UNKNOWN";
    }
}

void gk_log_write(gk_log_level_t level, const char *fmt, ...)
{
    if (s_current_level == GK_LOG_SILENT || level < s_current_level)
        return;
    fprintf(stderr, "[%s] ", gk_log_level_to_string(level));
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void gk_log_last_error(void)
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
        gk_log_error("Windows error %lu\n", (unsigned long)error);
        return;
    }

    gk_log_error("%s (code %lu)\n", buffer, (unsigned long)error);
}