/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_enc_api.h
 * ** Desc          : ������Դ����
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/

#ifndef __CFG_RES_ENC_API_H__
#define __CFG_RES_ENC_API_H__

#include "Avcomm.h"

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

/*������Դ�ṹ,512�ֽ�*/
typedef struct RES_ENC_CFG_s
{
	uint32_t u32SupportType;	/*֧�ֱ�������,video_comp_e����*/
	uint32_t u32Brc;			/*���ʿ��Ʒ�ʽ,ȡֵvenc_brc_e����*/
	uint32_t u32StreamType;		/*֧����������,ȡֵ����*/
	uint32_t u32MaxChn;			/*����ͨ����*/
	uint32_t maxW;				/*��������,��λ����*/
	uint32_t maxH;				/*������߶�,��λ����*/
	uint32_t ability;			/*����֧������,D1Ϊ��λ����*/

	uint32_t res[121];
}RES_ENC_CFG_S;

#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getEncCfg(RES_ENC_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

