/***********************************************************************
  * filename: plat_vdec.h 
  *
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Revisions  : Created on 2016-12-16
  * Author: hzgs
  *
  * Des:具体平台对外提供的功能接口
  *
  **********************************************************************/
#ifndef __PLAT_VDEC_H__
#define __PLAT_VDEC_H__

#include "Type.h"


#ifdef __cplusplus
extern "C"{
#endif

/* 解码通道属性*/
typedef struct
{
	uint32_t vdecMode; // 解码模式,取值vdec_mode_e,实时IPC预览解码模式,回放解码模式
	uint32_t encType;	/* 码流类型,取值GCSTP_VENC_TYPE_E*/
	uint32_t width;		/* 解码宽度*/
	uint32_t height;	/* 解码高度*/
	uint32_t refnum;	/* 参考帧数目*/
	uint8_t sn[64];   /* 当前解码通道相机序列号,IPC解码方式下有效*/
	uint32_t res[4];
}vdecparam_s;

/* 送解码数据描述信息 */
typedef struct
{
	uint8_t *pBuf;	/*数据指针*/
	uint32_t len;	/*长度*/
	uint32_t seq;	/*帧序号*/
	uint32_t pts;	/*毫秒时间戳*/
	uint32_t fps;	/*帧率,用于解码后数据其他用途帧率控制*/
	uint32_t res[3];
}VdecStreamDes_s;


/*********************************************************************
*函数名:plat_vdecCreateChn()
*功  能:创建具体平台的解码通道
*入  参:vdecChn: 解码通道号
*		pstVdecParam:解码通道属性
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vdecCreateChn(int32_t vdecChn, vdecparam_s *pstVdecParam);

/*********************************************************************
*函数名:plat_vdecStartChn()
*功  能:开启解码通道,开始接收数据
*入  参:vdecChn: 解码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vdecStartChn(int32_t vdecChn);

/*********************************************************************
*函数名:plat_vdecStopChn()
*功  能:停止解码通道,停止接受数据
*入  参:vdecChn: 解码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vdecStopChn(int32_t vdecChn);

/*********************************************************************
*函数名:plat_vdecDestroyChn()
*功  能:销毁解码通道
*入  参:vdecChn: 解码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vdecDestroyChn(int32_t vdecChn);

/*********************************************************************
*函数名:plat_vdecPutbuf()
*功  能:送码流数据,目前统一按帧方式送数据
*入  参:vdecChn: 解码通道号
*		pstVdecStream:码流信息描述
*		msTimeout:超时时间,单位ms
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vdecPutbuf(int32_t vdecChn, VdecStreamDes_s *pstVdecStream, uint32_t msTimeout);



#ifdef __cplusplus
}
#endif

#endif /* __PLAT_VDEC_H__*/
