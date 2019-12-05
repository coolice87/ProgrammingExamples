/*
 * protocol_add.h
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: lxs
 */

#ifndef COMMPROTOCOL_PROTOCOL_ADD_H_
#define COMMPROTOCOL_PROTOCOL_ADD_H_

typedef struct commDataFrame_1
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	tDebugInfo    info;
	Pcie_u32t 	  dataBlockEnd;
}tDebugInfoFrame;

typedef struct commDataFrame_2
{
	tCommSync sync;
	tCmdNodeHead  cmdHead;
	tOriginalDataDescription  description;
	Pcie_u32t 	 dataBlockEnd;
}tOrigDataDescriptionFrame;

typedef struct commDataFrame_3
{
	tCommSync         sync;
	tCmdNodeHead      cmdHead;
	tAlgorithmResult_FD  result;
	Pcie_u32t 	 	  	 dataBlockEnd;
}tAlgorithmResultFrame_FD;

typedef struct commDataFrame_4
{
	tCommSync         sync;
	tCmdNodeHead      cmdHead;
	tAlgorithmParm_FD  config;
	Pcie_u32t 	      dataBlockEnd;
}tAlgorithmConfigFrame_FD;

typedef struct commDataFrame_5
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	tSystemTime   systemTime;
	Pcie_u32t 	  dataBlockEnd;
}tSystemTImeFrame;

typedef struct commDataFrame_6
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	tDspRunState  dspRunState;
	Pcie_u32t 	  dataBlockEnd;
}tDspRunStateFrame;

typedef struct commDataFrame_7
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	Pcie_u32t     level;  //printfInfoLevel
	Pcie_u32t 	  dataBlockEnd;
}tPrintLevelFrame;

typedef struct commDataFrame_8
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	Pcie_u32t 	  dataBlockEnd;
}tDspSWResetFrame;

typedef struct commDataFrame_9
{
	tCommSync     sync;
	tCmdNodeHead  cmdHead;
	Pcie_u8t      info[32];
	Pcie_u32t 	  dataBlockEnd;
}tTestFrame;

#endif /* COMMPROTOCOL_PROTOCOL_ADD_H_ */
