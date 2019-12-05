/********************************************************************************
 * ** Copyright (C) 1992-2011, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : pcie_msg.h
 * ** Desc          : include resource of MCC(Multi-Chips-Communication)
 * ** Author        : he_liangbin
 * ** LastChange    : 2017_06_22
 * ********************************************************************************/

#ifndef _PCIE_MSG_H_
#define _PCIE_MSG_H_

#define MCC_USR_DEV 		"/dev/mcc_userdev"
#define PCIE_MAX_CHIPNUM        32
struct mcc_handle_attr 
{
	int32_t target_id;
	int32_t port;
	int32_t priority;

	/* to store remote device ids */
	int32_t remote_id[PCIE_MAX_CHIPNUM];
};

struct pcie_window_move
{
	uint32_t start; //pyh addr
	uint32_t length;
};

#define HI_IOC_MCC_BASE         'M'
/* Create a new mcc handle. A file descriptor is only used once for one mcc handle. */
#define HI_MCC_IOC_CONNECT      _IOW(HI_IOC_MCC_BASE, 1, struct mcc_handle_attr)
#define HI_MCC_IOC_CHECK        _IOW(HI_IOC_MCC_BASE, 2, struct mcc_handle_attr)
#define HI_MCC_IOC_GET_LOCAL_ID     _IOW(HI_IOC_MCC_BASE, 4, struct mcc_handle_attr) 
#define HI_MCC_IOC_GET_REMOTE_ID    _IOW(HI_IOC_MCC_BASE, 5, struct mcc_handle_attr)
#define HI_MCC_IOC_ATTR_INIT        _IOW(HI_IOC_MCC_BASE, 6, struct mcc_handle_attr)
#define HI_MCC_IOC_PCIE_WIN_MOVE    _IOW(HI_IOC_MCC_BASE, 7, struct pcie_window_move)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif

