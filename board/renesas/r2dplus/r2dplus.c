// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2007,2008
 * Nobuhiro Iwamatsu <iwamatsu@nigauri.org>
 */

#include <ide.h>
#include <init.h>
#include <net.h>
#include <netdev.h>
#include <asm/processor.h>
#include <asm/io.h>

int checkboard(void)
{
	puts("BOARD: Renesas Solutions R2D Plus\n");
	return 0;
}

int board_late_init(void)
{
	return 0;
}

#define FPGA_BASE		0xA4000000
#define FPGA_CFCTL		(FPGA_BASE + 0x04)
#define CFCTL_EN		(0x432)
#define FPGA_CFPOW		(FPGA_BASE + 0x06)
#define CFPOW_ON		(0x02)
#define FPGA_CFCDINTCLR	(FPGA_BASE + 0x2A)
#define CFCDINTCLR_EN	(0x01)

void ide_set_reset(int idereset)
{
	/* if reset = 1 IDE reset will be asserted */
	if (idereset) {
		outw(CFCTL_EN, FPGA_CFCTL);	/* CF enable */
		outw(inw(FPGA_CFPOW)|CFPOW_ON, FPGA_CFPOW); /* Power OM */
		outw(CFCDINTCLR_EN, FPGA_CFCDINTCLR); /* Int clear */
	}
}

#ifndef CONFIG_DM_ETH
int board_eth_init(struct bd_info *bis)
{
	return pci_eth_init(bis);
}
#endif
