/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : cfg_res_audio_api.h
 * ** Desc          : ��Ƶ��Դ����
 * ** Author        : 
 * ** LastChange    : 2017_04_25
 * ********************************************************************************/
#ifndef __CFG_RES_AUDIO_API_H__
#define __CFG_RES_AUDIO_API_H__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "Type.h"
#endif

/*��Ƶ��Դ�ṹ,512�ֽ�*/
typedef struct RES_AUD_CFG_s
{
	int32_t res[128];
}RES_AUD_CFG_S;


#ifdef __cplusplus
extern "C"{
#endif

int32_t RES_getAudioCfg(RES_AUD_CFG_S *pstResCfg);

#ifdef __cplusplus
}
#endif


#endif
