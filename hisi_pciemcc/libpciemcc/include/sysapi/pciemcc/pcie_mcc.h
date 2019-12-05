/********************************************************************************
 * ** Copyright (C) 1992-2011, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : pcie_mcc.h
 * ** Desc          : include resource of MCC(Multi-Chips-Communication)
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_06_23
 * ********************************************************************************/

#ifndef _PCIE_MCC_H_
#define _PCIE_MCC_H_

#define PCIE_MSG_BASE_PORT          100     /* we use msg port above this value */
#define PCIE_MSG_MAX_PORT_NUM       260     /* max msg port count, also you can change it */
#define PCIE_MSG_MAX_PORT           ((PCIE_MSG_BASE_PORT)+(PCIE_MSG_MAX_PORT_NUM))

#define PCIV_MSGPORT_COMM_CMD       PCIV_MSG_BASE_PORT  /* common msg port, used for general command */

#ifdef __cplusplus
extern "C" {
#endif

/* 功能说明:   获取PCIE从设备ID */
int pcie_get_remoteid(int32_t *remote_id, int32_t *count);

/*  功能说明:   获取PCIE 本地ID */
int pcie_get_localid(int32_t *local_id);

/*  功能说明:   与从设备建立连接 */
int pcie_wait_connect(int32_t target_id);

/*  功能说明:   打开消息端口 */
int pcie_open_msgport(int32_t target_id, int32_t port);

/*  功能说明:   关闭消息端口 */
int pcie_close_msgport(int32_t target_id, int32_t port);

/*  功能说明:   发送消息 */
int pcie_send_msg(int32_t target_id, int32_t port, void *pmsg, int len);

/*  功能说明:   接收消息 */
int pcie_recv_msg(int32_t target_id, int32_t port, void *pmsg, int len);

/*  功能说明:   设置移动窗口起始地址 */
int pcie_move_window(int32_t target_id, int32_t port, uint32_t start_addr, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif

