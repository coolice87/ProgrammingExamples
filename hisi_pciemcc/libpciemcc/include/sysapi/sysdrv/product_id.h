/********************************************************************************
 * ** Copyright (C) 2015-2020, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : product_id.h
 * ** Desc          : ���ݲ�ƷID��������
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_04_19
 * ********************************************************************************/
#ifndef _PRODUCT_ID_H
#define _PRODUCT_ID_H

/* ###########################################################################
 * ���ֹ���:
 * 32λö��: 31...24    23...16    15...0   0x00000000��0xffffffff��ʹ��
 *           1byte���� 1byte���� 2byte�����ͺ�
 * ����:
 * 		0x01: IVS
 * 		0x02: IPC
 * IVS����:
 * 		0x01: FD
 * 		0x02: FR
 * 		0x03: VI
 * FD�����ͺ�:
 * 		0x0001: 0601A
 * example:
 * PRODUCT_ID_IVSFD0601 = 0x01010001
 * PRODUCT_SUBTYPE_IVS_FD = 0x01010000
 * ########################################################################*/

/* ���֧��6�� */
#define MAX_ITEM_NUM        6
typedef enum produc_items
{
	PRODUCT_ITEM_COMPANY = 0,  //GC, XX ..
	PRODUCT_ITEM_TYPE = 1,     //IVS, IPC ..
	PRODUCT_ITEM_SUBTYPE = 2,  //FD0601A FD0602A ...
	PRODUCT_ITEM_VERSION = 3,  //V100 ...
}PRODUCT_ITEMS_E;

typedef enum product_id
{
	/****************** class IVS ************ */
	PRODUCT_ID_UNKNOWN = 0x00000000,
	/* 0x01010001 ~ 0x0101ffff IVS-FD ��Ʒ�ͺ� */
	PRODUCT_ID_IVSFD0601 = 0x01010001,
	PRODUCT_ID_IVSFD0602 = 0x01010002,
	PRODUCT_ID_IVSFD0204 = 0x01010003,
	PRODUCT_ID_IVSFD0208 = 0x01010004,
	PRODUCT_ID_IVSFD1201 = 0x01010005,
	/* 0x01020001 ~ 0x0102ffff IVS-FR ��Ʒ�ͺ� */
	PRODUCT_ID_IVSFR0601 = 0x01020001,
	/* 0x01030001 ~ 0x0103ffff IVS-VI ��Ʒ�ͺ� */
	PRODUCT_ID_IVSVI0601 = 0x01030001,

	PRODUCT_ID_END = 0xffffffff
}PRODUCT_ID_E;

#define PRODUCT_SUBTYPE_MASK 		0xffff0000
typedef enum product_subtype
{
	PRODUCT_SUBTYPE_UNKNOWN = 0x00000000,
	/* 0x01010001 ~ 0x0101ffff IVS-FD ��Ʒ�ͺ� */
	PRODUCT_SUBTYPE_IVS_FD = 0x01010000,
	/* 0x01010001 ~ 0x0101ffff IVS-FR ��Ʒ�ͺ� */
	PRODUCT_SUBTYPE_IVS_FR = 0x01020000,
	/* 0x01010001 ~ 0x0101ffff IVS-VI ��Ʒ�ͺ� */
	PRODUCT_SUBTYPE_IVS_VI = 0x01030000,

	PRODUCT_SUBTYPE_END = 0xffffffff
}PRODUCT_SUBTYPE_E;

/* ��ȡ��Ϣ�ṹ�� */
#define MAX_LEN_PER_ITEM    16
typedef struct product_info
{
	uint32_t item_num; ///��Ϣ��Ŀ��
	/* ��ά����,ÿ���������ݶ��������ö��,��һά����ʹ��ö��ֵ(info[PRODUCT_ITEM_TYPE][MAX_LEN_PER_ITEM]) */
	char info[MAX_ITEM_NUM][MAX_LEN_PER_ITEM];
	uint32_t id; ///ÿ����ƷID, Ӧ����ʱ�ò���,��Ƶ��ʹ��
	uint32_t subtype; ///��Ʒ���ࣺFD\FR\VI��
	uint8_t reserved[20];
}PRODUCT_INFO_ST;

/* return: -1 failed, 0: success */
int get_product_info(PRODUCT_INFO_ST *pinfo);

#endif


