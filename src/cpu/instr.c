/*
 * Copyright (c) 2001-2003 Viliam Holub
 * All rights reserved.
 *
 * Distributed under the terms of GPL.
 *
 *
 *  Instruction decoding
 *
 */

#include "instr.h"

char *reg_name[REG_VARIANTS][REG_COUNT] = {
	{
		"r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",  "r8",  "r9",
		"r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19",
		"r20", "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29",
		"r30", "r31"
	},
	{
		"$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",  "$8",  "$9",
		"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
		"$30", "$31"
	},
	{
		"0",  "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1",
		"t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", 
		"s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp",
		"fp", "ra"
	}
};

char *cp0_name[REG_VARIANTS][REG_COUNT] = {
	{
		"0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
		"30", "31"
	},
	{
		"$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",  "$8",  "$9",
		"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
		"$30", "$31"
	},
	{
		"index",    "random",   "entrylo0", "entrylo1",
		"context",  "pagemask", "wired",    "res_7",
		"badvaddr", "count",    "entryhi",  "compare",
		"status",   "cause",    "epc",      "prid",
		"config",   "lladdr",   "watchlo",  "watchhi",
		"xcontext", "res_21",   "res_22",   "res_23",
		"res_24",   "res_25",   "res_26",   "res_27",
		"res_28",   "res_29",   "errorepc", "res_31"
	}
};

char *cp1_name[REG_VARIANTS][REG_COUNT] = {
	{
		"0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", 
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
		"30", "31"
	},
	{
		"$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",  "$8",  "$9",
		"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
		"$30", "$31"
	},
	{
		"cp1_0",  "cp1_1",  "cp1_2",  "cp1_3",  "cp1_4",  "cp1_5",  "cp1_6",
		"cp1_7",  "cp1_8",  "cp1_9",  "cp1_10", "cp1_11", "cp1_12", "cp1_13",
		"cp1_14", "cp1_15", "cp1_16", "cp1_17", "cp1_18", "cp1_19", "cp1_20",
		"cp1_21", "cp1_22", "cp1_23", "cp1_24", "cp1_25", "cp1_26", "cp1_27",
		"cp1_28", "cp1_29", "cp1_30", "cp1_31"
	}
};

char *cp2_name[REG_VARIANTS][REG_COUNT] = {
	{
		"0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", 
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
		"30", "31"
	},
	{
		"$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",  "$8",  "$9",
		"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
		"$30", "$31"
	},
	{
		"cp2_0",  "cp2_1",  "cp2_2",  "cp2_3",  "cp2_4",  "cp2_5",  "cp2_6",
		"cp2_7",  "cp2_8",  "cp2_9",  "cp2_10", "cp2_11", "cp2_12", "cp2_13",
		"cp2_14", "cp2_15", "cp2_16", "cp2_17", "cp2_18", "cp2_19", "cp2_20",
		"cp2_21", "cp2_22", "cp2_23", "cp2_24", "cp2_25", "cp2_26", "cp2_27",
		"cp2_28", "cp2_29", "cp2_30", "cp2_31"
	}
};

char *cp3_name[REG_VARIANTS][REG_COUNT] = {
	{
		"0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", 
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
		"30", "31"
	},
	{
		"$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",  "$8",  "$9",
		"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
		"$30", "$31"
	},
	{
		"cp3_0",  "cp3_1",  "cp3_2",  "cp3_3",  "cp3_4",  "cp3_5",  "cp3_6",
		"cp3_7",  "cp3_8",  "cp3_9",  "cp3_10", "cp3_11", "cp3_12", "cp3_13",
		"cp3_14", "cp3_15", "cp3_16", "cp3_17", "cp3_18", "cp3_19", "cp3_20",
		"cp3_21", "cp3_22", "cp3_23", "cp3_24", "cp3_25", "cp3_26", "cp3_27",
		"cp3_28", "cp3_29", "cp3_30", "cp3_31"
	}
};