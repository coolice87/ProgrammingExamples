/***********************************************************************
* filename: video_iva.h 
*
* Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
*
* Revisions  : Created on 2016-12-20
* Author: hzgs
*
* Des: iva库和媒体库交互接口
*
**********************************************************************/

#ifndef __VIDEO_IVA_API_H__
#define __VIDEO_IVA_API_H__

#include "Type.h"

#ifdef __cplusplus
extern "C" {
#endif

/*原始数据内存分布格式*/
typedef enum imageformat
{
    Yonly,		/* Y 数据*/
    YUVYUV,		/* YUV间插*/
    YYUVUV,		/* YUV半平面,Y平面UV间插*/
    YYUUVV,		/* YUV平面*/
    YUVUV		/**/
}ImageFormat;

/*数据结构*/
typedef struct VA_IMAG_INFO_s
{
	uint32_t seq;		/* 帧序号*/
	int32_t width;		/* 待分析图片宽度*/
	int32_t height;		/* 待分析图片高度*/
	int32_t stride;		/* 待分析图片跨度*/
	int32_t format;		/* 数据格式,取值ImageFormat*/
	int32_t adapt;		/* 自适应标志,1:表示需要根据图片大小进行自适应,其他不需要*/
	uint8_t *virtAddr;	/* 虚拟地址*/
	uint32_t phyAddr;	/* 物理地址*/
	uint8_t sn[64];     /* 相机id,IPC模式有效*/
	int32_t res[8];		/* 保留*/
}VA_IMAG_INFO_S;

/*帧引用计数*/
typedef struct
{
	uint32_t srcSeq;
	uint32_t refCnt;
	uint32_t res[2];
}FrameRefcnt_S;

/*算法请求媒体库发送图片参数*/
typedef struct RqImageParam
{
	Handle pHandle;		/* 分析器句柄*/
	int32_t chn;		/* 通道号*/
	int32_t chnType;	/* 通道类型,IPC\VI 暂时未用*/
	int32_t width;		/* 待分析图片宽度*/
	int32_t height;		/* 待分析图片高度*/
	int32_t fps;		/* 算法分析要求帧率*/
	int32_t format;		/* 数据格式,取值ImageFormat*/
	int32_t holdNum;	/* 抓图等用途要求的缓存张数,0表示不需要缓存,分析结束立即释放*/
	int32_t res[3];
}RqImageParam;

/*********************************************************************
*函数名:Iva_sendYuvImage()
*功  能:yuv数据送入函数
*入  参:pHandle:分析器句柄,算法转换
*		pImageInfo:数据信息指针
*		len:数据长度
*返回值:0:成功需要保存原始图片  -1:失败 不保存原始图片
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
int Iva_sendYuvImage(Handle pHandle, VA_IMAG_INFO_S *pImageInfo, uint32_t len);

/*********************************************************************
*函数名:Iva_getBigpicSnapStatus()
*功  能:获取ID生存周期内大图编码状态
*入  参:pHandle:分析器句柄,算法转换
*		ID:检测对象ID
*返回值:0:未编码  1:已编码
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
uint32_t Iva_getBigpicSnapStatus(Handle pHandle, uint32_t ID);

/*********************************************************************
*函数名:Iva_setBigpicSnapStatus()
*功  能:设置ID生存周期内大图编码状态,默认状态为未编码,无需设置
*入  参:pHandle:分析器句柄,算法转换
*		ID:检测对象ID
*		status:大图编码状态 0:未编码 1:已编码
*返回值:0:成功需要保存原始图片  -1:失败 不保存原始图片
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
int Iva_setBigpicSnapStatus(Handle pHandle, uint32_t ID, uint32_t status);

/*********************************************************************
*函数名:Iva_RequestImageRegistCBFunc
*功  能:使能逻辑通道
*入  参:pHandle 分析器句柄,内部转化
*		pImageParam 请求数据参数
*		enable:1通道使能
*				0通道关闭	
*返回值:0:成功;-1:失败
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
int Iva_RequestImageRegistCBFunc(int (*IvaRqImageCbFun)(RqImageParam *pImageParam, int enable));

/*********************************************************************
*函数名:Iva_ImageAddrefRegistCBFunc
*功  能:算法库增加原始图片引用回调注册函数
*入  参:pHandle 分析器句柄,内部转化
*		chn 请求数据参数
*		snapCnt:抓图引用次数
*
*返回值:0:成功;-1:失败
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
int Iva_ImageAddSnapRefRegistCBFunc(int (*IvaImageAddSnapRefCbFun)(Handle vaHandle, int chn, uint32_t srcSeq, int snapCnt));


/*********************************************************************
*函数名:Iva_ImageResetRefRegistCBFunc
*功  能:算法库增加原始图片引用回调注册函数
*入  参:pHandle 分析器句柄,内部转化
*		chn 请求数据参数
*		stFrameRef[]:增加引用次数
*		cnt:stFrameRef数组个数
*返回值:0:成功;-1:失败
*---------------------------------------------------------------------
*修改记录:
**********************************************************************/
int Iva_ImageResetRefRegistCBFunc(int (*IvaImageResetRefCbFun)(Handle vaHandle, int chn, FrameRefcnt_S stFrameRef[], int cnt));


#ifdef __cplusplus
}
#endif

#endif
