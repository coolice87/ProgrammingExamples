/***********************************************************************
  * filename: plat_vdec.h 
  *
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Revisions  : Created on 2016-12-16
  * Author: hzgs
  *
  * Des:����ƽ̨�����ṩ�Ĺ��ܽӿ�
  *
  **********************************************************************/
#ifndef __PLAT_VDEC_H__
#define __PLAT_VDEC_H__

#include "Type.h"


#ifdef __cplusplus
extern "C"{
#endif

/* ����ͨ������*/
typedef struct
{
	uint32_t vdecMode; // ����ģʽ,ȡֵvdec_mode_e,ʵʱIPCԤ������ģʽ,�طŽ���ģʽ
	uint32_t encType;	/* ��������,ȡֵGCSTP_VENC_TYPE_E*/
	uint32_t width;		/* ������*/
	uint32_t height;	/* ����߶�*/
	uint32_t refnum;	/* �ο�֡��Ŀ*/
	uint8_t sn[64];   /* ��ǰ����ͨ��������к�,IPC���뷽ʽ����Ч*/
	uint32_t res[4];
}vdecparam_s;

/* �ͽ�������������Ϣ */
typedef struct
{
	uint8_t *pBuf;	/*����ָ��*/
	uint32_t len;	/*����*/
	uint32_t seq;	/*֡���*/
	uint32_t pts;	/*����ʱ���*/
	uint32_t fps;	/*֡��,���ڽ��������������;֡�ʿ���*/
	uint32_t res[3];
}VdecStreamDes_s;


/*********************************************************************
*������:plat_vdecCreateChn()
*��  ��:��������ƽ̨�Ľ���ͨ��
*��  ��:vdecChn: ����ͨ����
*		pstVdecParam:����ͨ������
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vdecCreateChn(int32_t vdecChn, vdecparam_s *pstVdecParam);

/*********************************************************************
*������:plat_vdecStartChn()
*��  ��:��������ͨ��,��ʼ��������
*��  ��:vdecChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vdecStartChn(int32_t vdecChn);

/*********************************************************************
*������:plat_vdecStopChn()
*��  ��:ֹͣ����ͨ��,ֹͣ��������
*��  ��:vdecChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vdecStopChn(int32_t vdecChn);

/*********************************************************************
*������:plat_vdecDestroyChn()
*��  ��:���ٽ���ͨ��
*��  ��:vdecChn: ����ͨ����
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vdecDestroyChn(int32_t vdecChn);

/*********************************************************************
*������:plat_vdecPutbuf()
*��  ��:����������,Ŀǰͳһ��֡��ʽ������
*��  ��:vdecChn: ����ͨ����
*		pstVdecStream:������Ϣ����
*		msTimeout:��ʱʱ��,��λms
*		
*����ֵ:0:�ɹ� -1:ʧ��
**********************************************************************/
int plat_vdecPutbuf(int32_t vdecChn, VdecStreamDes_s *pstVdecStream, uint32_t msTimeout);



#ifdef __cplusplus
}
#endif

#endif /* __PLAT_VDEC_H__*/
