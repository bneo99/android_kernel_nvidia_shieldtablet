/*
 * drivers/video/tegra/host/t124/t124.c
 *
 * Tegra Graphics Init for T124 Architecture Chips
 *
 * Copyright (c) 2011-2012, NVIDIA Corporation.
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <linux/slab.h>

#include "dev.h"
#include "nvhost_job.h"
#include "class_ids.h"

#include "t124.h"
#include "host1x/host1x.h"

#include "hardware_t124.h"
#include "syncpt_t124.h"

#include "gk20a/gk20a.h"
#include "t20/t20.h"
#include "vic03/vic03.h"
#include "msenc/msenc.h"
#include "tsec/tsec.h"

#include "nvhost_memmgr.h"
#include "chip_support.h"

static int t124_num_alloc_channels = 0;

#define HOST_EMC_FLOOR 300000000

static struct resource tegra_host1x04_resources[] = {
	{
		.start = TEGRA_HOST1X_BASE,
		.end = TEGRA_HOST1X_BASE + TEGRA_HOST1X_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = INT_SYNCPT_THRESH_BASE,
		.end = INT_SYNCPT_THRESH_BASE + INT_SYNCPT_THRESH_NR - 1,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = INT_HOST1X_MPCORE_GENERAL,
		.end = INT_HOST1X_MPCORE_GENERAL,
		.flags = IORESOURCE_IRQ,
	},
};

static const char *s_syncpt_names[NV_HOST1X_SYNCPT_NB_PTS] = {
	[NVSYNCPT_CSI_VI_0]	= "csi_vi_0",
	[NVSYNCPT_CSI_VI_1]	= "csi_vi_1",
	[NVSYNCPT_VI_ISP_0]	= "vi_isp_0",
	[NVSYNCPT_VI_ISP_1]	= "vi_isp_1",
	[NVSYNCPT_VI_ISP_2]	= "vi_isp_2",
	[NVSYNCPT_VI_ISP_3]	= "vi_isp_3",
	[NVSYNCPT_VI_ISP_4]	= "vi_isp_4",
	[NVSYNCPT_3D]		= "3d",
	[NVSYNCPT_MPE]		= "mpe",
	[NVSYNCPT_MPE_EBM_EOF]	= "mpe_ebm_eof",
	[NVSYNCPT_MPE_WR_SAFE]	= "mpe_wr_safe",
	[NVSYNCPT_VIC]		= "vic",
	[NVSYNCPT_TSEC]		= "tsec",
	[NVSYNCPT_DISP0_A]	= "disp0",
	[NVSYNCPT_DISP1_A]	= "disp1",
	[NVSYNCPT_AVP_0]	= "avp",
	[NVSYNCPT_DISP0_B]	= "disp0b",
	[NVSYNCPT_DISP1_B]	= "disp1b",
	[NVSYNCPT_DISP0_C]	= "disp0c",
	[NVSYNCPT_DISP1_C]	= "disp0c",
	[NVSYNCPT_VBLANK0]	= "vblank0",
	[NVSYNCPT_VBLANK1]	= "vblank1",
	[NVSYNCPT_DSI]		= "dsi",
};

static struct host1x_device_info host1x04_info = {
	.nb_channels	= T124_NVHOST_NUMCHANNELS,
	.nb_pts		= NV_HOST1X_SYNCPT_NB_PTS,
	.nb_mlocks	= NV_HOST1X_NB_MLOCKS,
	.nb_bases	= NV_HOST1X_SYNCPT_NB_BASES,
	.syncpt_names	= s_syncpt_names,
	.client_managed	= NVSYNCPTS_CLIENT_MANAGED,
};

static struct nvhost_device_data tegra_host1x04_info = {
	.clocks		= {{"host1x", UINT_MAX}, {} },
	NVHOST_MODULE_NO_POWERGATE_IDS,
};


static struct platform_device tegra_host1x04_device = {
	.name		= "host1x",
	.resource	= tegra_host1x04_resources,
	.num_resources	= ARRAY_SIZE(tegra_host1x04_resources),
	.dev            = {
		.platform_data = &tegra_host1x04_info,
	},
};


static struct resource isp_resources[] = {
	{
		.name = "regs",
		.start = TEGRA_ISP_BASE,
		.end = TEGRA_ISP_BASE + TEGRA_ISP_SIZE - 1,
		.flags = IORESOURCE_MEM,
	}
};

static struct nvhost_device_data tegra_isp01_info = {
	.syncpts = NV_ISP_0_SYNCPTS,
	.modulemutexes = BIT(NVMODMUTEX_ISP_0),
	.clocks = {{"isp", UINT_MAX}, {} },
	.exclusive     = true,
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.moduleid      = NVHOST_MODULE_ISP,
};
static struct platform_device tegra_isp01_device = {
	.name          = "isp",
	.resource      = isp_resources,
	.num_resources = ARRAY_SIZE(isp_resources),
	.dev           = {
		.platform_data = &tegra_isp01_info,
	},
};

static struct resource ispb_resources[] = {
	{
		.name = "regs",
		.start = TEGRA_ISPB_BASE,
		.end = TEGRA_ISPB_BASE + TEGRA_ISPB_SIZE - 1,
		.flags = IORESOURCE_MEM,
	}
};


static struct nvhost_device_data tegra_isp01b_info = {
	.syncpts = NV_ISP_1_SYNCPTS,
	.modulemutexes = BIT(NVMODMUTEX_ISP_1),
	.clocks = {{"isp.1", UINT_MAX}, {} },
	.exclusive     = true,
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.moduleid      = (1 << 16) | NVHOST_MODULE_ISP,
};

static struct platform_device tegra_isp01b_device = {
	.name          = "isp",
	.id            = 1, /* .1 on the dev node */
	.resource      = ispb_resources,
	.num_resources = ARRAY_SIZE(ispb_resources),
	.dev  = {
		.platform_data = &tegra_isp01b_info,
	},
};

