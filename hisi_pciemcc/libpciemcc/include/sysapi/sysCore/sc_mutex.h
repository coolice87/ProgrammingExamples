/***********************************************************************
* Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
*
* Description: sc_mutex.h 
* Revisions  : Created on 2017-06-09
* Author: xu_longfei
*
*
* 		  接口调用流程如下:
* 		  ==========================
* 				  | 						   
* 		  SC_mutexCreate
* 				  |
* 		  SC_mutexLock/SC_mutexUnlock
* 				  |
* 		  SC_mutexDelete
* 		  ===========================
* 		  注意:对于类型为SC_MUTEX_NORMAL的互斥锁，同一线程不能加锁多次
* 			   对于类型为SC_MUTEX_RECURSIVE的互斥锁，同一线程可以加锁多次
*
*
************************************************************************/


#ifndef __SC_MUTEX_H__
#define __SC_MUTEX_H__

#include "sc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif


/* 调用SC_mutexCreate返回的互斥锁句柄类型,上层模块不需要关心其中的具体内容,*/
/* 只需要在各互斥锁操作接口中传入该句柄即可*/
typedef Handle SC_MutexHandle;

/*定义互斥锁的类型*/
typedef enum
{
    SC_MUTEX_NORMAL = 0,      /*普通锁,不支持递归*/
    SC_MUTEX_RECURSIVE        /*递归锁,支持递归加锁,即同一线程可以对锁加锁多次*/
}SC_MutexType;

/*定义线程互斥锁对象*/
typedef struct
{
    uint32_t uiMgicNum;			/*魔数,用于校验句柄有效性。*/

    pthread_mutex_t lock;		/*用户态互斥锁变量*/
}SC_MutexObj;

/*********************************************************************
*函数名:SC_mutexCreate
*功  能:创建一个线程互斥锁
*入  参:type:    互斥锁类型,参见SC_MutexType定义
*		phMutex: 互斥锁句柄指针,当创建成功时输出互斥锁句柄
*		
*返回值: SC_SUC:  创建成功
*        SC_FAIL: 创建失败
**********************************************************************/
int32_t SC_mutexCreate(uint32_t type, SC_MutexHandle *phMutex);

/*********************************************************************
*函数名:SC_mutexLock
*功  能:互斥锁加锁
*入  参:hMutex: 互斥锁句柄
*		
*返回值: SC_SUC:  创建成功
*		 SC_FAIL: 创建失败
**********************************************************************/
int32_t SC_mutexLock(SC_MutexHandle hMutex);


/*********************************************************************
*函数名:SC_mutexTryLock
*功  能:试图对互斥锁进行加锁。该接口目前只支持Linux用户层调用。
*       该接口不能在内核态中断上下文调用
*入  参:hMutex: 互斥锁句柄
*		
*返回值:SC_SUC:  成功
*       SC_BUSY: 锁被占用
*       SC_FAIL: 失败
**********************************************************************/
int32_t SC_mutexTryLock(SC_MutexHandle hMutex);


/*******************************************************************************
* 函数名: SC_mutexUnlock
* 功  能: 互斥锁解锁
*         该接口不能在内核态中断上下文调用
* 入  参: hMutex: 互斥锁句柄,
*
* 返回值: SC_SUC:  成功
*         SC_FAIL: 失败
*******************************************************************************/
int32_t SC_mutexUnlock(SC_MutexHandle hMutex);

/*******************************************************************************
* 函数名: SC_mutexDelete
* 功  能: 销毁一个线程互斥锁
*		  该接口不能在内核态中断上下文调用
* 入  参: hMutex: 互斥锁句柄,
*
* 返回值: SC_SUC:  成功
*		  SC_FAIL: 失败
*******************************************************************************/
int32_t SC_mutexDelete(SC_MutexHandle hMutex);

#ifdef __cplusplus
}
#endif

#endif  /*  _SC_MUTEX_H_  */


