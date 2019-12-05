/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_vo_api.h
 * ** Desc          : ��Ƶ�����Դ����
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/

#ifndef __CFG_RES_VO_API_H__
#define __CFG_RES_VO_API_H__

#include "Avcomm.h"

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

#define MAX_RES_VO_DEV_NUM (8)		/*���֧��8����ʾ�豸*/

/*��Ƶ�����Դ�ṹ,512�ֽ�*/
typedef struct RES_VO_CFG_s
{
	uint32_t uiDevNum;							/*����豸��*/
	uint8_t devId[MAX_RES_VO_DEV_NUM];			/*����豸ID��*/
	uint8_t maxChnNum[MAX_RES_VO_DEV_NUM];		/*ÿ���豸�����ʾͨ����*/
	uint32_t reslutionMask[MAX_RES_VO_DEV_NUM];	/*����ֱ�������,video_out_resolution_e*/
	
	int32_t res[115];							/*Ԥ��*/
}RES_VO_CFG_S;

#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getVoCfg(RES_VO_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

