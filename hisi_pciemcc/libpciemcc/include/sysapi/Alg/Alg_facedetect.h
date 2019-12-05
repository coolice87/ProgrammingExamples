/*******************************************************************************
* Alg_facedetect.h
*
* Copyright (c) 2016, HzGosun,  All rights reserved.
*
* Description:  
* Revisions  : Created on 2016-12-10
* Author: 
*
* Desc: 			Alg_FdCalcMemSize
*						|
*					Alg_FdInit 
*						|
*					Alg_FdSetConfig Alg_FdGetConfig
*						|
*					Alg_FdProcess_CodeStream
*						|
*					Alg_FdDeInit
*
* Modification: 
* 1. Date    : 
*    Revision: 
*    Author  : 
*    Contents: 
*
*******************************************************************************/

#ifndef _ALG_FACEDETECT_H_
#define _ALG_FACEDETECT_H_

#if (defined WIN32 || defined WIN64)
#  define GS_EXPORTS __declspec(dllexport)
#else
#  define GS_EXPORTS
#endif

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************
							人脸检测算法结构定义
*******************************************************************************/

/* 人脸检测句柄*/
typedef struct GSFD_Handle
{
	unsigned char *pBuffer;	/* 人脸检测使用内存*/
	int buflen;				/* buf长度*/
	int useLen;

	int width;				/* 分析图像的宽*/
	int height;				/* 分析图像的高*/
	int stide;				/* 图像跨距*/
}GSFD_Handle;


/*坐标点结构体*/
typedef struct GSFD_Point
{
	int x;
	int y;
}GSFD_Point;

/*矩形结构体*/
typedef struct GSFD_Rect 
{
	int x;
	int y;
	int w;
	int h;
}GSFD_Rect;

/*人脸检测坐标点信息,顺序合围成连通域*/
typedef struct GSFD_Region
{
	int pointNum;		/*点数目*/
	GSFD_Point *pPoint;	/*每个点的绝对坐标*/
}GSFD_Region;

#define ALG_MAX_FD_REGION_NUM (8)

/* 人脸检测参数*/
typedef struct GSFD_Param
{
	GSFD_Region Region[ALG_MAX_FD_REGION_NUM];	/* 检测区域指针,与RegionNum配套使用*/
	int RegionNum;							/* 检测区域数,最大为8*/
	int maxwidth;							/* 检测最大人脸宽*/
	int minwidth;							/* 检测最小人脸宽*/
	int precision;							/* 检测精度,0 - 100*/
	int sensitivity;						/* 检测灵敏度,0 - 100*/
	int maxnum;								/* 支持最大检测人脸数目,和平台性能相关*/
	int rectratio;							/* 上报人脸框尺寸宽度百分比,100-200,参数省略%,默认140*/
	int res[3];								/* 保留*/
}GSFD_Param;

/* 默认人脸检测参数*/
typedef struct GSFD_DefaultParam
{
	int maxRectNum;			/* 最大支持检测区域数*/
	int maxWidth;			/* 检测最大人脸宽,像素值*/
	int minWidth;			/* 检测最小人脸宽,像素值*/
	int precision;			/* 检测精度,0 - 100*/
	int sensitivity;		/* 检测灵敏度,0 - 100*/
	int scoreThr;			/* 默认分数阈值,0 - 100*/
	int maxNum;				/* 支持最大检测人脸数目,和平台性能相关*/
	int rectratio;			/* 上报人脸框尺寸宽度百分比,100-200,参数省略%,默认140*/
	int res[4];				/* 保留*/
}GSFD_DefaultParam;


/* 人脸检测结果*/
typedef struct GSFD_Result 
{
	int Operation;		/* 1-新增目标ID, 2-增加目标框， 3-删除目标 4-隐藏状态*/
	int ID;				/* 人脸ID*/
	int TLen;			/* 人脸轨迹长度*/
//	GSPoint *pPos;		/* 人脸轨迹点*/
	GSFD_Rect rect;		/* 人脸区域*/
	
	int score;			/* 人脸检测最佳值得分,100分制,*/
}GSFD_Result;


/**********************************************************************************
						人脸检测算法函数定义区
**********************************************************************************/

/************************************************************************
函数功能：                 人脸检测参数设置
输入：
	pFDHandle              人脸检测句柄
	pFDParam               人脸检测参数
输出：                     无
返回：                     0--成功 -1--失败                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdSetConfig(GSFD_Handle *pFDHandle, GSFD_Param *pFDParam);

/************************************************************************
函数功能：                 获取当前检测参数
输入：
	pFDHandle              人脸检测句柄
输出：                       
	pFDParam               人脸检测参数
返回：                     0--成功 -1--失败                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdGetConfig(GSFD_Handle *pFDHandle, GSFD_Param *pFDParam);

/************************************************************************
函数功能：                 获取当前检测默认参数
输入：
	pFDHandle              人脸检测句柄
输出：                       
	pFDParam               人脸检测默认参数
返回：                     0--成功 -1--失败                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdGetDefaultParam(GSFD_Handle *pFDHandle, GSFD_DefaultParam *pFDParam);


/************************************************************************
函数功能：                计算人脸检测需要内存
输入：
	pFDParam              人脸检测参数
输出：                    无
返回：                    内存大小
************************************************************************/
int GS_EXPORTS Alg_FdCalcMemSize(GSFD_Handle *pFDHandle);

/************************************************************************
函数功能：                 人脸检测初始化
输入：
	pFDHandle              人脸检测句柄
	pFDModelPath           人脸检测模型路径
输出：                     无
返回：                     0--成功 -1--失败
************************************************************************/
int GS_EXPORTS Alg_FdInit(GSFD_Handle *pFDHandle, char *pFDModelPath);

/************************************************************************
函数功能： 		人脸检测去初始化
输入：
	pFDHandle 	人脸检测句柄
输出：			无
返回: 			0--成功 -1--失败
************************************************************************/
int GS_EXPORTS Alg_FdDeInit(GSFD_Handle *pFDHandle);

/************************************************************************
函数功能：				人脸检测送数据并获取检测结果
输入：
	pFDHandle[in]		人脸检测句柄
	pGrayImage[in]		灰度图像数据指针
	pFDResult[out]		检测结果，数组大小不超过设参中最大人脸数,内存由调用者申请
	
返回：                  检测到人脸数目(>=0)，-1失败
************************************************************************/
int GS_EXPORTS Alg_FdProcess_CodeStream(GSFD_Handle *pFDHandle, unsigned char *pGrayImage, GSFD_Result pFDResult[]);

/************************************************************************
函数功能：				人脸检测送数据并获取检测结果
输入：
pFDHandle[in]		人脸检测句柄
pMajor[out]			主版本号,重大改动版本号增加
pMinor[out]			次版本号,小改动版本号增加
pSvn[out]			svn 版本号
返回：              0--成功 -1--失败
************************************************************************/
int GS_EXPORTS Alg_FdGetVersion(GSFD_Handle *pFDHandle, unsigned int *pMajor, unsigned int *pMinor, unsigned int *pSvn);


#ifdef __cplusplus
}
#endif

#endif
