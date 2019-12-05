/*
 * protocol.h
 *
 *  Created on: 2016年12月19日
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

#define MAX_CONTENT_LEN  1024   			   //通信内容最大长度，以4个字节对齐
#define MAX_PRINT_LEN    128

//通信帧 2017.3.23增加
#define COMM_FRAME_HEAD (0xAAAAAAAA)
#define COMM_FRAME_TAIL (0x55555555)

#define MAX_FACE_DETECT_NUM  40
/**************************************************************************************
 * 通信格式：
 * 	   同步头        命令头         数据块         数据结束
 *|| tCommSync || tCmdNodeHead || tDataBlock || tDataBlockEnd ||
 *同步头，也就是帧头 帧头标识、通信类型、帧序号、后面数据长度
 *命令头 ，为数据块头，标识数据块中数据结构
 *tDataBlockEnd 为0x55555555，也为同步尾（由帧尾标识）
 *framedata = tCommSync + mCmdNodeHead + tDataBlock
 *framelen = sizeof(tCommSync) + toaldatalen
 *实际处理消息帧长度: sizeof(具体消息结构体大小)即可, 定义在protocol_add.h中
 **************************************************************************************/

/****************************************************************
 * 系统日期时间同步
 * sizeof(tSystemTime)	= 64字节
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
	Pcie_u32t  ms;				 			 //命令发送时时间, 精确到毫秒
	Pcie_u32t  us;         					 //命令发送时时间, 精确到微秒
	Pcie_u32t  isdst;
	Pcie_u32t  reserved[6];
}tSystemTime;


/****************************************
 * 算法类型
 * sizeof(tAlgorithmType)	= 4字节
 ******************************************/
typedef enum Algorithm_type
{
	ALG_TYPE_FD	= 0, 		    			 //人脸检测
	ALG_TYPE_FR, 			    			 //人脸识别
	ALG_TYPE_2, 			
	ALG_TYPE_3, 
}tAlgorithmType;


//2017.7.3增加
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
 * 人脸检测坐标点信息,顺序合围成连通域
 * sizeof(GSFD_Region_com)	= (2*16 + 1) * 4 = 132字节
 ********************************/
#define MAX_GSFD_POINT_NUM 16
typedef struct GSFD_Region_com
{
	int pointNum;		                //点数目
	tPoint Point[MAX_GSFD_POINT_NUM];	//每个点的绝对坐标
}GSFD_Region_Comm;

/************************************
 * 人脸算法配置参数
 * sizeof(tAlgorithmParm_FD) = 132 * 8 + 40
 ************************************/
#define ALG_MAX_FD_REGION_NUM (8)
typedef struct alg_config_fd
{
	GSFD_Region_Comm Region[ALG_MAX_FD_REGION_NUM];// 检测区域指针,与RegionNum配套使用
	int RegionNum;							      // 检测区域数,最大为8
	int maxwidth;							      // 检测最大人脸宽
	int minwidth;							      // 检测最小人脸宽
	int precision;							      // 检测精度,0 - 100
	int sensitivity;						      // 检测灵敏度,0 - 100
	int maxnum;								      // 支持最大检测人脸数目,和平台性能相关
	int im_width;								  // 图片宽度
	int im_heigth;								  //图片 高度
	int stide;                                    //图片行宽度+无效数据
	int res[4];								      // 保留
}tAlgorithmParm_FD;

/////////////////////////人脸检测结果/////////////////////////////////////////////
// 人脸检测结果
typedef struct GSFD_Result_Comm
{
	int Operation;		// 1-新增目标ID, 2-增加目标框， 3-删除目标 4-隐藏状态
	int ID;				// 人脸ID
	int TLen;			// 人脸轨迹长度
//	GSPoint *pPos;		// 人脸轨迹点
	tRect rect;		// 人脸区域

	int score;			/* 人脸检测最佳值得分,100分制,*/
}GSFD_Result_Comm;

//2017.7.3增加
/*************************************
 * 人脸检测算法结果
 * sizeof(tAlgorithmResult_FD)	= 64 * 40字节
 *************************************/
