/********************************************************************************
 * ** Copyright (C) 1992-2011, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : pcie_msg.c
 * ** Desc          : operate interface of pcie message
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_06_22
 * ********************************************************************************/

/*------------------------------ include header file ------------------------*/
#include "common.h"
#include "protocol.h"
#include "pcie_mcc.h"
#include "pcie_msg.h"

/*------------------------------ macro definitin ----------------------------*/

/*------------------------------ global variables ---------------------------*/

/*------------------------------ local variables ----------------------------*/
static int msg_fd[PCIE_MAX_CHIPNUM][PCIE_MSG_MAX_PORT_NUM+1];

/*------------------------------ declararion --------------------------------*/

/*------------------------------ functions interface ------------------------*/
/*************************************************************
 **  函数名称:   pcie_wait_connect
 **  功能说明:   与从设备建立连接
 **  入参    :   1. target_id: 从设备ID
 **  出参    :   none
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_wait_connect(int32_t target_id)
{
	int32_t fd;
	int32_t retry;
	struct mcc_handle_attr attr;

	fd = open(MCC_USR_DEV, O_RDWR);
	if (fd <= 0)
	{
		PCIE_ERR("open pci msg dev fail!\n");
		return -1;
	}

	if (ioctl(fd, HI_MCC_IOC_ATTR_INIT, &attr))
	{
		PCIE_ERR("initialization for attr failed!\n");
		goto fail;
	}

	attr.target_id = target_id;
	PCIE_MSG("start check pci target id:%d  ... ... ... \n", target_id);
	retry = 0;
	while (ioctl(fd, HI_MCC_IOC_CHECK, &attr))
	{
		usleep(10000);
		retry++;
		if(retry >= 10)
			break;
	}
	if(retry >= 10)
	{
		PCIE_ERR("check timeout\n");
		goto fail;
	}
	else
		PCIE_MSG("have checked pci target id:%d ok ! \n", target_id);

	attr.port      = 1000;
	attr.priority  = 0;
	if(ioctl(fd, HI_MCC_IOC_CONNECT, &attr))
	{
		PCIE_ERR("connect failed\n");
		goto fail;
	}
	/* check target chip whether is start up, */

	close(fd);
	return 0;
fail:
	close(fd);
	return -1;
}

