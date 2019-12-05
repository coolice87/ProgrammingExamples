
#ifndef __PCIE_MCC_ARCH_HI3519_HEADER__
#define __PCIE_MCC_ARCH_HI3519_HEADER__

#define PCIE_WIN0_BASE			0x90000000
#define PCIE_WIN0_SIZE			0x100000
#define PCIE_WIN1_BASE			0x91000000
#define PCIE_WIN1_SIZE			0x10000
#define PCIE_WIN2_BASE			0x92000000
#define PCIE_WIN2_SIZE			0x100000


#define SYS_CTRL_BASE			0x12020000
#define MISC_CTR_BASE			0x12160000


/* Set 1 to trigger an interrupt[slave] */
#define GLOBAL_SOFT_IRQ			74
#define GLB_SOFT_IRQ_CMD_REG		0x1c
#define GLB_SOFT_IRQ_CMD_BIT		(1<<0)

/*
 * Host will mark this reg to tell slave
 * the right slot_index of the slave
 */
#define DEV_INDEX_REG_OFFSET		0x154
#define SLAVE_SHAKED_BIT		0x6

/* Set this bit to trigger a pcie interrupt */
#define PCIE_SYS_CTRL7			0x101C
#define PCIE_INT_X_BIT			(1 << 5)

#endif
