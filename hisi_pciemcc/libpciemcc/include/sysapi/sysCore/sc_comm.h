/***********************************************************************
* Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
*
* Description: sc_comm.h  定义sc库一些公用杂项
* OS : 
* Revisions  : Created on 2017-06-09
* Author: xu_longfei
*
**********************************************************************/

#ifndef __SC_COMM_H__
#define __SC_COMM_H__


/*value按照align向上对齐*/
#define SC_ALIGN_UP(value, align) ((((value) + (align) -1) / (align)) * (align))

/*value按照align向下对齐,对齐取整*/
#define SC_ALIGN_DOWN(value, align) (((value) / (align)) * (align))

/* 数值大小比较 */
#define SC_max(a, b)    ( (a) > (b) ? (a) : (b) )
#define SC_min(a, b)    ( (a) < (b) ? (a) : (b) )


/* 定义NULL值 */
#define SC_NULL      (NULL)

/* 定义函数返回值 */
#define SC_SUC      (0)		/* 成功 */
#define SC_FAIL     (-1)	/* 通用错误 */
#define SC_BUSY     (-2)	/* 对象忙 */
#define SC_TIMEOUT  (-3)	/* 等待超时 */
#define SC_INTR     (-4)	/* 被信号中断 */


/* 定义Bool类型值 */
#define SC_TRUE		(1)       /* 真 */
#define SC_FALSE	(0)       /* 假 */


/* 定义超时参数 */
#define SC_TIMEOUT_NONE         (0)    /* 不超时等待，立即返回。*/ 
#define SC_TIMEOUT_BLOCK      	(~0U)  /* 阻塞等待，直到返回 */


/* 数据存储度量单位 */
#define SC_KB (1024)
#define SC_MB (SC_KB * SC_KB)
#define SC_GB (SC_KB * SC_MB)

/* 设置真假 */
#define SC_setTrue(value)		((value) = SC_TRUE)
#define SC_setFalse(value)		((value) = SC_FALSE)  

#define SC_isNull(ptr)			(NULL == (ptr))
#define SC_isNotNull(ptr)		(NULL != (ptr))

#define SC_isTrue(value)		(SC_TRUE == (value))
#define SC_isNotTrue(value)		(SC_TRUE != (value))

#define SC_isSuc(value)			(SC_SUC == (value))
#define SC_isFail(value)		(SC_SUC != (value))


/* 获取数组成员数量 */
#define SC_arraySize(array)    (sizeof(array)/sizeof((array)[0]))

/* 
** 设置版本号使用的宏:高8位代表高版本号,中间8位表示中版本号,低16代表version。
*/
#define SC_versionSet(major, minor, version)  \
        ((((major) & 0xff) << 24U) | (((minor) & 0xff) << 16U) | ((version) & 0xffff))

/* 内存操作 */
#define SC_clear(ptr)					memset((ptr), 0, sizeof(*(ptr)))	
#define SC_clearSize(ptr, size)        	memset((ptr), 0, (size))
#define SC_setSize(ptr, value, size)    memset((ptr), value, (size))
#define SC_memCmp(dst, src)            	memcmp((dst), (src), sizeof(*(src)))
#define SC_memCmpSize(dst, src, size)  	memcmp((dst), (src), (size))

/* 获取结构体成员的地址偏移量 */
#ifdef __compiler_offsetof
#define SC_offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define SC_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


/* 通过结构体成员获取结构体首地址 */
#define SC_getStructHead(ptr, type, member) ({			\
        const typeof(((type *)0)->member ) *__mptr = (ptr);	\
        (type *)((char *)__mptr - SC_offsetof(type,member));})

/* 检测value值是否是2的N次方 */
#define SC_checkIs2n(value)  ( ((value) == 0) ? SC_FALSE  \
         : ((value) & ((value) - 1)) ? SC_FALSE : SC_TRUE )

#ifdef _SC_DEBUG_

	#define SC_assert(x) \
		if(0 == (x)) \
		{ \
			assert(0); \
		}
		
	/*空指针断言*/
	#define SC_assertIsNull(Ptr) \
		SC_assert(!(NULL == Ptr))
	
	#define SC_assertIsFail(ret) \
				SC_assert(!(SC_SUC == ret))
#else
	#define SC_assert(x)
	#define SC_assertIsNull(Ptr)
	#define SC_assertIsFail(ret)
#endif

#endif /*end __SC_COMM_H__*/
