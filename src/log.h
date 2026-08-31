/*
 * log.h - Level-based logging to stderr
 *
 * Simple logging with compile-time macros for each level.
 * Output goes to stderr so it doesn't interfere with stdout.
 * Set level to GK_LOG_SILENT to suppress all output (useful in tests).
 */

#ifndef GAMEKILLER_LOG_H
#define GAMEKILLER_LOG_H

typedef enum {
    GK_LOG_SILENT,
    GK_LOG_DEBUG,
    GK_LOG_INFO,
    GK_LOG_WARN,
    GK_LOG_ERROR,
} gk_log_level_t;

void gk_log_init(gk_log_level_t level);
void gk_log_set_level(gk_log_level_t level);
gk_log_level_t gk_log_get_level(void);

/* Returns -1 if the string is not recognized */
int gk_log_level_from_string(const char *str, gk_log_level_t *out);
const char *gk_log_level_to_string(gk_log_level_t level);

void gk_log_write(gk_log_level_t level, const char *fmt, ...);

#define gk_log_debug(...) gk_log_write(GK_LOG_DEBUG, __VA_ARGS__)
#define gk_log_info(...)  gk_log_write(GK_LOG_INFO,  __VA_ARGS__)
#define gk_log_warn(...)  gk_log_write(GK_LOG_WARN,  __VA_ARGS__)
#define gk_log_error(...) gk_log_write(GK_LOG_ERROR, __VA_ARGS__)

void gk_log_last_error(void);

#endif