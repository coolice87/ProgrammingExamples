/***********************************************************************
* filename: video_iva.h 
*
* Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
*
* Revisions  : Created on 2016-12-20
* Author: hzgs
*
* Des: iva���ý��⽻���ӿ�
*
**********************************************************************/

#ifndef __VIDEO_IVA_API_H__
#define __VIDEO_IVA_API_H__

#include "Type.h"

#ifdef __cplusplus
extern "C" {
#endif

/*ԭʼ�����ڴ�ֲ���ʽ*/
typedef enum imageformat
{
    Yonly,		/* Y ����*/
    YUVYUV,		/* YUV���*/
    YYUVUV,		/* YUV��ƽ��,Yƽ��UV���*/
    YYUUVV,		/* YUVƽ��*/
    YUVUV		/**/
}ImageFormat;

/*���ݽṹ*/
typedef struct VA_IMAG_INFO_s
{
	uint32_t seq;		/* ֡���*/
	int32_t width;		/* ������ͼƬ���*/
	int32_t height;		/* ������ͼƬ�߶�*/
	int32_t stride;		/* ������ͼƬ���*/
	int32_t format;		/* ���ݸ�ʽ,ȡֵImageFormat*/
	int32_t adapt;		/* ����Ӧ��־,1:��ʾ��Ҫ����ͼƬ��С��������Ӧ,��������Ҫ*/
	uint8_t *virtAddr;	/* �����ַ*/
	uint32_t phyAddr;	/* �����ַ*/
	uint8_t sn[64];     /* ���id,IPCģʽ��Ч*/
	int32_t res[8];		/* ����*/
}VA_IMAG_INFO_S;

/*֡���ü���*/
typedef struct
{
	uint32_t srcSeq;
	uint32_t refCnt;
	uint32_t res[2];
}FrameRefcnt_S;

/*�㷨����ý��ⷢ��ͼƬ����*/
typedef struct RqImageParam
{
	Handle pHandle;		/* ���������*/
	int32_t chn;		/* ͨ����*/
	int32_t chnType;	/* ͨ������,IPC\VI ��ʱδ��*/
	int32_t width;		/* ������ͼƬ���*/
	int32_t height;		/* ������ͼƬ�߶�*/
	int32_t fps;		/* �㷨����Ҫ��֡��*/
	int32_t format;		/* ���ݸ�ʽ,ȡֵImageFormat*/
	int32_t holdNum;	/* ץͼ����;Ҫ��Ļ�������,0��ʾ����Ҫ����,�������������ͷ�*/
	int32_t res[3];
}RqImageParam;

/*********************************************************************
*������:Iva_sendYuvImage()
*��  ��:yuv�������뺯��
*��  ��:pHandle:���������,�㷨ת��
*		pImageInfo:������Ϣָ��
*		len:���ݳ���
*����ֵ:0:�ɹ���Ҫ����ԭʼͼƬ  -1:ʧ�� ������ԭʼͼƬ
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
int Iva_sendYuvImage(Handle pHandle, VA_IMAG_INFO_S *pImageInfo, uint32_t len);

/*********************************************************************
*������:Iva_getBigpicSnapStatus()
*��  ��:��ȡID���������ڴ�ͼ����״̬
*��  ��:pHandle:���������,�㷨ת��
*		ID:������ID
*����ֵ:0:δ����  1:�ѱ���
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
uint32_t Iva_getBigpicSnapStatus(Handle pHandle, uint32_t ID);

/*********************************************************************
*������:Iva_setBigpicSnapStatus()
*��  ��:����ID���������ڴ�ͼ����״̬,Ĭ��״̬Ϊδ����,��������
*��  ��:pHandle:���������,�㷨ת��
*		ID:������ID
*		status:��ͼ����״̬ 0:δ���� 1:�ѱ���
*����ֵ:0:�ɹ���Ҫ����ԭʼͼƬ  -1:ʧ�� ������ԭʼͼƬ
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
int Iva_setBigpicSnapStatus(Handle pHandle, uint32_t ID, uint32_t status);

/*********************************************************************
*������:Iva_RequestImageRegistCBFunc
*��  ��:ʹ���߼�ͨ��
*��  ��:pHandle ���������,�ڲ�ת��
*		pImageParam �������ݲ���
*		enable:1ͨ��ʹ��
*				0ͨ���ر�	
*����ֵ:0:�ɹ�;-1:ʧ��
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
int Iva_RequestImageRegistCBFunc(int (*IvaRqImageCbFun)(RqImageParam *pImageParam, int enable));

/*********************************************************************
*������:Iva_ImageAddrefRegistCBFunc
*��  ��:�㷨������ԭʼͼƬ���ûص�ע�ắ��
*��  ��:pHandle ���������,�ڲ�ת��
*		chn �������ݲ���
*		snapCnt:ץͼ���ô���
*
*����ֵ:0:�ɹ�;-1:ʧ��
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
int Iva_ImageAddSnapRefRegistCBFunc(int (*IvaImageAddSnapRefCbFun)(Handle vaHandle, int chn, uint32_t srcSeq, int snapCnt));


/*********************************************************************
*������:Iva_ImageResetRefRegistCBFunc
*��  ��:�㷨������ԭʼͼƬ���ûص�ע�ắ��
*��  ��:pHandle ���������,�ڲ�ת��
*		chn �������ݲ���
*		stFrameRef[]:�������ô���
*		cnt:stFrameRef�������
*����ֵ:0:�ɹ�;-1:ʧ��
*---------------------------------------------------------------------
*�޸ļ�¼:
**********************************************************************/
int Iva_ImageResetRefRegistCBFunc(int (*IvaImageResetRefCbFun)(Handle vaHandle, int chn, FrameRefcnt_S stFrameRef[], int cnt));


#ifdef __cplusplus
}
#endif

#endif
