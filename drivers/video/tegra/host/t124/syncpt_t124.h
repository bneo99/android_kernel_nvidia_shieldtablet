/*
 * drivers/video/tegra/host/t124/syncpt_t124.h
 *
 * Tegra Graphics Host Syncpoints for T124
 *
 * Copyright (c) 2011, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __NVHOST_SYNCPT_T124_H
#define __NVHOST_SYNCPT_T124_H

#include "host1x/host1x_syncpt.h"

#define NVSYNCPT_ISP_0_0	NVSYNCPT_MPE
#define NVSYNCPT_ISP_0_1	1
#define NVSYNCPT_ISP_0_2	2
#define NVSYNCPT_ISP_0_3	3
#define NVSYNCPT_ISP_1_0	4
#define NVSYNCPT_ISP_1_1	5
#define NVSYNCPT_ISP_1_2	6
#define NVSYNCPT_ISP_1_3	7
#define NVSYNCPT_VI_0_0		NVSYNCPT_VI_ISP_0
#define NVSYNCPT_VI_0_1		NVSYNCPT_VI_ISP_1
#define NVSYNCPT_VI_0_2		NVSYNCPT_VI_ISP_2
#define NVSYNCPT_VI_0_3		NVSYNCPT_VI_ISP_3
#define NVSYNCPT_VI_0_4		NVSYNCPT_VI_ISP_4
#define NVSYNCPT_VI_1_0		NVSYNCPT_MPE_EBM_EOF
#define NVSYNCPT_VI_1_1		NVSYNCPT_MPE_WR_SAFE
#define NVSYNCPT_VI_1_2		NVSYNCPT_DISP0_B /* !!!FIXME!!! */
#define NVSYNCPT_VI_1_3		NVSYNCPT_DISP1_B /* !!!FIXME!!! */
#define NVSYNCPT_VI_1_4		NVSYNCPT_DISP0_C /* !!!FIXME!!! */
#define NVSYNCPT_TSEC		NVSYNCPT_DISP1_C /* !!!FIXME!!! */
#define NVSYNCPT_MSENC		NVSYNCPT_MPE

#ifdef CONFIG_ARCH_TEGRA_VIC
#define NVSYNCPT_VIC		NVSYNCPT_2D_0
#endif

#define NVSYNCPT_GK20A_BASE 32
/* following is base + number of gk20a channels. TODO: remove magic */
#define NVSYNCPT_GK20A_LAST (NVSYNCPT_GK20A_BASE + 127)

#define NV_VI_0_SYNCPTS ( \
	BIT(NVSYNCPT_VI_0_0) | \
	BIT(NVSYNCPT_VI_0_1) | \
	BIT(NVSYNCPT_VI_0_2) | \
	BIT(NVSYNCPT_VI_0_3) | \
	BIT(NVSYNCPT_VI_0_4) | \
	0 )

#define NV_VI_1_SYNCPTS ( \
	BIT(NVSYNCPT_VI_1_0) | \
	BIT(NVSYNCPT_VI_1_1) | \
	BIT(NVSYNCPT_VI_1_2) | \
	BIT(NVSYNCPT_VI_1_3) | \
	BIT(NVSYNCPT_VI_1_4) | \
	0 )

#define NV_ISP_0_SYNCPTS ( \
	BIT(NVSYNCPT_ISP_0_0) | \
	BIT(NVSYNCPT_ISP_0_1) | \
	BIT(NVSYNCPT_ISP_0_2) | \
	BIT(NVSYNCPT_ISP_0_3) | \
	0 )

#define NV_ISP_1_SYNCPTS ( \
	BIT(NVSYNCPT_ISP_1_0) | \
	BIT(NVSYNCPT_ISP_1_1) | \
	BIT(NVSYNCPT_ISP_1_2) | \
	BIT(NVSYNCPT_ISP_1_3) | \
	0 )

#define NVCAMERA_MANAGED_SYNCPTS ( \
	NV_VI_0_SYNCPTS  | NV_VI_1_SYNCPTS  | \
	NV_ISP_0_SYNCPTS | NV_ISP_1_SYNCPTS | \
	0 )

#define NVWAITBASE_3D   (3)
#define NVWAITBASE_MSENC  (4)
#define NVWAITBASE_TSEC   (5)

#endif /* __NVHOST_SYNCPT_T124_H */