/*************************************************************
 **  函数名称:   pcie_open_msgport
 **  功能说明:   打开消息端口
 **  入参    :   1. target_id: 从设备ID
 ** 			 2. port: 消息端口
 **  出参    :   none
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_open_msgport(int32_t target_id, int32_t port)
{
	int32_t ret = 0;
	struct mcc_handle_attr attr;
	int32_t fd;

	if (target_id >= PCIE_MAX_CHIPNUM || port >= PCIE_MSG_MAX_PORT)
	{
		PCIE_ERR("invalid pci msg port(%d,%d)!\n", target_id, port);
		return -1;
	}

	if (msg_fd[target_id][port-PCIE_MSG_BASE_PORT] > 0)
	{
		PCIE_MSG("pci msg port(%d,%d) have open!\n", target_id, port);
		return 0;
	}

	fd = open(MCC_USR_DEV, O_RDWR);
	if (fd <= 0)
	{
		PCIE_ERR("open pci msg dev fail!\n");
		return -1;
	}
	attr.target_id = target_id;
	attr.port      = port;
	attr.priority  = 2;
	ret = ioctl(fd, HI_MCC_IOC_CONNECT, &attr);
	if (ret)
	{
		PCIE_ERR("HI_MCC_IOC_CONNECT err, target:%d, port:%d\n",target_id,port);
		close(fd);
		return -1;
	}

	msg_fd[target_id][port-PCIE_MSG_BASE_PORT] = fd;
	return 0;
}

/*************************************************************
 **  函数名称:   pcie_close_msgport
 **  功能说明:   关闭消息端口
 **  入参    :   1. target_id: 从设备ID
 ** 			 2. port: 消息端口
 **  出参    :   none
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_close_msgport(int32_t target_id, int32_t port)
{
	int32_t fd;
	if (target_id >= PCIE_MAX_CHIPNUM || port >= PCIE_MSG_MAX_PORT)
	{
		PCIE_ERR("invalid pci msg port(%d,%d)!\n", target_id, port);
		return -1;
	}
	fd = msg_fd[target_id][port-PCIE_MSG_BASE_PORT];
	if (fd <= 0)
	{
		return 0;
	}
	
	close(fd);
	msg_fd[target_id][port-PCIE_MSG_BASE_PORT] = -1;
	return 0;		
}

/*************************************************************
 **  函数名称:   pcie_send_msg
 **  功能说明:   发送消息
 **  入参    :   1. target_id: 从设备ID
 ** 			 2. port: 消息端口
 ** 		 	 3. pmsg: 消息数据指针
 ** 			 4. len: 消息长度
 **  出参    :   none
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_send_msg(int32_t target_id, int32_t port, void *pmsg, int len)
{
	int32_t ret = 0;
	int32_t fd;

	if (target_id >= PCIE_MAX_CHIPNUM || port >= PCIE_MSG_MAX_PORT)
	{
		PCIE_ERR("invalid pci msg port(%d,%d)!\n", target_id, port);
		return -1;
	}

	fd = msg_fd[target_id][port-PCIE_MSG_BASE_PORT];
	if (fd <= 0)
	{
		PCIE_ERR("you should open msg port before send message !\n");
		return -1;
	}

	ret = write(fd, pmsg, len);
	if (ret != len)
	{
		PCIE_ERR("pcie_send_msg write_len err:%d\n", ret);
		return -1;
	}

	return 0;
}

/*************************************************************
 **  函数名称:   pcie_recv_msg
 **  功能说明:   接收消息
 **  入参    :   1. target_id: 从设备ID
 ** 			 2. port: 消息端口
 ** 			 3. len: 消息buf长度
 **  出参    :   1. pmsg: 存放消息指针
 **  返回    :   >=0: 实际消息长度; -1:不成功
 *************************************************************/
int pcie_recv_msg(int32_t target_id, int32_t port, void *pmsg, int len)
{
	int32_t ret;
	int32_t fd;

	if (target_id >= PCIE_MAX_CHIPNUM || port >= PCIE_MSG_MAX_PORT || (NULL==pmsg))
	{
		PCIE_ERR("invalid pci msg port(%d,%d)!\n", target_id, port);
		return -1;
	}

	fd = msg_fd[target_id][port-PCIE_MSG_BASE_PORT];
	if (fd <= 0)
	{
		PCIE_ERR("you should open msg port before read message!\n");
		return -1;
	}

	ret = read(fd, pmsg, len);
	if (ret <= 0)
	{
		return -1;
	}

	return ret;
}

/*************************************************************
 **  函数名称:   pcie_move_window
 **  功能说明:   设置移动窗口起始地址
 **  入参    :   1. target_id: 从设备ID
 ** 			 2. port: 消息端口
 ** 		 	 3. start_addr: 待拷贝数据物理起始地址
 ** 			 4. len: 数据长度
 **  出参    :   none
 **  返回    :   0:成功; -1:不成功
 *************************************************************/
int pcie_move_window(int32_t target_id, int32_t port, uint32_t start_addr, uint32_t len)
{
	struct pcie_window_move win_info;
	int32_t ret = 0;
	int32_t fd;

	if (target_id >= PCIE_MAX_CHIPNUM || port >= PCIE_MSG_MAX_PORT)
	{
		PCIE_ERR("invalid pci msg port(%d,%d)!\n", target_id, port);
		return -1;
	}

	fd = msg_fd[target_id][port-PCIE_MSG_BASE_PORT];
	if (fd <= 0)
	{
		PCIE_ERR("you should open msg port before send message !\n");
		return -1;
	}

	win_info.start = start_addr;
	win_info.length = len;
	ret = ioctl(fd, HI_MCC_IOC_PCIE_WIN_MOVE, &win_info);
	if (ret)
	{
		PCIE_ERR("HI_MCC_IOC_PCIE_WIN_MOVE err, target:%d, port:%d\n",target_id,port);
		return -1;
	}

	return 0;
}


