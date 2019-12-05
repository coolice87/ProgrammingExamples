/********************************************************************************
 * ** Copyright (C) 2016-2025, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : bootenv.h
 * ** Desc          : provide interfaces to other library 
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_02_21
 * ********************************************************************************/
#ifndef _BOOTENV_H_
#define _BOOTENV_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 配置恢复默认boot控制变量, 1:恢复默认,0:不恢复 */
#define BOOT_ENV_DEFAULT_CONFIG 	"defaultcfg"

int bootenv_init(void);

void bootenv_destroy(void);

int bootenv_set_value(char *ps8Key, const char *ps8Value);

int bootenv_get_value(char *ps8Key, char *ps8Data, uint32_t u32Len);

#ifdef __cplusplus
}
#endif 


#endif


