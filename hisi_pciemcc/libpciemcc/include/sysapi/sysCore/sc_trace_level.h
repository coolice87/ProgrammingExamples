/***********************************************************************
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Description: sc_trace_level.h 
  * Revisions  : Created on 2017-06-09
  * Author: xu_longfei
  *
  **********************************************************************/

#ifndef __SC_TRACE_LEVEL_H__
#define __SC_TRACE_LEVEL_H__

#ifdef __KERNEL__    /* linux kernel */
    #include <linux/kernel.h>

    #define SC_print  printk
#else                /* linux Application */
    #include <stdio.h>
    
    #define SC_print  printf
#endif

/* 打印字体显示的颜色 */
#define NONE          "\033[m"   
#define RED           "\033[0;32;31m"   
#define GREEN         "\033[0;32;32m"   
#define BLUE          "\033[0;32;34m"   
#define DARY_GRAY     "\033[1;30m"   
#define CYAN          "\033[0;36m"   
#define PURPLE        "\033[0;35m"     
#define BROWN         "\033[0;33m"   
#define YELLOW        "\033[1;33m"   
#define WHITE         "\033[1;37m"   

#ifndef SC_MODULE_NAME
#error Not defined SC_MODULE_NAME !!!
#endif

#ifdef  _SC_DEBUG_
#define SC_DEBUG(fmt, args ...) \
	do{ \
		SC_print("DEBUG|"SC_MODULE_NAME"|(%s|%d):" fmt, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_INFO(fmt, args ...)  \
	do{ \
		SC_print("INFO|"SC_MODULE_NAME"|(%s|%d):" fmt, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_WARN(fmt, args ...)  \
	do{ \
		SC_print(YELLOW "WARN|" SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_ERROR(fmt, args ...)  \
	do{ \
		SC_print(RED "ERROR|"SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_ERRFATAL(fmt, args ...)  \
	do{ \
		SC_print(RED "FATALERR|"SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)
#else
/******************************************************************/
/*      打印统一输出到log库，由log库进行等级管理及日志保存        */
/******************************************************************/
#include "GsLog.h"

#define SC_DEBUG(fmt, args ...) \
	do{ \
		gsPrintf(GsLogLevel_debug,"DEBUG|"SC_MODULE_NAME"|(%s|%d):" fmt, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_INFO(fmt, args ...)  \
	do{ \
		gsPrintf(GsLogLevel_info,"INFO|"SC_MODULE_NAME"|(%s|%d):" fmt, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_WARN(fmt, args ...)  \
	do{ \
		gsPrintf(GsLogLevel_warn,YELLOW "WARN|" SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#define SC_ERROR(fmt, args ...)  \
	do{ \
		gsPrintf(GsLogLevel_error,RED "ERROR|"SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)
		
#define SC_ERRFATAL(fmt, args ...)  \
	do{ \
		gsPrintf(GsLogLevel_fatal,RED "FATALERR|"SC_MODULE_NAME"|(%s|%d):" fmt NONE, \
		__func__, __LINE__, ## args); \
	} \
	while(0)

#endif
	
#endif
