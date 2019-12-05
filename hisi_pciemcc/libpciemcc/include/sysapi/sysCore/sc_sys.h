/***********************************************************************
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Description: sc_sys.h 
  * Revisions  : Created on 2017-06-09
  * Author: xu_longfei
  *
  **********************************************************************/
	  
#ifndef __SC_SYS_H__
#define __SC_SYS_H__
	  
	  
/***********************************************************************/
/*							 linux内核头文件		     			   */
/***********************************************************************/

#ifdef __KERNEL__   	   /* Linux kernel */
#include <linux/version.h> /* Kernel version */
#include <linux/module.h>
#include <linux/kernel.h>  /* Kernel support */
#include <linux/fs.h>      /* Defines File operations */
#include <linux/types.h>
#include <linux/ioport.h>  /* Memory/device locking macros   */
#include <linux/errno.h>   /* Defines standard error codes */
#include <linux/sched.h>   /* Defines pointer (current) to current task */
#include <linux/fcntl.h>   /* Modify file */
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>

#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/interrupt.h>

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/phy.h>

#include <asm/system.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

/*KERNEL_VERSION >= 2,6,0*/
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/cdev.h>    /* Charactor device support */
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/serial_core.h>
#include <linux/namei.h>
#include <linux/io.h>
/*end KERNEL_VERSION >= 2,6,0*/

#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/i2c.h>
#include <linux/console.h>
#include <linux/serial_reg.h>
#include <linux/tty_flip.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/file.h>
#include <linux/wait.h>
#include <linux/vmalloc.h>
#include <linux/poll.h>
#include <linux/mount.h>

#include <linux/securebits.h>

#else
/* linux application*/
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>
#include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/unistd.h>
#include <semaphore.h>
#include <sys/vfs.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include <linux/ioctl.h>
#include <sys/mount.h>
#include <sys/sysinfo.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <linux/sockios.h>
#include <sys/mman.h>
#include <linux/errno.h>
#include <linux/kd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>

#include <sys/times.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>


#endif

	  
#endif /* end __SC_SYS_H__ */