static struct resource vi_resources[] = {
	{
		.name = "regs",
		.start = TEGRA_VI_BASE,
		.end = TEGRA_VI_BASE + TEGRA_VI_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
};

static struct nvhost_device_data tegra_vi01_info = {
	.syncpts       = NV_VI_0_SYNCPTS,
	.modulemutexes = BIT(NVMODMUTEX_VI_0),
	.exclusive     = true,
	.clocks = {{"vi", UINT_MAX}, {} },
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.moduleid      = NVHOST_MODULE_VI,
};


static struct platform_device tegra_vi01_device = {
	.name		= "vi",
	.resource	= vi_resources,
	.num_resources	= ARRAY_SIZE(vi_resources),
	.dev		= {
		.platform_data = &tegra_vi01_info,
	},
};

static struct nvhost_device_data tegra_vi01b_info = {
	.syncpts       = NV_VI_1_SYNCPTS,
	.modulemutexes = BIT(NVMODMUTEX_VI_1),
	.exclusive     = true,
	.clocks = {{"vi.1", UINT_MAX}, {} },
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.moduleid      = (1 << 16 | NVHOST_MODULE_VI),
};

static struct platform_device tegra_vi01b_device = {
	.name		= "vi",
	.id		= 1, /* .1 on the dev node */
	.dev		= {
		.platform_data = &tegra_vi01b_info,
	},
};

static struct resource msenc_resources[] = {
	{
		.name = "regs",
		.start = TEGRA_MSENC_BASE,
		.end = TEGRA_MSENC_BASE + TEGRA_MSENC_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
};

static struct nvhost_device_data tegra_msenc03_info = {
	.version       = NVHOST_ENCODE_MSENC_VER(3, 1),
	.syncpts       = BIT(NVSYNCPT_MSENC),
	.waitbases     = BIT(NVWAITBASE_MSENC),
	.class	       = NV_VIDEO_ENCODE_MSENC_CLASS_ID,
	.clocks = {{"msenc", UINT_MAX}, {"emc", HOST_EMC_FLOOR} },
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.exclusive     = true,
	.keepalive     = true,
	.moduleid	= NVHOST_MODULE_MSENC,
};

struct platform_device tegra_msenc03_device = {
	.name	       = "msenc",
	.resource      = msenc_resources,
	.num_resources = ARRAY_SIZE(msenc_resources),
	.dev           = {
		.platform_data = &tegra_msenc03_info,
	},
};

static struct resource tsec_resources[] = {
	{
		.name = "regs",
		.start = TEGRA_TSEC_BASE,
		.end = TEGRA_TSEC_BASE + TEGRA_TSEC_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
};

static struct nvhost_device_data tegra_tsec01_info = {
	.version       = NVHOST_ENCODE_TSEC_VER(1, 0),
	.syncpts       = BIT(NVSYNCPT_TSEC),
	.waitbases     = BIT(NVWAITBASE_TSEC),
	.class         = NV_TSEC_CLASS_ID,
	.exclusive     = true,
	.clocks = {{"tsec", UINT_MAX}, {"emc", HOST_EMC_FLOOR} },
	NVHOST_MODULE_NO_POWERGATE_IDS,
	NVHOST_DEFAULT_CLOCKGATE_DELAY,
	.moduleid      = NVHOST_MODULE_TSEC,
};

static struct platform_device tegra_tsec01_device = {
	.name		= "tsec",
	.resource	= tsec_resources,
	.num_resources	= ARRAY_SIZE(tsec_resources),
	.dev		= {
		.platform_data = &tegra_tsec01_info,
	},
};



static struct platform_device *t12_devices[] = {
	&tegra_isp01_device,
	&tegra_isp01b_device,
	&tegra_vi01_device,
	&tegra_vi01b_device,
	&tegra_msenc03_device,
	&tegra_tsec01_device,
#if defined(CONFIG_TEGRA_GK20A)
	&tegra_gk20a_device,
#endif
#if defined(CONFIG_ARCH_TEGRA_VIC)
	&tegra_vic03_device,
#endif
};


struct platform_device *tegra12_register_host1x_devices(void)
{
	int index = 0;
	struct platform_device *pdev;

