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

/*�ڴ����˽��ͷ,4�ֽڶ���*/
typedef struct
{
	uint32_t uiMagic;
	uint32_t uiSize;
}SC_MEM_HEAD_S;


#ifdef __cplusplus
extern "C"{
#endif

#define SC_memAlloc(size)          SC_memUAllocAlign((size), 0)
/*����memset 0����*/
#define SC_memCalloc(size)         SC_memUCallocAlign((size), 0)
#define SC_memFree(ptr)            SC_memUFree((ptr))
#define SC_memCpy(dst, src)        SC_memCpySize((dst), (src), sizeof(*(src)))


/*********************************************************************
*������:SC_memUAllocAlign()
*��  ��:�û�̬���������ڴ�
*��  ��:size: �ڴ��С
*		align:���������������4������������
*		
*����ֵ:��NULL:�ɹ� NULL:ʧ��
**********************************************************************/
Ptr SC_memUAllocAlign(uint32_t size, uint32_t align);

/*********************************************************************
*������:SC_memUCallocAlign()
*��  ��:�û�̬���������ڴ�,�����������
*��  ��:size: �ڴ��С
*		align:���������������4������������
*		
*����ֵ:��NULL:�ɹ� NULL:ʧ��
**********************************************************************/
Ptr SC_memUCallocAlign(uint32_t size, uint32_t align);


/*********************************************************************
*������:SC_memUFree()
*��  ��:�ͷ��ڴ�
*��  ��:pPtr: �ڴ�ָ��
*		
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int32_t SC_memUFree(Ptr pPtr);

#ifdef __ARM_NEON__
/*******************************************************************************
* ������: SC_memCpySize
* ��  ��: �ú���������linux�û�̬�½������ݿ���
* ��  ��: - pDst: Ŀ�ĵ�ַ
*       : - pSrc: Դ��ַ
*       : - size: �������ݳ���
* ����ֵ: Ptr : ָ��Ŀ�ĵ�ַ��ָ�� 
*******************************************************************************/
Ptr SC_memCpySize(Ptr pDst,Ptr pSrc,uint32_t size);
#else
#define SC_memCpySize(dst, src, size)  memcpy((dst), (src), (size))
#endif


#ifdef __cplusplus
}
#endif

#endif  /*  end __SC_MEM_H__  */


