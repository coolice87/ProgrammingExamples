/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_vo_api.h
 * ** Desc          : 视频输出资源配置
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

#define MAX_RES_VO_DEV_NUM (8)		/*最大支持8个显示设备*/

/*视频输出资源结构,512字节*/
typedef struct RES_VO_CFG_s
{
	uint32_t uiDevNum;							/*输出设备数*/
	uint8_t devId[MAX_RES_VO_DEV_NUM];			/*输出设备ID号*/
	uint8_t maxChnNum[MAX_RES_VO_DEV_NUM];		/*每个设备最大显示通道数*/
	uint32_t reslutionMask[MAX_RES_VO_DEV_NUM];	/*输出分辨率掩码,video_out_resolution_e*/
	
	int32_t res[115];							/*预留*/
}RES_VO_CFG_S;

#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getVoCfg(RES_VO_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif

