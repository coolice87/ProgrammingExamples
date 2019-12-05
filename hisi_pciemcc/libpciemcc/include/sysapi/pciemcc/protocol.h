/*
 * protocol.h
 *
 *  Created on: 2016��12��19��
 *      Author: lxs
 */

#ifndef PCIE_DSPCMD_H_
#define PCIE_DSPCMD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>

#include "protocolTypeDef.h"

#define MAX_CONTENT_LEN  1024   			   //ͨ��������󳤶ȣ���4���ֽڶ���
#define MAX_PRINT_LEN    128

//ͨ��֡ 2017.3.23����
#define COMM_FRAME_HEAD (0xAAAAAAAA)
#define COMM_FRAME_TAIL (0x55555555)

#define MAX_FACE_DETECT_NUM  40
/**************************************************************************************
 * ͨ�Ÿ�ʽ��
 * 	   ͬ��ͷ        ����ͷ         ���ݿ�         ���ݽ���
 *|| tCommSync || tCmdNodeHead || tDataBlock || tDataBlockEnd ||
 *ͬ��ͷ��Ҳ����֡ͷ ֡ͷ��ʶ��ͨ�����͡�֡��š��������ݳ���
 *����ͷ ��Ϊ���ݿ�ͷ����ʶ���ݿ������ݽṹ
 *tDataBlockEnd Ϊ0x55555555��ҲΪͬ��β����֡β��ʶ��
 *framedata = tCommSync + mCmdNodeHead + tDataBlock
 *framelen = sizeof(tCommSync) + toaldatalen
 *ʵ�ʴ�����Ϣ֡����: sizeof(������Ϣ�ṹ���С)����, ������protocol_add.h��
 **************************************************************************************/

/****************************************************************
 * ϵͳ����ʱ��ͬ��
 * sizeof(tSystemTime)	= 64�ֽ�
 ****************************************************************/
typedef struct tagSYSTEM_TIME
{
	Pcie_u32t  year;
	Pcie_u32t  month;
	Pcie_u32t  day;
	Pcie_u32t  wday;
	Pcie_u32t  hour;
	Pcie_u32t  minute;
	Pcie_u32t  second;
	Pcie_u32t  ms;				 			 //�����ʱʱ��, ��ȷ������
	Pcie_u32t  us;         					 //�����ʱʱ��, ��ȷ��΢��
	Pcie_u32t  isdst;
	Pcie_u32t  reserved[6];
}tSystemTime;


/****************************************
 * �㷨����
 * sizeof(tAlgorithmType)	= 4�ֽ�
 ******************************************/
typedef enum Algorithm_type
{
	ALG_TYPE_FD	= 0, 		    			 //�������
	ALG_TYPE_FR, 			    			 //����ʶ��
	ALG_TYPE_2, 			
	ALG_TYPE_3, 
}tAlgorithmType;


//2017.7.3����
typedef struct _Point_t
{
	int x;
	int y;
}tPoint;

typedef struct _rect_t
{
	int x;
	int y;
	int w;
	int h;
}tRect;

/********************************
 * ��������������Ϣ,˳���Χ����ͨ��
 * sizeof(GSFD_Region_com)	= (2*16 + 1) * 4 = 132�ֽ�
 ********************************/
#define MAX_GSFD_POINT_NUM 16
typedef struct GSFD_Region_com
{
	int pointNum;		                //����Ŀ
	tPoint Point[MAX_GSFD_POINT_NUM];	//ÿ����ľ�������
}GSFD_Region_Comm;

/************************************
 * �����㷨���ò���
 * sizeof(tAlgorithmParm_FD) = 132 * 8 + 40
 ************************************/
#define ALG_MAX_FD_REGION_NUM (8)
typedef struct alg_config_fd
{
	GSFD_Region_Comm Region[ALG_MAX_FD_REGION_NUM];// �������ָ��,��RegionNum����ʹ��
	int RegionNum;							      // ���������,���Ϊ8
	int maxwidth;							      // ������������
	int minwidth;							      // �����С������
	int precision;							      // ��⾫��,0 - 100
	int sensitivity;						      // ���������,0 - 100
	int maxnum;								      // ֧�������������Ŀ,��ƽ̨�������
	int im_width;								  // ͼƬ���
	int im_heigth;								  //ͼƬ �߶�
	int stide;                                    //ͼƬ�п��+��Ч����
	int res[4];								      // ����
}tAlgorithmParm_FD;

/////////////////////////���������/////////////////////////////////////////////
// ���������
typedef struct GSFD_Result_Comm
{
	int Operation;		// 1-����Ŀ��ID, 2-����Ŀ��� 3-ɾ��Ŀ�� 4-����״̬
	int ID;				// ����ID
	int TLen;			// �����켣����
//	GSPoint *pPos;		// �����켣��
	tRect rect;		// ��������

	int score;			/* ����������ֵ�÷�,100����,*/
}GSFD_Result_Comm;

//2017.7.3����
/*************************************
 * ��������㷨���
 * sizeof(tAlgorithmResult_FD)	= 64 * 40�ֽ�
 *************************************/
typedef struct algorithm_result_fd
{
	Pcie_u32t channel;                                //ͨ����
	Pcie_u32t seq;                                    //ͼƬ����֡˳���
	Pcie_u32t faceCount;        				      //��⵽��������
	Pcie_u32t reserved[1];
	GSFD_Result_Comm stFdResult[MAX_FACE_DETECT_NUM]; //ͼƬ�����м�⵽���������Ľ��
}tAlgorithmResult_FD;
//////////////////////////////////////////////////////////////////////////////////

/************************************
 * ͨ������
 * CommType_ACK ��ҪӦ�� LnkList
 * CommType_NACK ����ҪӦ��
 * CommType_ACK_R ����Ӧ��
 * CommType_NACK_R ���յ���Ӧ��
 * sizeof(tCommType) = 4�ֽ�
 *************************************/
typedef enum commType
{
	CommType_NACK	= 0,
	CommType_ACK,
	CommType_ACK_R,
	CommType_NACK_R,
}tCommType;


/**************************************
 * sizeof(tPcieCmd) = 4�ֽ� 2�ֽ�δ��+1�ֽڴ���+1�ֽ�����
 * ���໮��(ʮ������):
 * 0100: general ͨ������(��ʱ��ͬ��,������Ϣ��)
 * 0200: video ��Ƶ�������
 * 0300: audio ��Ƶ�������
 * 0400: encode �����������
 * 0500: decode �����������
 * 0600: algorithm �㷨�������
 * 0700 ~ ff00: ����
 **************************************/
typedef enum pcieCmd
{
	/* generalͨ������ */
	PcieCmd_GEN_DEBUG_INFO       = 0xF0F00100,  //���Դ�ӡ��Ϣ��ϵͳ��Ϣ�ʹ�����Ϣ��ִ��ʱ��ͳ�Ƶȣ�
	PcieCmd_GEN_PRINT_LEVEL      = 0xF0F00101,  //���õ��Դ��ӡ���� 2017.06.27
	PcieCmd_GEN_DSPRUN_STATE     = 0xF0F00102,  //DSPϵͳ����״̬
	PcieCmd_GEN_CFG_DATE         = 0xF0F00103,  //����DSP����ʱ��
	PcieCmd_GEN_SW_RESET         = 0xF0F00104,  //��λDSP
	PcieCmd_GEN_TEST             = 0xF0F00105,  //����֡

	/* video ��Ƶ������� */
	PcieCmd_VIDEO_DATA           = 0xF0F00200,  //��Ƶ����
	
	/* audio ��Ƶ������� */
	PcieCmd_AUDIO_DATA           = 0xF0F00300,  //��Ƶ����

	/* encode ����������� */
	PcieCmd_ENC_TYPE             = 0xF0F00400,  //��������

	/* decode ����������� */
	PcieCmd_DEC_TYPE             = 0xF0F00500,  //��������

	/* algorithm �㷨������� */
	PcieCmd_ALG_IMAGEDATA        = 0xF0F00600,  //ͼƬ����
	PcieCmd_ALG_RESULT_FD        = 0xF0F00601,  //��������㷨���
	PcieCmd_ALG_CONFIG_FD        = 0xF0F00602,  //��������㷨����
	PcieCmd_ALG_RECONFIG_FD      = 0xF0F00603,  //��������㷨������
	PcieCmd_ALG_START            = 0xF0F00604,  //�㷨����
	PcieCmd_ALG_STOP             = 0xF0F00605,  //�㷨ֹͣ
	PcieCmd_ALG_SEND             = 0xF0F00606,  //����ͼƬ��ͼ������
	PcieCmd_ALG_DESTROY          = 0xF0F00607,  //�㷨����
}tPcieCmd;


/****************************************************************
 * ���ݿ�ͷ
 * sizeof(tCmdNodeHead) = 12�ֽ�
 ******************************************************************/
typedef struct cmdNodeHead
{
	Pcie_u32t	cmd;						//���ݿ����� tPcieCmd
	Pcie_u32t	size;						//��С,ֻ����content�Ĵ�С
	//2017.6.30ɾ��
/*	Pcie_u32t	globch;						//ȫ��ͨ����
	Pcie_u32t	chSeq;						//���,���ںͷ���ƥ���ã�����ͨ���ֿ�
	Pcie_u32t	crc;						//У��,����У��content,ʹ��crc32, ����4�ֽڶ�����0,	
	tSystemTime	dt;						//�����ʱ����ʱ��, ��ȷ�����룿΢�룿
	Pcie_u32t	reserved[11];	*/
	Pcie_u32t	reserved[1];
}tCmdNodeHead;
 
 
/**********************************
 * ͬ��ͷ ��֡ͷ��
 * sizeof(tCommSync) = 16�ֽ�
 *********************************/
