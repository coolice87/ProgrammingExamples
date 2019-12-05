/********************************************************************************
 * ** Copyright (C) 1992-2011, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : pcie_dev.c
 * ** Desc          : operate interface of pcie device
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_06_22
 * ********************************************************************************/

/*------------------------------ include header file ------------------------*/
#include "common.h"
#include "pcie_mcc.h"
#include "pcie_msg.h"

/*------------------------------ macro definitin ----------------------------*/

/*------------------------------ global variables ---------------------------*/

/*------------------------------ local variables ----------------------------*/

/*------------------------------ declararion --------------------------------*/

/*------------------------------ functions interface ------------------------*/
/*************************************************************
 **  函数名称:   pcie_get_remoteid
 **  功能说明:   获取PCIE从设备ID
 **  入参    :   none
 **  出参    :   1.remote_id: 从设备ID
 **              2.count: 获取到的总共设备
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_get_remoteid(int32_t *remote_id, int32_t *count)
{
	int fd;
	int i;
	struct mcc_handle_attr attr;

	fd = open(MCC_USR_DEV, O_RDWR);
	if(fd <= 0)
	{
		PCIE_ERR("open %s failed\n", MCC_USR_DEV);
		return -1;
	}

	/* HI_MCC_IOC_ATTR_INIT should be sent first ! */
	if (ioctl(fd, HI_MCC_IOC_ATTR_INIT, &attr))
	{    
		PCIE_ERR("initialization for attr failed!\n");
		goto fail;
	}

	if (ioctl(fd, HI_MCC_IOC_GET_REMOTE_ID, &attr))
	{    
		PCIE_ERR("get pci remote id fail \n");
		goto fail;
	}    

	for (i=0; i<PCIE_MAX_CHIPNUM-1; i++) 
	{    
		if (-1 == attr.remote_id[i]) break;
		remote_id[i] = attr.remote_id[i];
		PCIE_MSG("get pci remote id : %d \n", attr.remote_id[i]);
	}    
	*count = i; 

	close(fd);
	return 0;
fail:
	close(fd);
	return -1;
}

/*************************************************************
 **  函数名称:   pcie_get_localid
 **  功能说明:   获取PCIE 本地ID
 **  入参    :   none
 **  出参    :   1.remote_id: 本设备ID
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_get_localid(int32_t *local_id)
{
	int fd;
	struct mcc_handle_attr attr;

	fd = open(MCC_USR_DEV, O_RDWR);
	if(fd <= 0)
	{
		PCIE_ERR("open %s failed\n", MCC_USR_DEV);
		return -1;
	}

	/* HI_MCC_IOC_ATTR_INIT should be sent first ! */
	if (ioctl(fd, HI_MCC_IOC_ATTR_INIT, &attr))
	{    
		PCIE_ERR("initialization for attr failed!\n");
		goto fail;
	}

	*local_id = ioctl(fd, HI_MCC_IOC_GET_LOCAL_ID, &attr);
	PCIE_MSG("pci local id is %d \n", *local_id);

	close(fd);
	return 0;
fail:
	close(fd);
	return -1;
}

