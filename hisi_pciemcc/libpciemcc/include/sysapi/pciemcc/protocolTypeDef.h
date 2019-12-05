/*
 * DSPTypeDef.h
 *
 *  Created on: 2016Äê12ÔÂ19ÈÕ
 *      Author: lxs
 */

#ifndef PCIE_DSPTYPEDEF_H_
#define PCIE_DSPTYPEDEF_H_

//#define __64BIT_PLATFORM
#ifndef __64BIT_PLATFORM

typedef		double			Pcie_u64t_f;
typedef 	double			Pcie_i64t_f;
typedef		unsigned int	Pcie_u32t;
typedef		int				Pcie_i32t;
typedef		unsigned short	Pcie_u16t;
typedef		short			Pcie_i16t;
typedef		unsigned char	Pcie_u8t;
typedef		char			Pcie_i8t;
typedef		unsigned int	Pcie_bool;

#else
typedef unsigned long long  Pcie_u64t
typedef Pcie_u64t 		    Pcie_u32t
#endif

#define		Pcie_True		1
#define		Pcie_False		0

#ifndef NULL
#define 	NULL			0
#endif

#endif /* PCIE_DSPTYPEDEF_H_ */
