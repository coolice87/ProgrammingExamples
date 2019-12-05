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
							��������㷨�ṹ����
*******************************************************************************/

/* ���������*/
typedef struct GSFD_Handle
{
	unsigned char *pBuffer;	/* �������ʹ���ڴ�*/
	int buflen;				/* buf����*/
	int useLen;

	int width;				/* ����ͼ��Ŀ�*/
	int height;				/* ����ͼ��ĸ�*/
	int stide;				/* ͼ����*/
}GSFD_Handle;


/*�����ṹ��*/
typedef struct GSFD_Point
{
	int x;
	int y;
}GSFD_Point;

/*���νṹ��*/
typedef struct GSFD_Rect 
{
	int x;
	int y;
	int w;
	int h;
}GSFD_Rect;

/*��������������Ϣ,˳���Χ����ͨ��*/
typedef struct GSFD_Region
{
	int pointNum;		/*����Ŀ*/
	GSFD_Point *pPoint;	/*ÿ����ľ�������*/
}GSFD_Region;

#define ALG_MAX_FD_REGION_NUM (8)

/* ����������*/
typedef struct GSFD_Param
{
	GSFD_Region Region[ALG_MAX_FD_REGION_NUM];	/* �������ָ��,��RegionNum����ʹ��*/
	int RegionNum;							/* ���������,���Ϊ8*/
	int maxwidth;							/* ������������*/
	int minwidth;							/* �����С������*/
	int precision;							/* ��⾫��,0 - 100*/
	int sensitivity;						/* ���������,0 - 100*/
	int maxnum;								/* ֧�������������Ŀ,��ƽ̨�������*/
	int rectratio;							/* �ϱ�������ߴ��Ȱٷֱ�,100-200,����ʡ��%,Ĭ��140*/
	int res[3];								/* ����*/
}GSFD_Param;

/* Ĭ������������*/
typedef struct GSFD_DefaultParam
{
	int maxRectNum;			/* ���֧�ּ��������*/
	int maxWidth;			/* ������������,����ֵ*/
	int minWidth;			/* �����С������,����ֵ*/
	int precision;			/* ��⾫��,0 - 100*/
	int sensitivity;		/* ���������,0 - 100*/
	int scoreThr;			/* Ĭ�Ϸ�����ֵ,0 - 100*/
	int maxNum;				/* ֧�������������Ŀ,��ƽ̨�������*/
	int rectratio;			/* �ϱ�������ߴ��Ȱٷֱ�,100-200,����ʡ��%,Ĭ��140*/
	int res[4];				/* ����*/
}GSFD_DefaultParam;


/* ���������*/
typedef struct GSFD_Result 
{
	int Operation;		/* 1-����Ŀ��ID, 2-����Ŀ��� 3-ɾ��Ŀ�� 4-����״̬*/
	int ID;				/* ����ID*/
	int TLen;			/* �����켣����*/
//	GSPoint *pPos;		/* �����켣��*/
	GSFD_Rect rect;		/* ��������*/
	
	int score;			/* ����������ֵ�÷�,100����,*/
}GSFD_Result;


/**********************************************************************************
						��������㷨����������
**********************************************************************************/

/************************************************************************
�������ܣ�                 ��������������
���룺
	pFDHandle              ���������
	pFDParam               ����������
�����                     ��
���أ�                     0--�ɹ� -1--ʧ��                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdSetConfig(GSFD_Handle *pFDHandle, GSFD_Param *pFDParam);

/************************************************************************
�������ܣ�                 ��ȡ��ǰ������
���룺
	pFDHandle              ���������
�����                       
	pFDParam               ����������
���أ�                     0--�ɹ� -1--ʧ��                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdGetConfig(GSFD_Handle *pFDHandle, GSFD_Param *pFDParam);

/************************************************************************
�������ܣ�                 ��ȡ��ǰ���Ĭ�ϲ���
���룺
	pFDHandle              ���������
�����                       
	pFDParam               �������Ĭ�ϲ���
���أ�                     0--�ɹ� -1--ʧ��                                                                      
************************************************************************/
int GS_EXPORTS Alg_FdGetDefaultParam(GSFD_Handle *pFDHandle, GSFD_DefaultParam *pFDParam);


/************************************************************************
�������ܣ�                �������������Ҫ�ڴ�
���룺
	pFDParam              ����������
�����                    ��
���أ�                    �ڴ��С
************************************************************************/
int GS_EXPORTS Alg_FdCalcMemSize(GSFD_Handle *pFDHandle);

/************************************************************************
�������ܣ�                 ��������ʼ��
���룺
	pFDHandle              ���������
	pFDModelPath           �������ģ��·��
�����                     ��
���أ�                     0--�ɹ� -1--ʧ��
************************************************************************/
int GS_EXPORTS Alg_FdInit(GSFD_Handle *pFDHandle, char *pFDModelPath);

/************************************************************************
�������ܣ� 		�������ȥ��ʼ��
���룺
	pFDHandle 	���������
�����			��
����: 			0--�ɹ� -1--ʧ��
************************************************************************/
int GS_EXPORTS Alg_FdDeInit(GSFD_Handle *pFDHandle);

/************************************************************************
�������ܣ�				������������ݲ���ȡ�����
���룺
	pFDHandle[in]		���������
	pGrayImage[in]		�Ҷ�ͼ������ָ��
	pFDResult[out]		������������С��������������������,�ڴ��ɵ���������
	
���أ�                  ��⵽������Ŀ(>=0)��-1ʧ��
************************************************************************/
int GS_EXPORTS Alg_FdProcess_CodeStream(GSFD_Handle *pFDHandle, unsigned char *pGrayImage, GSFD_Result pFDResult[]);

/************************************************************************
�������ܣ�				������������ݲ���ȡ�����
���룺
pFDHandle[in]		���������
pMajor[out]			���汾��,�ش�Ķ��汾������
pMinor[out]			�ΰ汾��,С�Ķ��汾������
pSvn[out]			svn �汾��
���أ�              0--�ɹ� -1--ʧ��
************************************************************************/
int GS_EXPORTS Alg_FdGetVersion(GSFD_Handle *pFDHandle, unsigned int *pMajor, unsigned int *pMinor, unsigned int *pSvn);


#ifdef __cplusplus
}
#endif

#endif
