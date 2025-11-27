/***********************************************
*	File name:		plat_common.c
*	Description:	c source file for platform common
*	Author:			cai <sybstudy@yeah.net>
*	Version:		v1.0, 27Nov25, create file
************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/prctl.h>
#include <pthread.h>
#include "plat_common.h"

PRIVATE pthread_mutex_t dbg_printf_mtx = PTHREAD_MUTEX_INITIALIZER;
#define DBG_LOCK    pthread_mutex_lock(&dbg_printf_mtx);
#define DBG_UNLOCK  pthread_mutex_unlock(&dbg_printf_mtx);

/*
*   Function name:  plat_debug_printf
*   Function:       debug printf
*   Param in:       level   - debug level
*                   file    - file string
*                   line    - line in file
*                   fmt     - format
*                   ...     - args in fmt
*   Param out:      
*   Return:         void
*/
void plat_debug_printf(IN debug_level_e level, IN const char *file, IN int line, IN const char *fmt, ...)
{
    va_list list;
    // sys_time, process_name, file, line, fmt
    const char* fmt_front = NULL;
    time_t timep = 0;
    struct tm _sysTm = {};
    struct tm *p_tm = NULL;
    char sys_time[DBG_MAX_LEN] = {};
    char tname[DBG_MAX_LEN] = {};
    char dbg_fmt[DBG_MAX_LEN] = {};

    plat_ensure_ret_void(level > DBG_LEVEL_START && level < DBG_LEVEL_END);

    switch(level)
    {
        case DBG_LEVEL_NORMAL:
            fmt_front = "%s[<%s>:<%s:%d>] %s\r\n";
            break;
        case DBG_LEVEL_MAJOR:
            fmt_front = "\033[33;49m%s[<%s>:<%s:%d>] %s\033[0m\r\n";
            break;
        case DBG_LEVEL_ERROR:
            fmt_front = "\033[31;49m%s[<%s>:<%s:%d>] %s\033[0m\r\n";
            break;
        default:
            break;
    }

    timep = time(NULL);
    localtime_r(&timep, &_sysTm);
    p_tm = (struct tm *)&_sysTm;
    if(p_tm)
    {
        snprintf(sys_time, "%02d-%02d %02d:%02d:%02d", (p_tm->tm_mon + 1), p_tm->tm_mday, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);
    }

    prctl(PR_GET_NAME, tname);

    va_start(list, fmt);
    snprintf(dbg_fmt, DBG_MAX_LEN, fmt_front, sys_time, tname, file, line, fmt);
    DBG_LOCK;                   // 非线程安全，需要加锁
    vprintf(dbg_fmt, list);     // 输出到终端
    DBG_UNLOCK;
    va_end(list);

    return;
}