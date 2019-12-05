/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_vi_api.h
 * ** Desc          : 视频采集资源配置
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/

#ifndef __CFG_RES_VI_API_H__
#define __CFG_RES_VI_API_H__

#include "Avcomm.h"

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

/*视频采集资源结构,512字节*/
typedef struct RES_VI_CFG_s
{
	int32_t res[128];	/*暂时没有采集,预留*/
}RES_VI_CFG_S;


#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getViCfg(RES_VI_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif
