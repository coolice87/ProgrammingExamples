
#include <linux/module.h>
#include <linux/device.h>
#include <linux/mempolicy.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/vmalloc.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/crc32.h>
#include <linux/bitops.h>
#include <linux/dma-mapping.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

#include "../../ddr_reg_init.h"

#define MAX_PCIE_CFG_LEN_TO_SAVE	(256/4)	

#ifdef SLV_ARCH_HI3536
	#define CRG_REG_BASE		0x12040000
	#define SYS_CTR_REG_BASE	0x12050000
#elif defined SLV_ARCH_HI3535
	#define CRG_REG_BASE		0x20030000
	#define SYS_CTR_REG_BASE	0x20050000
#elif defined SLV_ARCH_HI3532
	#define CRG_REG_BASE		0x20030000
	#define SYS_CTR_REG_BASE	0x20050000
#elif defined SLV_ARCH_HI3519
#define CRG_REG_BASE		0x12010000
#define SYS_CTR_REG_BASE	0x12020000
#else
	#error "No proper reg base addr defined...\n"
#endif

#define PERI_CRG10		0x28
#define HI3519_PERI_CRG11	0x2C
#define HI3531_SC_SYSRES	0x4
#define HI3532_SC_SYSRES	0x4
#define HI3535_SC_SYSRES	0x4
#define HI3536_SC_SYSRES	0x4
#define HI3519_SC_SYSRES	0x4

#define HI3535_SYSBOOT9		0x154
#define HI3536_SYSBOOT9		0x154
#define HI3519_SYSBOOT9		0x154

#define HI3535_SRAM_BASE	0x4010000
#define HI3536_SRAM_BASE	0x4010000

#define HI3531_DEV_ID		0x353119e5
#define HI3532_DEV_ID		0x353219e5
#define HI3535_DEV_ID		0x353519e5
#define HI3536_DEV_ID		0x353619e5
#define HI3519_DEV_ID		0x351919e5

#define HI3531_UNRESET_BIT	(1<<5)
#define HI3532_UNRESET_BIT	(1<<4)
#define HI3535_UNRESET_BIT	(1<<0)
#define HI3536_UNRESET_BIT	(1<<1)
#define HI3519_UNRESET_BIT	(1<<20)

#define MAX_BAR0_SPACE_SIZE	(0x800000)

extern void pcie_init_registers(struct regentry reg_table[], struct hi35xx_dev *hi_dev, unsigned int pm);
extern void hi3536_ddr_init(struct hi35xx_dev *hi_dev); 

struct pci_cfg_context *pci_cfg_entry;
struct pci_cfg_context *pci_bridge_cfg;
volatile unsigned int *pcie_cfg_base = NULL;

struct reg_info {
	unsigned int reg_offset;
	unsigned int value;
};

static int s_current_reg_base = 0;

/*
 * In order to store compatible configuration and iatu configuration,
 * we store content of the pcie configuration space from offset 0x0
 * to offset 0x256.
 */
static int store_pci_context(struct hi35xx_dev *hi_dev)
{
	unsigned int i;
	unsigned int offset;
	unsigned int *pci_ptr = NULL;
	unsigned int *pci_bridge = NULL;

	for (i = 0; i < g_local_handler->remote_device_number; i++) {
		if (hi_dev == g_hi35xx_dev_map[i]) {
			pci_ptr = (unsigned int *)&pci_cfg_entry[i];
			pci_bridge = (unsigned int *)&pci_bridge_cfg[i];
			break;
		}
	}

	if (NULL == pci_ptr) {
		boot_trace(BOOT_ERR, "error: pci_ptr is NULL.");
		return -1;
	}

	/* Save the bridge's config registers value */	
	if (hi_dev->slot_index > 1) {
		if (NULL == pci_bridge) {
			boot_trace(BOOT_ERR, "error: pci_bridge is NULL.");
			return -1;
		}

		for (i = 0; i < MAX_PCIE_CFG_LEN_TO_SAVE; i++) {
			offset = (i << 2);
	 		pci_read_config_dword(hi_dev->pdev->bus->self, offset, pci_bridge);
			pci_bridge++;	
		}

	}

	/* Save the device's config registers value */
	for (i = 0; i < MAX_PCIE_CFG_LEN_TO_SAVE; i++) {
		offset = (i << 2);
		g_local_handler->pci_config_read(hi_dev, offset, pci_ptr);
		pci_ptr++;
	}

	return 0;
}

