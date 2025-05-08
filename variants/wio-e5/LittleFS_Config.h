#pragma once

#include <Adafruit_LittleFS.h>

#define LFS_UNUSED(p) (void)((p))
    
#define STM32WL_PAGE_SIZE (FLASH_PAGE_SIZE)
#define STM32WL_PAGE_COUNT (FLASH_PAGE_NB)
#define STM32WL_FLASH_BASE (FLASH_BASE)
    
#define LFS_FLASH_TOTAL_SIZE (16 * 2048) /* 32k flash */
#define LFS_BLOCK_SIZE (2048)
#define LFS_FLASH_ADDR_END (FLASH_END_ADDR)
#define LFS_FLASH_ADDR_BASE (LFS_FLASH_ADDR_END - LFS_FLASH_TOTAL_SIZE + 1)
    
#define _LFS_DBG(fmt, ...)

extern struct lfs_config _InternalFSConfig;