typedef struct commSync
{
	Pcie_u32t	commSync;				    //ͬ���ź� 0xAAAAAAAA�����ֽ���ǰ ��֡ͷ��ʶ
	Pcie_u32t	commType;				    //��ʾͨ�����ͣ����typedef enum commType
	Pcie_u32t	commSeq;			        //ͨ����ţ������ж��Ƿ��µ�����
//	Pcie_u32t	commSize;				    //��������ݿ鳤�� 2017.7.1ɾ��
	Pcie_u32t	commCrc;				    //���ֶ�ǰ����ʱ���4���ֽ�0����������
//	Pcie_u32t	reserved[3];                //2017.6.30ɾ��
} tCommSync;


/*****************************************
 * ���Դ�ӡ��Ϣ
 * sizeof(printfInfoLevel) = 4�ֽ�
 *****************************************/
typedef enum 
{
	PRINT_SYS_INFO	= 0, 				    //�汾��ϵͳ���� ���ȼ�����ߣ����µݼ�
	PRINT_ERROR,        				    //ERROR
	PRINT_WARN,         				    //warn
	PRINT_DEBUG,        				    //DEBUG
	PRINT_OTHER         
}printfInfoLevel;


/*****************************************
 * sizeof(tExeTime) = 8�ֽ�
 *****************************************/
typedef struct
{
	Pcie_u32t position; 				    //��������λ��
	Pcie_u32t times;    				    //ִ��ʱ�� ��΢��Ϊ��λ
}tExeTime;


/*****************************************
 * sizeof(tDebugInfo) = 88�ֽ�
 *****************************************/
typedef struct
{
	tExeTime statTimes;     		        //ִ��ʱ��ͳ��
	Pcie_u8t systemInfo[MAX_PRINT_LEN];     //ϵͳ��Ϣ�����󼰾��棩
}tDebugInfo;


/*****************************************
 * sizeof(tDspRunState) = 32�ֽ�
 *****************************************/										   //DSP��ϵͳ����̽��
typedef struct
{
	Pcie_u32t system;      				   //ϵͳ�����Ƿ�����������һ������Ϊ1������Ϊ0
	Pcie_u32t reserved[7]; 			       //���������������PCIEͨѶ����������ز������Ĺ��ܻ�ģ��ı�ʶ�����ܻ�ģ����ݶ���ǰ�ڵ��Բ�ʹ�ã���0���
}tDspRunState;


/*****************************************
 * sizeof(tDataFormat) = 4�ֽ�
 *****************************************/	//���ͼ����������
typedef enum
{
	DataFormat_Y  = 0,  				   //������Y����
	DataFormat_YUV,						   //�̶�һ��YUV��ʽ����ARM�˳��ø�ʽΪ׼        4:2:0��ƽ��
	DataFormat_OTHERT,
}tDataFormat;


/*****************************************
 * sizeof(tDataDescription) = 32�ֽ�
 *****************************************/
typedef struct
{
	Pcie_u32t      channel;                //ͼƬͨ����
	Pcie_u32t      algType;     		   //�㷨����     tAlgorithmType
	Pcie_u32t      format;      		   //ͼƬ�����ݸ�ʽ ��YUV���ǽ�Y tDataFormat
	Pcie_u32t      strideWidth;       	   //ͼƬ�������п��  width + ��Ч���
	Pcie_u32t      strideHeight;  		   //ͼƬ�������п��  height + ��Ч�߶�
	Pcie_u32t      width;       		   //ͼƬ��Ȼ�������
	Pcie_u32t      height;      		   //ͼƬ�߶Ȼ�������
	Pcie_u32t      reserved[1];
}tDataDescription;


/*****************************************
 * sizeof(tOriginalDataDescription) = 40�ֽ�
 *****************************************/
typedef struct
{
	Pcie_u32t        startAddr;            //ͼ ������ʼ��ַ
	Pcie_u32t        length;               //ͼ ���ݳ���
	tDataDescription Description;  	   //���������ṹ ���㷨���͡�ͼƬ�ֱ��ʡ�ͼƬ��ʽ
//	void * pDataPtr;      				   //���ݿ�ָ�� ���ֶ�Ϊ ? ������й���
}tOriginalDataDescription;


//2017.6.27����
#include "protocol_add.h"

#ifdef __cplusplus
}
#endif

#endif /* PCIE_DSPCMD_H_ */
