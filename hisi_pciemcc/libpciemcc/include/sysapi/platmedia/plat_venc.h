/***********************************************************************
  * filename: plat_venc.h 
  *
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Revisions  : Created on 2016-12-27
  * Author: hzgs
  *
  * Des:����ƽ̨�����ṩ�Ĺ��ܽӿ�
  *
  **********************************************************************/
#ifndef __PLAT_VENC_H__
#define __PLAT_VENC_H__

#include "Type.h"


#ifdef __cplusplus
extern "C"{
#endif

/* ����ͨ������*/
typedef struct
{
	uint32_t encType;	/* ��������,ȡֵGCSTP_VENC_TYPE_E*/
	uint32_t width;		/* ������*/
	uint32_t height;	/* ����߶�*/
	uint32_t fps;		/* ֡��,��16λ��ʾ��ĸ����Ϊ0��ʾ֧�ַ���֡�ʣ���16λ��ʾ����*/
	uint32_t gop;		/* I֡���*/ 
	uint32_t bitRate;	/* ��������*/
	uint32_t quality;	/* ͼƬ����*/
	uint32_t refnum;	/* �ο�֡��Ŀ*/

	VEMallocPacketLst	mallocPacketLst;/*����PacketLst*/
	VEFreePacketLst		freePacketLst;	/*�ͷ�PacketLst����releaseResult�е���*/
	uint32_t res[8];
}vencparam_s;

/* ��������������Ϣ */
typedef struct
{
	uint8_t *pBuf;	/*����ָ��*/
	uint32_t len;	/*����*/
	uint32_t seq;	/*֡���*/
	uint32_t pts;	/*����ʱ���*/
	uint32_t res[4];
}VencStreamDes_s;

#define MAX_CUTOUT_CNT (50)
/* ��ͼλ�ü�֡������ò���*/
typedef struct vencCutOutRect
{
	uint32_t encSeq;	/* ��Ҫ�͵���������֡���*/
	Rect stRect;		/* ��ͼ��Ϣ,����0 - 8192�������ϵ*/
}vencCutOutRect_s;

/* ��ͼ������Ϣ */
typedef struct vencCutOutParam
{
	uint32_t seq;		/* ��Ҫ��ͼ��֡���*/
	uint32_t headSeq;	/* ͷ֡���*/
	uint32_t cnt;		/* ��������*/
	/* ��ͼλ�����ò���,��Ч��ȡ����cnt*/
	vencCutOutRect_s stCutOutRect[MAX_CUTOUT_CNT];
	uint32_t objIDCnt;  /*���Ŀ��ID��*/
	uint32_t *objIDList;/*���objIDCntʹ��,ע���ͷ�*/
	uint32_t res[4];
} vencCutOutParam_s;

/*********************************************************************
*������:plat_vencCreateChn()
*��  ��:��������ƽ̨�ı���ͨ��
*��  ��:vencChn: ����ͨ����
*		pstVencParam:����ͨ������
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencCreateChn(int32_t vencChn, vencparam_s *pstVencParam);

/*********************************************************************
*������:plat_vencSetParam()
*��  ��:��������ƽ̨�ı���ͨ��
*��  ��:vencChn: ����ͨ����
*		pstVeParam:����ͨ������
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencSetParam(int32_t vencChn, VEParam *pstVeParam);

/*********************************************************************
*������:plat_vencCutOutInfo()
*��  ��:���ÿ�ͼ
*��  ��:vencChn: ����ͨ����
*		pstVencParam:����ͨ������
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencCutOutInfo(int32_t vencChn, vencCutOutParam_s *pstVencParam);

/*********************************************************************
*������:plat_vencStartChn()
*��  ��:��������ͨ��,��ʼ��������
*��  ��:vencChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencStartChn(int32_t vencChn);

/*********************************************************************
*������:plat_vencStopChn()
*��  ��:ֹͣ����ͨ��,ֹͣ��������
*��  ��:vencChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencStopChn(int32_t vencChn);

/*********************************************************************
*������:plat_vencDestroyChn()
*��  ��:���ٱ���ͨ��
*��  ��:vencChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencDestroyChn(int32_t vencChn);

/*********************************************************************
*������:plat_vencGetStream()
*��  ��:���ٱ���ͨ��
*��  ��:vencChn: ����ͨ����
*		pstVencStream ����buf����
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencGetStream(int32_t vencChn, VEResult *pstVencStream);

/*********************************************************************
*������:plat_vencGetStream()
*��  ��:���ٱ���ͨ��
*��  ��:vencChn: ����ͨ����
*		pstVencStream ����buf����
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vencReleaseStream(int32_t vencChn, VEResult *pstVencStream);


#ifdef __cplusplus
}
#endif

#endif /* __PLAT_VENC_H__*/

