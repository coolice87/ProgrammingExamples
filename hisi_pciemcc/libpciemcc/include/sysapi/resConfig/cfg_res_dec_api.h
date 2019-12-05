/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_dec_api.h
 * ** Desc          : ������Դ����
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/

#ifndef __CFG_RES_DEC_API_H__
#define __CFG_RES_DEC_API_H__

#include "Avcomm.h"

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

/*������Դ�ṹ,512�ֽ�*/
typedef struct RES_DEC_CFG_s
{
	uint32_t maxChn;	/*������֧��ͨ����*/
	uint32_t compMask;	/*����֧����������,ȡֵvideo_comp_e*/
	uint32_t maxW;		/*��������,��λ����*/
	uint32_t maxH;		/*������߶�,��λ����*/
	uint32_t ability;	/*����֧������,D1Ϊ��λ����*/

	int32_t res[123];		/*����*/
}RES_DEC_CFG_S;

#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getDecCfg(RES_DEC_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

