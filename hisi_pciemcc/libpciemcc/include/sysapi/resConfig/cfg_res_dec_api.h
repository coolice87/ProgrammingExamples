/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_dec_api.h
 * ** Desc          : 解码资源配置
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

/*解码资源结构,512字节*/
typedef struct RES_DEC_CFG_s
{
	uint32_t maxChn;	/*最大解码支持通道数*/
	uint32_t compMask;	/*解码支持类型掩码,取值video_comp_e*/
	uint32_t maxW;		/*最大解码宽度,单位像素*/
	uint32_t maxH;		/*最大解码高度,单位像素*/
	uint32_t ability;	/*解码支持能力,D1为单位计算*/

	int32_t res[123];		/*保留*/
}RES_DEC_CFG_S;

#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getDecCfg(RES_DEC_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