	struct nvhost_device_data *pdata =
		(struct nvhost_device_data *)tegra_host1x04_device.dev.platform_data;

	nvhost_dbg_fn("");

	pdata->private_data = &host1x04_info;

	/* register host1x device first */
	platform_device_register(&tegra_host1x04_device);
	tegra_host1x04_device.dev.parent = NULL;

	/* register clients with host1x device as parent */
	for (index = 0; index < ARRAY_SIZE(t12_devices); index++) {
		pdev = t12_devices[index];
		pdev->dev.parent = &tegra_host1x04_device.dev;
		platform_device_register(pdev);
	}

	return &tegra_host1x04_device;
}

static inline void __iomem *t124_channel_aperture(void __iomem *p, int ndx)
{
	return p + (ndx * NV_HOST1X_CHANNEL_MAP_SIZE_BYTES);
}

static int t124_channel_init(struct nvhost_channel *ch,
			    struct nvhost_master *dev, int index)
{
	ch->chid = index;
	mutex_init(&ch->reflock);
	mutex_init(&ch->submitlock);

	ch->aperture = t124_channel_aperture(dev->aperture, index);

	nvhost_dbg_fn("dev=%s chid=%d ap=%p",
		      dev_name(&ch->dev->dev),
		      ch->chid,
		      ch->aperture);

	return t124_nvhost_hwctx_handler_init(ch);
}

#include "host1x/host1x_channel.c"
static int t124_channel_submit(struct nvhost_job *job)
{
	nvhost_dbg_fn("");

#if defined(CONFIG_TEGRA_GK20A)
	if (job->ch->dev == &tegra_gk20a_device)
		return gk20a_channel_submit(job);
	else
#endif
		return host1x_channel_submit(job);
}

#if defined(CONFIG_TEGRA_GK20A)
static int t124_channel_alloc_obj(struct nvhost_hwctx *hwctx,
				 struct nvhost_alloc_obj_ctx_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_alloc_obj_ctx(hwctx->priv, args);
}

static int t124_channel_free_obj(struct nvhost_hwctx *hwctx,
				struct nvhost_free_obj_ctx_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_free_obj_ctx(hwctx->priv, args);
}

static int t124_channel_alloc_gpfifo(struct nvhost_hwctx *hwctx,
				    struct nvhost_alloc_gpfifo_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_alloc_channel_gpfifo(hwctx->priv, args);
}

static int t124_channel_submit_gpfifo(struct nvhost_hwctx *hwctx,
				     struct nvhost_gpfifo *gpfifo, u32 num_entries,
				     struct nvhost_fence *fence, u32 flags)
{
	nvhost_dbg_fn("");
	return gk20a_submit_channel_gpfifo(hwctx->priv, gpfifo, num_entries,
					fence, flags);
}

static int t124_channel_wait(struct nvhost_hwctx *hwctx,
			    struct nvhost_wait_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_channel_wait(hwctx->priv, args);
}

static int t124_channel_zcull_bind(struct nvhost_hwctx *hwctx,
			    struct nvhost_zcull_bind_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_channel_zcull_bind(hwctx->priv, args);
}

static int t124_channel_zbc_set_table(struct nvhost_hwctx *hwctx,
				struct nvhost_zbc_set_table_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_channel_zbc_set_table(hwctx->priv, args);
}

static int t124_channel_zbc_query_table(struct nvhost_hwctx *hwctx,
				struct nvhost_zbc_query_table_args *args)
{
	nvhost_dbg_fn("");
	return gk20a_channel_zbc_query_table(hwctx->priv, args);
}
#endif /* CONFIG_TEGRA_GK20A */

static void t124_free_nvhost_channel(struct nvhost_channel *ch)
{
	nvhost_dbg_fn("");
	nvhost_free_channel_internal(ch, &t124_num_alloc_channels);
}

static struct nvhost_channel *t124_alloc_nvhost_channel(
		struct platform_device *dev)
{
	struct nvhost_device_data *pdata = nvhost_get_devdata(dev);
	nvhost_dbg_fn("");
	return nvhost_alloc_channel_internal(pdata->index,
		nvhost_get_host(dev)->info.nb_channels,
		&t124_num_alloc_channels);
}

int nvhost_init_t124_channel_support(struct nvhost_master *host,
       struct nvhost_chip_support *op)
{
	int i, nb_channels;
	nvhost_dbg_fn("max channels=%d devices=%d",
		      NV_HOST1X_CHANNELS,
		      ARRAY_SIZE(t12_devices));
	BUILD_BUG_ON(T124_NVHOST_NUMCHANNELS < ARRAY_SIZE(t12_devices));

