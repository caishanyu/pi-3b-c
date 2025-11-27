/***********************************************
*	File name:		plat_alloc.h
*	Description:	c header file for alloc
*	Author:			cai <sybstudy@yeah.net>
*	Version:		v1.0, 27Nov25, create file
************************************************/

#include <pthread.h>
#include "plat_common.h"

typedef struct plat_mem_pool_s
{
    pthread_mutex_t mutex;      // 互斥锁，保护并发操作该内存池

    void *memory;               // 内存池起始
    size_t block_size;          // 每个内存块的大小
    size_t block_nums;          // 内存块的数量
    size_t block_used;          // 已使用的内存块数量
    void **free_list;           // 空闲块链表头
}plat_mem_pool_t;

/*
*   Function name:  plat_mem_pool_create
*   Function:       create a memory pool
*   Param in:       size    - total size of pool, Bytes
*   Param out:
*   Return:         pointer to memory pool; NULL -- create fail
*/
plat_mem_pool_t* plat_mem_pool_create(IN u32 size);