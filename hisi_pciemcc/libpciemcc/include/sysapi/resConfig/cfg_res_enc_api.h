/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_enc_api.h
 * ** Desc          : 编码资源配置
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

/*编码资源结构,512字节*/
typedef struct RES_ENC_CFG_s
{
	uint32_t u32SupportType;	/*支持编码类型,video_comp_e掩码*/
	uint32_t u32Brc;			/*码率控制方式,取值venc_brc_e掩码*/
	uint32_t u32StreamType;		/*支持码流类型,取值掩码*/
	uint32_t u32MaxChn;			/*编码通道数*/
	uint32_t maxW;				/*最大编码宽度,单位像素*/
	uint32_t maxH;				/*最大编码高度,单位像素*/
	uint32_t ability;			/*编码支持能力,D1为单位计算*/

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