	nb_channels =  ARRAY_SIZE(t12_devices);

	/* Set indices dynamically as we can have
	 * missing/non-static devices above (e.g.: vic, gk20a).
	 */

	for (i = 0; i < nb_channels; i++ ) {
		struct platform_device *dev = t12_devices[i];
		struct nvhost_device_data *pdata =
			(struct nvhost_device_data *)dev->dev.platform_data;
		pdata->index = i;
#if defined(CONFIG_ARCH_TEGRA_VIC)
		if (dev == &tegra_vic03_device) {
			pdata->modulemutexes = BIT(NVMODMUTEX_VIC);
			pdata->syncpts = BIT(NVSYNCPT_VIC);
		}
#endif
#if defined(CONFIG_TEGRA_GK20A)
		if (dev == &tegra_gk20a_device) {
			pdata->syncpts       = BIT(NVSYNCPT_3D);
			pdata->waitbases     = BIT(NVWAITBASE_3D);
			pdata->modulemutexes = BIT(NVMODMUTEX_3D);
		}
#endif
	}

	op->channel.init          = t124_channel_init;
	op->channel.submit        = t124_channel_submit;

#if defined(CONFIG_TEGRA_GK20A)
	op->channel.alloc_obj     = t124_channel_alloc_obj;
	op->channel.free_obj      = t124_channel_free_obj;
	op->channel.alloc_gpfifo  = t124_channel_alloc_gpfifo;
	op->channel.submit_gpfifo = t124_channel_submit_gpfifo;
	op->channel.wait          = t124_channel_wait;

	op->channel.zcull.bind     = t124_channel_zcull_bind;

	op->channel.zbc.set_table   = t124_channel_zbc_set_table;
	op->channel.zbc.query_table = t124_channel_zbc_query_table;
#endif
	op->nvhost_dev.alloc_nvhost_channel = t124_alloc_nvhost_channel;
	op->nvhost_dev.free_nvhost_channel = t124_free_nvhost_channel;

	return 0;
}

int t124_nvhost_hwctx_handler_init(struct nvhost_channel *ch)
{
	int err = 0;
	struct nvhost_device_data *pdata = nvhost_get_devdata(ch->dev);
	unsigned long syncpts = pdata->syncpts;
	unsigned long waitbases = pdata->waitbases;
	u32 syncpt = find_first_bit(&syncpts, BITS_PER_LONG);
	u32 waitbase = find_first_bit(&waitbases, BITS_PER_LONG);

	nvhost_dbg_fn("");

	if (pdata->alloc_hwctx_handler) {
		ch->ctxhandler = pdata->alloc_hwctx_handler(syncpt,
				waitbase, ch);
		if (!ch->ctxhandler)
			err = -ENOMEM;
	}

	return err;
}

static void t124_remove_support(struct nvhost_chip_support *op)
{
	kfree(op->priv);
	op->priv = 0;
}

#include "host1x/host1x_syncpt.c"
#include "host1x/host1x_intr.c"

int nvhost_init_t124_support(struct nvhost_master *host,
       struct nvhost_chip_support *op)
{
	int err;
	struct t124 *t124 = 0;

	/* don't worry about cleaning up on failure... "remove" does it. */
	err = nvhost_init_t124_channel_support(host, op);
	if (err)
		return err;

	err = nvhost_init_t124_cdma_support(op);
	if (err)
		return err;

	err = nvhost_init_t124_debug_support(op);
	if (err)
		return err;

	host->sync_aperture = host->aperture + HOST1X_CHANNEL_SYNC_REG_BASE;
	op->syncpt = host1x_syncpt_ops;
	op->intr = host1x_intr_ops;

	err = nvhost_memmgr_init(op);
	if (err)
		return err;

	err = nvhost_init_t124_as_support(op);
	if (err)
		return err;

	t124 = kzalloc(sizeof(struct t124), GFP_KERNEL);
	if (!t124) {
		err = -ENOMEM;
		goto err;
	}

	t124->host = host;
	op->priv = t124;
	op->remove_support = t124_remove_support;
	op->nvhost_dev.alloc_nvhost_channel = t124_alloc_nvhost_channel;
	op->nvhost_dev.free_nvhost_channel = t124_free_nvhost_channel;

	return 0;

err:
	kfree(t124);

	op->priv = 0;
	op->remove_support = 0;
	return err;
}