/*
 * After a device was reset, we need to re-configure the pci space
 * with the information stored before.[0x0 ~ 0x91c]
 */
static int restore_pci_context(struct hi35xx_dev *hi_dev)
{
	unsigned int i;
	unsigned int offset;
	unsigned int *pci_ptr = NULL;
	unsigned int *pci_bridge = NULL;

	for (i = 0; i < g_local_handler->remote_device_number; i++) {
		if (hi_dev == g_hi35xx_dev_map[i]) {
			pci_ptr = (unsigned int *)&pci_cfg_entry[i];
			pci_bridge = (unsigned int *)&pci_bridge_cfg[i];
			break;
		}
	}

	if (NULL == pci_ptr) {
		boot_trace(BOOT_ERR, "error: pci_ptr is NULL.");
		return -1;
	}

	/* Recover the bridge's config registers value */
	if (hi_dev->slot_index > 1) {
		if (NULL == pci_bridge) {
			boot_trace(BOOT_ERR, "error: pci_bridge is NULL.");
			return -1;
		}

		for(i = 0; i < MAX_PCIE_CFG_LEN_TO_SAVE; i++) {
			offset = (i << 2);
			pci_write_config_dword(hi_dev->pdev->bus->self, offset, *pci_bridge);
			pci_bridge++;
		}
	}
	
	/* Recover the device's config registers value */
	for(i = 0; i < MAX_PCIE_CFG_LEN_TO_SAVE; i++) {
		offset = (i << 2);
		g_local_handler->pci_config_write(hi_dev, offset, *pci_ptr);
		pci_ptr++;
	}

	return 0;
}


