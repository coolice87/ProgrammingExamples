/***********************************************************************
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Description: sc_mem.h 
  * Revisions  : Created on 2017-06-09
  * Author: xu_longfei
  *
  **********************************************************************/

#ifndef __SC_MEM_H__
#define __SC_MEM_H__

/*内存操作私有头,4字节对齐*/
typedef struct
{
	uint32_t uiMagic;
	uint32_t uiSize;
}SC_MEM_HEAD_S;


#ifdef __cplusplus
extern "C"{
#endif

#define SC_memAlloc(size)          SC_memUAllocAlign((size), 0)
/*增加memset 0操作*/
#define SC_memCalloc(size)         SC_memUCallocAlign((size), 0)
#define SC_memFree(ptr)            SC_memUFree((ptr))
#define SC_memCpy(dst, src)        SC_memCpySize((dst), (src), sizeof(*(src)))


/*********************************************************************
*函数名:SC_memUAllocAlign()
*功  能:用户态对齐申请内存
*入  参:size: 内存大小
*		align:对齐参数，必须是4的整数倍对齐
*		
*返回值:非NULL:成功 NULL:失败
**********************************************************************/
Ptr SC_memUAllocAlign(uint32_t size, uint32_t align);

/*********************************************************************
*函数名:SC_memUCallocAlign()
*功  能:用户态对齐申请内存,增加清零操作
*入  参:size: 内存大小
*		align:对齐参数，必须是4的整数倍对齐
*		
*返回值:非NULL:成功 NULL:失败
**********************************************************************/
Ptr SC_memUCallocAlign(uint32_t size, uint32_t align);


/*********************************************************************
*函数名:SC_memUFree()
*功  能:释放内存
*入  参:pPtr: 内存指针
*		
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int32_t SC_memUFree(Ptr pPtr);

#ifdef __ARM_NEON__
/*******************************************************************************
* 函数名: SC_memCpySize
* 功  能: 该函数负责在linux用户态下进行数据拷贝
* 入  参: - pDst: 目的地址
*       : - pSrc: 源地址
*       : - size: 拷贝数据长度
* 返回值: Ptr : 指向目的地址的指针 
*******************************************************************************/
Ptr SC_memCpySize(Ptr pDst,Ptr pSrc,uint32_t size);
#else
#define SC_memCpySize(dst, src, size)  memcpy((dst), (src), (size))
#endif


#ifdef __cplusplus
}
#endif

#endif  /*  end __SC_MEM_H__  */