typedef struct algorithm_result_fd
{
	Pcie_u32t channel;                                //通道号
	Pcie_u32t seq;                                    //图片数据帧顺序号
	Pcie_u32t faceCount;        				      //检测到的人脸数
	Pcie_u32t reserved[1];
	GSFD_Result_Comm stFdResult[MAX_FACE_DETECT_NUM]; //图片数据中检测到的人脸数的结果
}tAlgorithmResult_FD;
//////////////////////////////////////////////////////////////////////////////////

/************************************
 * 通信类型
 * CommType_ACK 需要应答 LnkList
 * CommType_NACK 不需要应答
 * CommType_ACK_R 接收应答
 * CommType_NACK_R 接收到非应答
 * sizeof(tCommType) = 4字节
 *************************************/
typedef enum commType
{
	CommType_NACK	= 0,
	CommType_ACK,
	CommType_ACK_R,
	CommType_NACK_R,
}tCommType;


/**************************************
 * sizeof(tPcieCmd) = 4字节 2字节未用+1字节大类+1字节子类
 * 大类划分(十六进制):
 * 0100: general 通用命令(如时间同步,调试信息等)
 * 0200: video 视频相关命令
 * 0300: audio 音频相关命令
 * 0400: encode 编码相关命令
 * 0500: decode 解码相关命令
 * 0600: algorithm 算法相关命令
 * 0700 ~ ff00: 保留
 **************************************/
typedef enum pcieCmd
{
	/* general通用命令 */
	PcieCmd_GEN_DEBUG_INFO       = 0xF0F00100,  //调试打印信息，系统信息和处理信息（执行时间统计等）
	PcieCmd_GEN_PRINT_LEVEL      = 0xF0F00101,  //配置调试打打印级别 2017.06.27
	PcieCmd_GEN_DSPRUN_STATE     = 0xF0F00102,  //DSP系统运行状态
	PcieCmd_GEN_CFG_DATE         = 0xF0F00103,  //配置DSP日期时间
	PcieCmd_GEN_SW_RESET         = 0xF0F00104,  //软复位DSP
	PcieCmd_GEN_TEST             = 0xF0F00105,  //测试帧

	/* video 视频相关命令 */
	PcieCmd_VIDEO_DATA           = 0xF0F00200,  //视频数据
	
	/* audio 音频相关命令 */
	PcieCmd_AUDIO_DATA           = 0xF0F00300,  //音频数据

	/* encode 编码相关命令 */
	PcieCmd_ENC_TYPE             = 0xF0F00400,  //编码类型

	/* decode 解码相关命令 */
	PcieCmd_DEC_TYPE             = 0xF0F00500,  //解码类型

	/* algorithm 算法相关命令 */
	PcieCmd_ALG_IMAGEDATA        = 0xF0F00600,  //图片数据
	PcieCmd_ALG_RESULT_FD        = 0xF0F00601,  //人脸检测算法结果
	PcieCmd_ALG_CONFIG_FD        = 0xF0F00602,  //人脸检测算法配置
	PcieCmd_ALG_RECONFIG_FD      = 0xF0F00603,  //人脸检测算法重配置
	PcieCmd_ALG_START            = 0xF0F00604,  //算法启动
	PcieCmd_ALG_STOP             = 0xF0F00605,  //算法停止
	PcieCmd_ALG_SEND             = 0xF0F00606,  //发送图片或图像数据
	PcieCmd_ALG_DESTROY          = 0xF0F00607,  //算法销毁
}tPcieCmd;


/****************************************************************
 * 数据块头
 * sizeof(tCmdNodeHead) = 12字节
 ******************************************************************/
typedef struct cmdNodeHead
{
	Pcie_u32t	cmd;						//数据块名称 tPcieCmd
	Pcie_u32t	size;						//大小,只计算content的大小
	//2017.6.30删除
/*	Pcie_u32t	globch;						//全局通道号
	Pcie_u32t	chSeq;						//序号,用于和反馈匹配用，按照通道分开
	Pcie_u32t	crc;						//校验,用于校验content,使用crc32, 不满4字节对齐填0,	
	tSystemTime	dt;						//命令发送时日期时间, 精确到毫秒？微秒？
	Pcie_u32t	reserved[11];	*/
	Pcie_u32t	reserved[1];
}tCmdNodeHead;
 
 
/**********************************
 * 同步头 （帧头）
 * sizeof(tCommSync) = 16字节
 *********************************/
