/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_iva_api.h
 * ** Desc          : 智能分析资源配置
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/

#ifndef __CFG_RES_IVA_API_H__
#define __CFG_RES_IVA_API_H__

#include "Avcomm.h"

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

/*智能分析资源结构,512字节*/
typedef struct RES_IVA_CFG_s
{
	uint32_t maxChn;	/*最大支持通道数*/

	uint32_t maxW;		/*最大分析宽度,单位像素*/
	uint32_t maxH;		/*最大分析高度,单位像素*/

	int32_t res[125];	/*保留*/
}RES_IVA_CFG_S;


#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getIvaCfg(RES_IVA_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

