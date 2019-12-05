
#ifndef _PCIE_BOOT_TEST_HEADER_
#define _PCIE_BOOT_TEST_HEADER_

#define HI_IOC_BOOT_BASE		'B'

#define HI_GET_ALL_DEVICES		_IOW(HI_IOC_BOOT_BASE, 1, struct boot_attr)
#define HI_PCIE_TRANSFER_DATA		_IOW(HI_IOC_BOOT_BASE, 2, struct boot_attr)
#define HI_START_TARGET_DEVICE		_IOW(HI_IOC_BOOT_BASE, 3, struct boot_attr)
#define HI_RESET_TARGET_DEVICE		_IOW(HI_IOC_BOOT_BASE, 4, struct boot_attr)

#define MAX_DEVICE_NUM  32
#define MAX_PATH_LEN    128

#define NEED_DDR_INIT           (1<<0)
#define NEED_DDR_TRAINING       (1<<1)

#define MAX_UBOOT_SIZE	0x100000
#define MAX_UIMAGE_SIZE 0x700000
#define MAX_FS_SIZE	0xB00000

#define ACTION_NONE		0x0
#define ACTION_START_DEVICE	(0x1<<0)
#define ACTION_RESET_DEVICE	(0x1<<1)
#define ACTION_DDRT		(0x1<<2)

struct hi_device_info {
	unsigned int id;
	unsigned int dev_type;
};

struct boot_attr {
	unsigned int id;
	unsigned int type;
	unsigned int src;
	unsigned int dest;
	unsigned int len;

	struct hi_device_info remote_devices[MAX_DEVICE_NUM];
};


#endif