typedef struct commSync
{
	Pcie_u32t	commSync;				    //同步信号 0xAAAAAAAA，低字节在前 ，帧头标识
	Pcie_u32t	commType;				    //表示通信类型，详见typedef enum commType
	Pcie_u32t	commSeq;			        //通信序号，用于判断是否新的命令
//	Pcie_u32t	commSize;				    //后面的数据块长度 2017.7.1删除
	Pcie_u32t	commCrc;				    //此字段前期暂时填充4个字节0，不做处理
//	Pcie_u32t	reserved[3];                //2017.6.30删除
} tCommSync;


/*****************************************
 * 调试打印信息
 * sizeof(printfInfoLevel) = 4字节
 *****************************************/
typedef enum 
{
	PRINT_SYS_INFO	= 0, 				    //版本、系统配置 优先级别最高，以下递减
	PRINT_ERROR,        				    //ERROR
	PRINT_WARN,         				    //warn
	PRINT_DEBUG,        				    //DEBUG
	PRINT_OTHER         
}printfInfoLevel;


/*****************************************
 * sizeof(tExeTime) = 8字节
 *****************************************/
typedef struct
{
	Pcie_u32t position; 				    //程序代码段位置
	Pcie_u32t times;    				    //执行时间 以微秒为单位
}tExeTime;


/*****************************************
 * sizeof(tDebugInfo) = 88字节
 *****************************************/
typedef struct
{
	tExeTime statTimes;     		        //执行时间统计
	Pcie_u8t systemInfo[MAX_PRINT_LEN];     //系统信息（错误及警告）
}tDebugInfo;


/*****************************************
 * sizeof(tDspRunState) = 32字节
 *****************************************/										   //DSP端系统运行探测
typedef struct
{
	Pcie_u32t system;      				   //系统运行是否正常，运行一切正常为1，否则为0
	Pcie_u32t reserved[7]; 			       //如果不正常，则在PCIE通讯正常情况返回不正常的功能或模块的标识，功能或模块表暂定，前期调试不使用，以0填充
}tDspRunState;


/*****************************************
 * sizeof(tDataFormat) = 4字节
 *****************************************/	//大块图像数据描述
typedef enum
{
	DataFormat_Y  = 0,  				   //仅仅是Y分量
	DataFormat_YUV,						   //固定一种YUV格式，以ARM端常用格式为准        4:2:0半平面
	DataFormat_OTHERT,
}tDataFormat;


/*****************************************
 * sizeof(tDataDescription) = 32字节
 *****************************************/
typedef struct
{
	Pcie_u32t      channel;                //图片通道号
	Pcie_u32t      algType;     		   //算法类型     tAlgorithmType
	Pcie_u32t      format;      		   //图片或数据格式 如YUV还是仅Y tDataFormat
	Pcie_u32t      strideWidth;       	   //图片或数据行跨度  width + 无效宽度
	Pcie_u32t      strideHeight;  		   //图片或数据列跨度  height + 无效高度
	Pcie_u32t      width;       		   //图片宽度或数据行
	Pcie_u32t      height;      		   //图片高度或数据列
	Pcie_u32t      reserved[1];
}tDataDescription;


/*****************************************
 * sizeof(tOriginalDataDescription) = 40字节
 *****************************************/
typedef struct
{
	Pcie_u32t        startAddr;            //图 数据起始地址
	Pcie_u32t        length;               //图 数据长度
	tDataDescription Description;  	   //数据描述结构 如算法类型、图片分辨率、图片格式
//	void * pDataPtr;      				   //数据块指针 此字段为 ? 缓冲队列管理
}tOriginalDataDescription;


//2017.6.27增加
#include "protocol_add.h"

#ifdef __cplusplus
}
#endif

#endif /* PCIE_DSPCMD_H_ */
