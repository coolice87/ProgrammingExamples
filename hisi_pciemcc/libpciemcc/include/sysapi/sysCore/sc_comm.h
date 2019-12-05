/***********************************************************************
* Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
*
* Description: sc_comm.h  ����sc��һЩ��������
* OS : 
* Revisions  : Created on 2017-06-09
* Author: xu_longfei
*
**********************************************************************/

#ifndef __SC_COMM_H__
#define __SC_COMM_H__


/*value����align���϶���*/
#define SC_ALIGN_UP(value, align) ((((value) + (align) -1) / (align)) * (align))

/*value����align���¶���,����ȡ��*/
#define SC_ALIGN_DOWN(value, align) (((value) / (align)) * (align))

/* ��ֵ��С�Ƚ� */
#define SC_max(a, b)    ( (a) > (b) ? (a) : (b) )
#define SC_min(a, b)    ( (a) < (b) ? (a) : (b) )


/* ����NULLֵ */
#define SC_NULL      (NULL)

/* ���庯������ֵ */
#define SC_SUC      (0)		/* �ɹ� */
#define SC_FAIL     (-1)	/* ͨ�ô��� */
#define SC_BUSY     (-2)	/* ����æ */
#define SC_TIMEOUT  (-3)	/* �ȴ���ʱ */
#define SC_INTR     (-4)	/* ���ź��ж� */


/* ����Bool����ֵ */
#define SC_TRUE		(1)       /* �� */
#define SC_FALSE	(0)       /* �� */


/* ���峬ʱ���� */
#define SC_TIMEOUT_NONE         (0)    /* ����ʱ�ȴ����������ء�*/ 
#define SC_TIMEOUT_BLOCK      	(~0U)  /* �����ȴ���ֱ������ */


/* ���ݴ洢������λ */
#define SC_KB (1024)
#define SC_MB (SC_KB * SC_KB)
#define SC_GB (SC_KB * SC_MB)

/* ������� */
#define SC_setTrue(value)		((value) = SC_TRUE)
#define SC_setFalse(value)		((value) = SC_FALSE)  

#define SC_isNull(ptr)			(NULL == (ptr))
#define SC_isNotNull(ptr)		(NULL != (ptr))

#define SC_isTrue(value)		(SC_TRUE == (value))
#define SC_isNotTrue(value)		(SC_TRUE != (value))

#define SC_isSuc(value)			(SC_SUC == (value))
#define SC_isFail(value)		(SC_SUC != (value))


/* ��ȡ�����Ա���� */
#define SC_arraySize(array)    (sizeof(array)/sizeof((array)[0]))

/* 
** ���ð汾��ʹ�õĺ�:��8λ����߰汾��,�м�8λ��ʾ�а汾��,��16����version��
*/
#define SC_versionSet(major, minor, version)  \
        ((((major) & 0xff) << 24U) | (((minor) & 0xff) << 16U) | ((version) & 0xffff))

/* �ڴ���� */
#define SC_clear(ptr)					memset((ptr), 0, sizeof(*(ptr)))	
#define SC_clearSize(ptr, size)        	memset((ptr), 0, (size))
#define SC_setSize(ptr, value, size)    memset((ptr), value, (size))
#define SC_memCmp(dst, src)            	memcmp((dst), (src), sizeof(*(src)))
#define SC_memCmpSize(dst, src, size)  	memcmp((dst), (src), (size))

/* ��ȡ�ṹ���Ա�ĵ�ַƫ���� */
#ifdef __compiler_offsetof
#define SC_offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define SC_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


/* ͨ���ṹ���Ա��ȡ�ṹ���׵�ַ */
#define SC_getStructHead(ptr, type, member) ({			\
        const typeof(((type *)0)->member ) *__mptr = (ptr);	\
        (type *)((char *)__mptr - SC_offsetof(type,member));})

/* ���valueֵ�Ƿ���2��N�η� */
#define SC_checkIs2n(value)  ( ((value) == 0) ? SC_FALSE  \
         : ((value) & ((value) - 1)) ? SC_FALSE : SC_TRUE )

#ifdef _SC_DEBUG_

	#define SC_assert(x) \
		if(0 == (x)) \
		{ \
			assert(0); \
		}
		
	/*��ָ�����*/
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