static int start_device(struct hi35xx_dev *hi_dev)
{
	unsigned int device_type = 0x0;
	unsigned int value = 0;
	int ret = 0;

	g_local_handler->move_pf_window_in(hi_dev, CRG_REG_BASE, 0xffff, 1);

	device_type = hi_dev->device_id;
	switch (device_type) {
		case HI3531_DEV_ID:
			printk(KERN_INFO "Starting device[0x%x][0x%x]\n",
					HI3531_DEV_ID, hi_dev->slot_index);
			value = readl((void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			value &= ~HI3531_UNRESET_BIT;
			writel(value, (void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			break;
		case HI3532_DEV_ID:
			printk(KERN_INFO "Starting device[0x%x][0x%x]\n",
					HI3532_DEV_ID, hi_dev->slot_index);
			value = readl((void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			value &= ~HI3532_UNRESET_BIT;
			writel(value, (void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			break;
		case HI3535_DEV_ID:
			printk(KERN_INFO "Starting device[0x%x][0x%x]\n",
					HI3535_DEV_ID, hi_dev->slot_index);
			value = readl((void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			value &= ~HI3535_UNRESET_BIT;
			writel(value, (void *)(hi_dev->pci_bar1_virt + PERI_CRG10));

			/* clear PCIE MCC handshake flag */
			g_local_handler->move_pf_window_in(hi_dev,
					SYS_CTR_REG_BASE, 0xffff, 1);
			writel(0x0, (void *)(hi_dev->pci_bar1_virt + HI3535_SYSBOOT9));
			break;
		case HI3536_DEV_ID:
			printk(KERN_INFO "Starting device[0x%x][0x%x]\n",
					HI3536_DEV_ID, hi_dev->slot_index);
			value = readl((void *)(hi_dev->pci_bar1_virt + PERI_CRG10));
			value &= ~HI3536_UNRESET_BIT;
			writel(value, (void *)(hi_dev->pci_bar1_virt + PERI_CRG10));

			/* clear PCIE MCC handshake flag */
			g_local_handler->move_pf_window_in(hi_dev, SYS_CTR_REG_BASE, 0xffff, 1);
			writel(0x0, (void *)(hi_dev->pci_bar1_virt + HI3536_SYSBOOT9));
			break;
		case HI3519_DEV_ID:
			printk(KERN_INFO "Starting device[0x%x][0x%x]\n",
					HI3519_DEV_ID, hi_dev->slot_index);

			/* Set the start flag for slave hi3519 to boot from sram*/
			g_local_handler->move_pf_window_in(hi_dev, SYS_CTR_REG_BASE, 0xffff, 1);
			writel(0x7964616f, (void *)(hi_dev->pci_bar1_virt + HI3519_SYSBOOT9));
			msleep(1);

			/* clear PCIE MCC handshake flag */
			g_local_handler->move_pf_window_in(hi_dev, SYS_CTR_REG_BASE, 0xffff, 1);
			writel(0x0, (void *)(hi_dev->pci_bar1_virt + HI3519_SYSBOOT9));
			break;
		default:
			boot_trace(BOOT_ERR, "unknow chip type, "
					"start dev[%d] failed!",
					hi_dev->slot_index);
			ret = -1;
	}

	g_local_handler->move_pf_window_in(hi_dev, SYS_CTR_REG_BASE, 0xffff, 1);

	return ret;
}

/*
 * reset the slave board
 */
static int reset_device(struct hi35xx_dev *hi_dev)
{
	unsigned int device_type = 0x0;

	g_local_handler->move_pf_window_in(hi_dev, SYS_CTR_REG_BASE, 0xffff, 1);

	device_type = hi_dev->device_id;

	switch (device_type) {
		case HI3531_DEV_ID:
			writel(0xeeeeffff, (void *)(hi_dev->pci_bar1_virt + HI3531_SC_SYSRES));
			break;
		case HI3532_DEV_ID:
			writel(0xeeeeffff, (void *)(hi_dev->pci_bar1_virt + HI3532_SC_SYSRES));
			break;
		case HI3535_DEV_ID:
			writel(0xeeeeffff, (void *)(hi_dev->pci_bar1_virt + HI3535_SC_SYSRES));
			break;
		case HI3536_DEV_ID:
			writel(0xeeeeffff, (void *)(hi_dev->pci_bar1_virt + HI3536_SC_SYSRES));
			break;
		case HI3519_DEV_ID:
			writel(0xeeeeffff, (void *)(hi_dev->pci_bar1_virt + HI3519_SC_SYSRES));
			break;
		default:
			boot_trace(BOOT_ERR, "unknow chip type, "
					"reset dev[%d] failed!",
					hi_dev->slot_index);
			return -1;
	}

	/*
	 * Wait for the device restarted to be stable,
	 * before we have any write operation.
	 * MAKE SURE there is enough delay for that.
	 */
	{
		int i = 40;
		while (i--)
			udelay(1000);
	}
	printk(KERN_INFO "wait ......\n");

	restore_pci_context(hi_dev);

	if (DEVICE_CHECKED_FLAG == hi_dev->vdd_checked_success)
		hi_dev->vdd_checked_success = DEVICE_RESTART_FLAG;

	return 0;
}

static int transfer_data(struct hi35xx_dev *hi_dev, struct boot_attr *attr)
{
	unsigned int target_addr = 0;
	unsigned int source_addr = 0;
	unsigned int last_length = 0;
	unsigned int loop_times  = 0;
	unsigned int max_loop_times = 0;

	boot_trace(BOOT_INFO, "transfer data called[target_addr:0x%x].", attr->dest);

	target_addr = attr->dest;
	source_addr = attr->src;

	max_loop_times = attr->len / MAX_BAR0_SPACE_SIZE;

	for (loop_times = 0; loop_times < max_loop_times; loop_times++) {

		g_local_handler->move_pf_window_in(hi_dev, target_addr, 0xffff, 0);

		if (copy_from_user((void *)hi_dev->pci_bar0_virt, (void *)source_addr,
					MAX_BAR0_SPACE_SIZE)) {
			boot_trace(BOOT_ERR, "transfer data to device failed.");
			return -1;
		}

		target_addr += MAX_BAR0_SPACE_SIZE;
		source_addr += MAX_BAR0_SPACE_SIZE;
	}

	last_length = attr->len % MAX_BAR0_SPACE_SIZE;
	if (last_length) {
		g_local_handler->move_pf_window_in(hi_dev, target_addr, 0xffff, 0);

		if (copy_from_user((void *)hi_dev->pci_bar0_virt, (void *)source_addr, last_length))
		{
			boot_trace(BOOT_ERR, "transfer last data to device failed.");
			return -1;
		}
	
	}

	boot_trace(BOOT_INFO, "data transfered!");
	return 0;
}

/*
 * Structure of file booter
 *
 *	**************** \					\
 *	**************** |					|
 *	**************** | booter code [16 KBytes]		|
 *	**************** |					|
 *	**00000000000000 /					|
 *	^^^^000000000000 > pc jump code [512 Bytes]		|total:24 KBytes
 *	################ \					|
 *	################ |					|
 *	################ | ddr training [8 KBytes - 512 Bytes]	|
 *	################ |					|
 *	###0000000000000 /					/
 */
#define FILE_BOOTER_SIZE	0x6000	/* 24 KBytes */
#define PC_JUMP_OFFSET		0x4000	/* 16 KBytes */
#define PC_JUMP_SIZE		0x200	/* 512 Bytes */
#define DDRT_CODE_OFFSET	(PC_JUMP_OFFSET + PC_JUMP_SIZE)
#define DDRT_CODE_SIZE		(FILE_BOOTER_SIZE - DDRT_CODE_OFFSET)

#define INNER_RAM_SIZE		0x2800	/* 10 KBytes */
#define DDRT_OFFSET_IN_RAM	0xc00	/* addr ahead is reserved for stack */

static int ddr_soft_training(struct hi35xx_dev *hi_dev)
{
	char *pfile_buf;
	struct file *fp;
	mm_segment_t old_fs;
	loff_t pos = 0;
	unsigned int read_count = 0;

	printk(KERN_INFO "# start DDR training!!\n");

	/* size of file booter is always 24KB */
	pfile_buf = kmalloc(FILE_BOOTER_SIZE, GFP_KERNEL);
	memset(pfile_buf, 0, FILE_BOOTER_SIZE);
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open("./booter", O_RDONLY, 0);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		kfree(pfile_buf);
		boot_trace(BOOT_ERR, "open booter failed!");
		return IS_ERR(fp);
	}
    
	read_count = fp->f_op->read(fp, pfile_buf, FILE_BOOTER_SIZE, &pos);
	set_fs(old_fs);
	filp_close(fp, 0);

	boot_trace(BOOT_DEBUG, "Size of booter: 0x%x", read_count);
	boot_trace(BOOT_DEBUG, "pc_jump: addr[0x%x]:0x%x  0x%x",
			(unsigned int)pfile_buf + PC_JUMP_OFFSET,
			*((unsigned int *)(pfile_buf + PC_JUMP_OFFSET)),
			*((unsigned int *)(pfile_buf + PC_JUMP_OFFSET + 4)));

	/* map pcie window to DDR in slave side */
	g_local_handler->move_pf_window_in(hi_dev, 0x0, 0xfffff, 0);

	/* copy pc jump code to slave DDR base */
	memcpy((void *)hi_dev->pci_bar0_virt, pfile_buf + PC_JUMP_OFFSET, 32);

	boot_trace(BOOT_DEBUG, "Read: addr[0x%x]:0x%x  0x%x",
			(unsigned int)pfile_buf + PC_JUMP_OFFSET,
			*((unsigned int *)(hi_dev->pci_bar0_virt)),
			*((unsigned int *)((unsigned int)hi_dev->pci_bar0_virt + 4)));
	
	kfree(pfile_buf);

	return 0;
}

static void slave_reg_write(struct hi35xx_dev *hi_dev,
				unsigned int reg_addr,
				unsigned int reg_value)
{
	if (s_current_reg_base != (reg_addr & 0xffff0000)) {
		boot_trace(BOOT_INFO, "write:move pf win: currentbase 0x%x, regbase 0x%x",
				s_current_reg_base, reg_addr);
		s_current_reg_base = (reg_addr & 0xffff0000);
		g_local_handler->move_pf_window_in(hi_dev,
				s_current_reg_base,
				0xffff,
				0x1);
	}

	writel(reg_value, (void *)(reg_addr - s_current_reg_base + hi_dev->pci_bar1_virt));
}

static void slave_reg_read(struct hi35xx_dev *hi_dev,
			unsigned int reg_addr,
			unsigned int *reg_value)
{
	unsigned int reg_val_r;

	if (s_current_reg_base != (reg_addr & 0xffff0000)) {
		boot_trace(BOOT_INFO, "read:move pf win: currentbase 0x%x, regbase 0x%x",
				s_current_reg_base, reg_addr);
		
		s_current_reg_base =  (reg_addr & 0xffff0000);
		g_local_handler->move_pf_window_in(hi_dev,
						s_current_reg_base,
						0xffff,
						0x1);
	}
	
	reg_val_r = (*(volatile unsigned *) (reg_addr - s_current_reg_base + hi_dev->pci_bar1_virt));
	*reg_value = reg_val_r;
}

#define REG_SC_GEN20			(0x90)
#define UBOOT_DOWNLOAD_TO_SRAM_SIZE	(0x4f00)
#define DDR_INIT_MAGIC			(0x7a696a75)

static void slave_ddr_init(struct hi35xx_dev *hi_dev,
			char *ddr_init_data,
			unsigned int len)
{
	unsigned int value = 0;
	unsigned long wait_time = 0;

	/* step1: write the magic flag */
	slave_reg_write(hi_dev, SYS_CTR_REG_BASE + REG_SC_GEN20, DDR_INIT_MAGIC);

	/* step2: download the uboot to sram */
	g_local_handler->move_pf_window_in(hi_dev, 0x0, 0xfffff, 0);
	memcpy((void *)hi_dev->pci_bar0_virt, ddr_init_data, len);

	/* step3: unreset the slave*/
#ifdef SLV_ARCH_HI3519
	slave_reg_read(hi_dev, CRG_REG_BASE + HI3519_PERI_CRG11, &value);
	value &= ~HI3519_UNRESET_BIT;
	slave_reg_write(hi_dev, CRG_REG_BASE + HI3519_PERI_CRG11, value);
#else
	slave_reg_read(hi_dev, CRG_REG_BASE + PERI_CRG10, &value);
	value &= ~HI3536_UNRESET_BIT;
	slave_reg_write(hi_dev, CRG_REG_BASE + PERI_CRG10, value);
#endif

	/* step4: wait ddr int complete*/
	wait_time = jiffies + 5 * HZ;
	do {
		if (!time_before(jiffies, wait_time)) {
			boot_trace(BOOT_ERR, "dev[%d] DDR training timeout!",
					hi_dev->slot_index);
			return;
		}
		
#ifdef SLV_ARCH_HI3519		
		slave_reg_read(hi_dev, SYS_CTR_REG_BASE + HI3519_SYSBOOT9, &value);
#else
		slave_reg_read(hi_dev, SYS_CTR_REG_BASE + HI3536_SYSBOOT9, &value);
#endif
	} while (0x8080 != value);

#ifdef SLV_ARCH_HI3536
	/* step5:reset the slave */
	slave_reg_read(hi_dev, CRG_REG_BASE + PERI_CRG10, &value);
	value |= HI3536_UNRESET_BIT;
	slave_reg_write(hi_dev, CRG_REG_BASE + PERI_CRG10, value);
#endif

}

static int init_ddr(struct hi35xx_dev *hi_dev, struct boot_attr *attr)
{
	int ret = 0;
	char *kernel_buf;
	struct regentry *pentry;

	boot_trace(BOOT_INFO, "init ddr called!");

	kernel_buf = kmalloc(UBOOT_DOWNLOAD_TO_SRAM_SIZE, GFP_KERNEL);
	if (NULL == kernel_buf) {
		boot_trace(BOOT_ERR, "kmalloc for ddr scripts failed.");
		return -1;
	}

	ret = copy_from_user(kernel_buf, (void *)attr->src, UBOOT_DOWNLOAD_TO_SRAM_SIZE);
	if (ret) {
		boot_trace(BOOT_ERR, "cpy ddr scripts from usr failed.");
		kfree(kernel_buf);
		return -1;
	}


	boot_trace(BOOT_INFO, "copy script from usr done.");
	boot_trace(BOOT_INFO, "about to init ddr.");

	/* init ddr */
	if (HI3519_DEV_ID == hi_dev->device_id 
		|| HI3536_DEV_ID == hi_dev->device_id) {
		slave_ddr_init(hi_dev, kernel_buf, UBOOT_DOWNLOAD_TO_SRAM_SIZE);
	} else {
		pentry = (struct regentry *)(kernel_buf + 0x40);
		pcie_init_registers(pentry, hi_dev, 0);
	}

	kfree(kernel_buf);

	/* Need to do DDR soft training ? */
	if (HI3519_DEV_ID == hi_dev->device_id
		|| HI3536_DEV_ID == hi_dev->device_id) {
		if (ddr_soft_training(hi_dev)) {
			boot_trace(BOOT_ERR, "slave ddr training failed!");
			return -1;
		}
	}

	return 0;
}

void pcie_arch_init(struct pcie_boot_opt * boot_opt)
{
	boot_opt->init_ddr = init_ddr;
	boot_opt->transfer_data = transfer_data;
	boot_opt->start_device = start_device;
	boot_opt->reset_device = reset_device;
}

/* Alloc space for pcie config data and store pcie config data*/
int pcie_cfg_store(void)
{
	struct hi35xx_dev *hi_dev;
	int i = 0;
	int cfg_size;

	cfg_size = sizeof(struct pci_cfg_context) * g_local_handler->remote_device_number;
	pci_cfg_entry = kmalloc(cfg_size, GFP_KERNEL);
	if (NULL == pci_cfg_entry) {
		boot_trace(BOOT_ERR, "kmalloc for pci cfg entry failed.\n");
		return -1;
	}

	pci_bridge_cfg = kmalloc(cfg_size, GFP_KERNEL);
	if (NULL == pci_bridge_cfg) {
		boot_trace(BOOT_ERR, "kmalloc for pci bridge cfg failed.\n");
	}

	for (i = 0; i < g_local_handler->remote_device_number; i++) {
		hi_dev = g_hi35xx_dev_map[i];
		store_pci_context(hi_dev);
	}
	
	return 0;
}

/* Free the space for pcie config data */
void pcie_cfg_free(void)
{
	if (pci_cfg_entry) {
		kfree(pci_cfg_entry);
		pci_cfg_entry = NULL;
	}
	
	if (pci_bridge_cfg) {
		kfree(pci_bridge_cfg);
		pci_bridge_cfg = NULL;
	}
}
