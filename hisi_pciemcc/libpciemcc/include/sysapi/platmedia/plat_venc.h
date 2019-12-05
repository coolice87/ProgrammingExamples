/***********************************************************************
  * filename: plat_venc.h 
  *
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Revisions  : Created on 2016-12-27
  * Author: hzgs
  *
  * Des:具体平台对外提供的功能接口
  *
  **********************************************************************/
#ifndef __PLAT_VENC_H__
#define __PLAT_VENC_H__

#include "Type.h"


#ifdef __cplusplus
extern "C"{
#endif

/* 编码通道属性*/
typedef struct
{
	uint32_t encType;	/* 码流类型,取值GCSTP_VENC_TYPE_E*/
	uint32_t width;		/* 编码宽度*/
	uint32_t height;	/* 编码高度*/
	uint32_t fps;		/* 帧率,高16位表示分母、不为0表示支持分数帧率，低16位表示分子*/
	uint32_t gop;		/* I帧间隔*/ 
	uint32_t bitRate;	/* 编码码率*/
	uint32_t quality;	/* 图片质量*/
	uint32_t refnum;	/* 参考帧数目*/

	VEMallocPacketLst	mallocPacketLst;/*申请PacketLst*/
	VEFreePacketLst		freePacketLst;	/*释放PacketLst，在releaseResult中调用*/
	uint32_t res[8];
}vencparam_s;

/* 编码数据描述信息 */
typedef struct
{
	uint8_t *pBuf;	/*数据指针*/
	uint32_t len;	/*长度*/
	uint32_t seq;	/*帧序号*/
	uint32_t pts;	/*毫秒时间戳*/
	uint32_t res[4];
}VencStreamDes_s;

#define MAX_CUTOUT_CNT (50)
/* 抠图位置及帧序号配置参数*/
typedef struct vencCutOutRect
{
	uint32_t encSeq;	/* 需要送到编码器的帧序号*/
	Rect stRect;		/* 抠图信息,采用0 - 8192相对坐标系*/
}vencCutOutRect_s;

/* 抠图配置信息 */
typedef struct vencCutOutParam
{
	uint32_t seq;		/* 需要抠图的帧序号*/
	uint32_t headSeq;	/* 头帧序号*/
	uint32_t cnt;		/* 编码张数*/
	/* 抠图位置配置参数,有效数取决于cnt*/
	vencCutOutRect_s stCutOutRect[MAX_CUTOUT_CNT];
	uint32_t objIDCnt;  /*检测目标ID数*/
	uint32_t *objIDList;/*配合objIDCnt使用,注意释放*/
	uint32_t res[4];
} vencCutOutParam_s;

/*********************************************************************
*函数名:plat_vencCreateChn()
*功  能:创建具体平台的编码通道
*入  参:vencChn: 编码通道号
*		pstVencParam:编码通道属性
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencCreateChn(int32_t vencChn, vencparam_s *pstVencParam);

/*********************************************************************
*函数名:plat_vencSetParam()
*功  能:创建具体平台的编码通道
*入  参:vencChn: 编码通道号
*		pstVeParam:编码通道参数
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencSetParam(int32_t vencChn, VEParam *pstVeParam);

/*********************************************************************
*函数名:plat_vencCutOutInfo()
*功  能:设置抠图
*入  参:vencChn: 编码通道号
*		pstVencParam:编码通道属性
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencCutOutInfo(int32_t vencChn, vencCutOutParam_s *pstVencParam);

/*********************************************************************
*函数名:plat_vencStartChn()
*功  能:开启编码通道,开始接收数据
*入  参:vencChn: 编码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencStartChn(int32_t vencChn);

/*********************************************************************
*函数名:plat_vencStopChn()
*功  能:停止编码通道,停止接受数据
*入  参:vencChn: 编码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencStopChn(int32_t vencChn);

/*********************************************************************
*函数名:plat_vencDestroyChn()
*功  能:销毁编码通道
*入  参:vencChn: 编码通道号
*		
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencDestroyChn(int32_t vencChn);

/*********************************************************************
*函数名:plat_vencGetStream()
*功  能:销毁编码通道
*入  参:vencChn: 编码通道号
*		pstVencStream 码流buf描述
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencGetStream(int32_t vencChn, VEResult *pstVencStream);

/*********************************************************************
*函数名:plat_vencGetStream()
*功  能:销毁编码通道
*入  参:vencChn: 编码通道号
*		pstVencStream 码流buf描述
*返回值:0:成功 -1:失败
**********************************************************************/
int plat_vencReleaseStream(int32_t vencChn, VEResult *pstVencStream);


#ifdef __cplusplus
}
#endif

#endif /* __PLAT_VENC_H__*/

