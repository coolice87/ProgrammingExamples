#ifndef __PCI_MCC_HI35XX_DEV__CONGIG_HEADER__
#define __PCI_MCC_HI35XX_DEV__CONGIG_HEADER__

#ifdef CONFIG_PCI  /* For HOST */
	#define __IS_PCI_HOST__			1
	/* #### Hi3531 #### */
	#ifdef CONFIG_ARCH_GODNET
		#define HOST_ARCH_HI3531
		#define HOST_PCIE0_ENABLED	1
		#define HOST_PCIE1_ENABLED	1
	#endif

	/* #### Hi3535 #### */
	#ifdef CONFIG_ARCH_HI3535
		#define HOST_ARCH_HI3535
		#define HOST_PCIE0_ENABLED	1
		#ifdef SLV_ARCH_HI3535
			#define SHARED_MEM_IN_SLAVE
		#endif
	#endif

	/* #### Hi3536 #### */
	#ifdef CONFIG_ARCH_HI3536
		#define HOST_ARCH_HI3536
		#define HOST_PCIE0_ENABLED	1
	#if defined(SLV_ARCH_HI3535) \
		|| defined(SLV_ARCH_HI3536) \
		|| defined(SLV_ARCH_HI3519)
			#define SHARED_MEM_IN_SLAVE
	#endif
    #endif

#else /* If not defined CONFIG_PCI, For SLAVE */

	/* #### Hi3531 #### */
	#ifdef CONFIG_ARCH_GODNET
		#define SLV_ARCH_HI3531		1
		/*
		 * Only one PCIe could be enabled!
		 * ---[0:disabled, 1: enabled]
		 */
		//#define SLV_PCIE0_ENABLED	1
		#define SLV_PCIE1_ENABLED	1
	#endif

	/* #### Hi3532 #### */
	#ifdef CONFIG_ARCH_GODCUBE
		#define SLV_ARCH_HI3532		1
		#define SLV_PCIE0_ENABLED	1
	#endif

	/* #### Hi3535 #### */
	#ifdef CONFIG_ARCH_HI3535
		#define SLV_ARCH_HI3535		1
		#define SLV_PCIE0_ENABLED	1
		#define SHARED_MEM_IN_SLAVE
	#endif

	/* #### Hi3536 #### */
	#ifdef CONFIG_ARCH_HI3536
		#define SLV_ARCH_HI3536		1
		#define SLV_PCIE0_ENABLED       1
		#define SHARED_MEM_IN_SLAVE
	#endif

#endif /* CONFIG_PCI */

#endif /* __PCI_MCC_HI35XX_DEV__CONGIG_HEADER__ */

