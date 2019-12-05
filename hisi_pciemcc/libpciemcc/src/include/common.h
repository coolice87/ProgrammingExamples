/********************************************************************************
 * ** Copyright (C) 1992-2011, Hangzhou Gosun Electronic Technology CO.LTD.
 * **                              All Rights Reserved
 * **
 * ** FileName      : common.h
 * ** Desc          : include general header file and types
 * ** Author        : he_liangbin
 * ** LastChange    : 2016_12_23
 * ********************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <asm/types.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>   
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <net/ethernet.h>
#include <linux/ioctl.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/sockios.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <netinet/in.h>  
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define NONE          "\033[m"
#define RED           "\033[0;31m"
#define GREEN         "\033[0;32m"
#define BLUE          "\033[0;34m"
#define DARY_GRAY     "\033[1;30m"
#define CYAN          "\033[0;36m"
#define PURPLE        "\033[0;35m"
#define BROWN         "\033[0;33m"
#define YELLOW        "\033[1;33m"
#define WHITE         "\033[1;37m"

#define PCIE_MSG(fmt, args ... )                         \
	do {                                                \
		printf(GREEN "[PCIEMCC-" SVN_VERSION "] "        \
				"MSG " fmt NONE, ## args);              \
	} while(0)

#define PCIE_ERR(fmt, args ... )                         \
do {                                                \
	printf(RED "[PCIEMCC-" SVN_VERSION "] "          \
			"ERR (%s|%s|%d): " fmt NONE,            \
			__FILE__, __func__, __LINE__, ## args); \
} while(0)

#define PCIE_WARN(fmt, args ... )                        \
	do {                                                \
		printf(YELLOW "[PCIEMCC-" SVN_VERSION "] "       \
				"WARN (%s|%s|%d): " fmt NONE,           \
				__FILE__, __func__, __LINE__, ## args); \
	} while(0)

//#define LOG_PCIE_DEBUG
#ifdef LOG_PCIE_DEBUG
#define PCIE_DBG(fmt, args ... )                         \
	do {                                                \
		printf(BLUE "[PCIEMCC-" SVN_VERSION "] "         \
				"DBG (%s|%s|%d): " fmt NONE,            \
				__FILE__, __func__, __LINE__, ## args); \
	} while(0)
#else
#define PCIE_DBG(fmt, args ...) 							\
	do { 												\
	}while(0) 		
#endif


#endif

