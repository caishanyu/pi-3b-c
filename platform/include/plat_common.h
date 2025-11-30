/***********************************************
*	File name:		common.h
*	Description:	c header file for sth common
*	Author:			cai <sybstudy@yeah.net>
*	Version:		v1.0, 27Nov25, create file
************************************************/

#ifndef __COMMON_H_
#define __COMMON_H_

#include <stdio.h>
#include <stdint.h>

#define IN          // 输入参数
#define OUT         // 输出参数
#define OPTIONAL    // 可选参数

#define PRIVATE static  // 私有

#ifndef likely
#define likely(x)   __builtin_expect(!!(x), 1)  // 用于分支语句，表示表达式x很可能成立
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)  // 用于分支语句，表示表达式x很可能不成立
#endif

typedef enum
{
    DBG_LEVEL_START = 0,

    DBG_LEVEL_NORMAL,
    DBG_LEVEL_MAJOR,
    DBG_LEVEL_ERROR,
    DBG_LEVEL_ALZ,

    DBG_LEVEL_END,
}debug_level_e;

// 调试相关
#define DBG_MAX_LEN     (128)

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
void plat_debug_printf(IN debug_level_e level, IN const char *file, IN int line, IN const char *fmt, ...);

#define DBG_ON
#ifdef DBG_ON
#define DBG(fmt, args...)       plat_debug_printf(DBG_LEVEL_NORMAL, __FILE__, __LINE__, fmt, ##args);
#define DBG_MAJ(fmt, args...)   plat_debug_printf(DBG_LEVEL_MAJOR, __FILE__, __LINE__, fmt, ##args);
#else
#define DBG(fmt, args...)
#define DBG_MAJ(fmt, args...)
#endif
#define DBG_ERR(fmt, args...)   plat_debug_printf(DBG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##args);
#define DBG_ALZ(fmt, args...)   plat_debug_printf(DBG_LEVEL_ALZ, __FILE__, __LINE__, fmt, ##args);

// 用于校验条件合法性，比如函数参数判断
// 检查x表达式是否成立，不成立则提示，不直接返回
#define plat_ensure(x)                  do{ \
    if(unlikely(!(x)))                      \
    {                                       \
        DBG_ERR("Ensure %s failed.", #x);   \
    }                                       \
}while(0);
// 检查x表达式是否成立，不成立则返回，用于返回值void的接口
#define plat_ensure_ret_void(x)         do{ \
    if(unlikely(!(x)))                      \
    {                                       \
        DBG_ERR("Ensure %s failed.", #x);   \
        return;                             \
    }                                       \
}while(0);
// 检查x表达式是否成立，不成立则返回val
#define plat_ensure_ret_val(x, val)     do{ \
    if(unlikely(!(x)))                      \
    {                                       \
        DBG_ERR("Ensure %s failed.", #x);   \
        return val;                         \
    }                                       \
}while(0);
// 检查x表达式是否成立，不成立则跳转到done
#define plat_ensure_done(x)             do{ \
    if(unlikely(!(x)))                      \
    {                                       \
        DBG_ERR("Ensure %s failed.", #x);   \
        goto done;                          \
    }                                       \
}while(0);

// 基本数据类型别名
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;

// 错误码汇总
typedef enum
{
    err_no_error = 0,       // ok
    err_bad_param,          // bad parameter
    err_no_memory,          // no memory

    err_unknown = 65535,    // unknown error
}error_code;

#endif
