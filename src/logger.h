/**
 * @file log.h
 * @brief Logger header
 * @author Lorenz C.
 *
 * This logging library provides a simple logging interface with different verbosity levels.
 * Each tag can have its own log level.
 * Only messages with a log level greater or equal to the log level of the tag and the global log level will be printed.
 */

#ifndef LOG_H
#define LOG_H

#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#if LOGGER_LEVEL_FATAL
#define LOGGER_LEVEL 5
#endif
#ifdef LOGGER_LEVEL_CRITICAL
#define LOGGER_LEVEL 4
#endif
#ifdef LOGGER_LEVEL_WARN
#define LOGGER_LEVEL 3
#endif
#ifdef LOGGER_LEVEL_INFO
#define LOGGER_LEVEL 2
#endif
#ifdef LOGGER_LEVEL_ALL
#define LOGGER_LEVEL 1
#endif

#ifdef LOGGER_USE_COLOR
#define LOGGER_COLOR 1
#endif

#ifndef LOGGER_LEVEL
#define LOGGER_LEVEL 3
#endif
#ifndef LOGGER_COLOR
#define LOGGER_COLOR 0
#endif

#define ANSI_ESC "\x1B"
#define ANSI_CSI "\x9B"
#define ANSI_DCS "\x90"
#define ANSI_OSC "\x9D"

#define CLEAR_SCREEN "\033c"

#define CURSOR_RESET ANSI_ESC "[H"
#define CURSOR_UP(n) ANSI_ESC "[" #n "A"
#define CURSOR_DOWN(n) ANSI_ESC "[" #n "B"
#define CURSOR_RIGHT(n) ANSI_ESC "[" #n "C"
#define CURSOR_LEFT(n) ANSI_ESC "[" #n "D"
#define CURSOR_NEXT_N_LINES(n) ANSI_ESC "[" #n "E"
#define CURSOR_PREV_N_LINES(n) ANSI_ESC "[" #n "F"
#define CURSOR_COL(n) ANSI_ESC "[" #n "G"
#define CURSOR_POS ANSI_ESC "[" #n ";" #n "H"
#define CURSOR_SAVE ANSI_ESC "7"
#define CURSOR_RESTORE ANSI_ESC "8"

#define ERASE_FROM_CURSOR_TO_END ANSI_ESC "[0J"
#define ERASE_FROM_CURSOR_TO_BEGINNING ANSI_ESC "[1J"
#define ERASE_ENTIRE_SCREEN ANSI_ESC "[2J"
#define ERASE_FROM_CURSOR_TO_END_LINE ANSI_ESC "[0K"
#define ERASE_FROM_CURSOR_TO_BEGINNING_LINE ANSI_ESC "[1K"
#define ERASE_ENTIRE_LINE ANSI_ESC "[2K"

#if LOGGER_COLOR == 1
#define LOG_RESET_COLOR "\033[0m"
#define LOG_COLOR_F     "\033[0;31m"    // Red
#define LOG_COLOR_C     "\033[0;31m"    // Red
#define LOG_COLOR_W     "\033[0;33m"    // Brown
#define LOG_COLOR_I     "\033[0;32m"    // Green
#define LOG_COLOR_D     LOG_RESET_COLOR // Default
#else
#define LOG_RESET_COLOR
#define LOG_COLOR_F
#define LOG_COLOR_C
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#endif

#if LOGGER_LEVEL <= 1
#define LOG_DEBUG(tag, fmt, ...) printf(LOG_COLOR_D"[Debug]    [%s]: " fmt LOG_RESET_COLOR, tag, ##__VA_ARGS__)
#else
#define LOG_DEBUG(tag, fmt, ...)
#endif
#if LOGGER_LEVEL <= 2
#define LOG_INFO(tag, fmt, ...)  printf(LOG_COLOR_I"[Info]     [%s]: " fmt LOG_RESET_COLOR, tag, ##__VA_ARGS__)
#else
#define LOG_INFO(tag, fmt, ...)
#endif
#if LOGGER_LEVEL <= 3
#define LOG_WARN(tag, fmt, ...)  printf(LOG_COLOR_W"[Warning]  [%s]: " fmt LOG_RESET_COLOR, tag, ##__VA_ARGS__)
#else
#define LOG_WARN(tag, fmt, ...)
#endif
#if LOGGER_LEVEL <= 4
#define LOG_CRIT(tag, fmt, ...)   printf(LOG_COLOR_C"[Critical] [%s]: " fmt LOG_RESET_COLOR, tag, ##__VA_ARGS__)
#else
#define LOG_CRIT(tag, fmt, ...)
#endif
#if LOGGER_LEVEL <= 4
#define LOG_FATAL(tag, fmt, ...)   printf(LOG_COLOR_F"[Fatal]    [%s]: " fmt LOG_RESET_COLOR, tag, ##__VA_ARGS__)
#else
#define LOG_FATAL(tag, fmt, ...)
#endif

#define LOGGER_INIT clock_t logger_start = clock();

/* For internal use only.
 * Use the LOG_* macros instead e.g., LOG_DEBUG(TAG, "Debug message");
 */
uint32_t logger_get_timestamp(clock_t* start);

#endif /* LOG_H */