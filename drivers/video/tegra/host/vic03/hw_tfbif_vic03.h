/*
 * drivers/video/tegra/host/vic03/hw_tfbif_vic03.h
 *
 * Copyright (c) 2012, NVIDIA Corporation.
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
 *
 */

 /*
  * Function naming determines intended use:
  *
  *     <x>_r(void) : Returns the offset for register <x>.
  *
  *     <x>_w(void) : Returns the word offset for word (4 byte) element <x>.
  *
  *     <x>_<y>_s(void) : Returns size of field <y> of register <x> in bits.
  *
  *     <x>_<y>_f(u32 v) : Returns a value based on 'v' which has been shifted
  *         and masked to place it at field <y> of register <x>.  This value
  *         can be |'d with others to produce a full register value for
  *         register <x>.
  *
  *     <x>_<y>_m(void) : Returns a mask for field <y> of register <x>.  This
  *         value can be ~'d and then &'d to clear the value of field <y> for
  *         register <x>.
  *
  *     <x>_<y>_<z>_f(void) : Returns the constant value <z> after being shifted
  *         to place it at field <y> of register <x>.  This value can be |'d
  *         with others to produce a full register value for <x>.
  *
  *     <x>_<y>_v(u32 r) : Returns the value of field <y> from a full register
  *         <x> value 'r' after being shifted to place its LSB at bit 0.
  *         This value is suitable for direct comparison with other unshifted
  *         values appropriate for use in field <y> of register <x>.
  *
  *     <x>_<y>_<z>_v(void) : Returns the constant value for <z> defined for
  *         field <y> of register <x>.  This value is suitable for direct
  *         comparison with unshifted values appropriate for use in field <y>
  *         of register <x>.
  */

#ifndef __hw_tfbif_vic03_h__
#define __hw_tfbif_vic03_h__
/*This file is autogenerated.  Do not edit. */

static inline u32 tfbif_mccif_fifoctrl_r(void)
{
	return 0x00001604;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_f(u32 v)
{
	return (v & 0x1) << 0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_m(void)
{
	return 0x1 << 0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_v(u32 r)
{
	return (r >> 0) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_override_enable_f(void)
{
	return 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_f(u32 v)
{
	return (v & 0x1) << 1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_m(void)
{
	return 0x1 << 1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_v(u32 r)
{
	return (r >> 1) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_override_enable_f(void)
{
	return 0x2;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_f(u32 v)
{
	return (v & 0x1) << 2;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_m(void)
{
	return 0x1 << 2;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_v(u32 r)
{
	return (r >> 2) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_wrcl_mcle2x_enable_f(void)
{
	return 0x4;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_f(u32 v)
{
	return (v & 0x1) << 3;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_m(void)
{
	return 0x1 << 3;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_v(u32 r)
{
	return (r >> 3) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_rdmc_rdfast_enable_f(void)
{
	return 0x8;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_f(u32 v)
{
	return (v & 0x1) << 4;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_m(void)
{
	return 0x1 << 4;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_v(u32 r)
{
	return (r >> 4) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_wrmc_clle2x_enable_f(void)
{
	return 0x10;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_f(u32 v)
{
	return (v & 0x1) << 5;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_m(void)
{
	return 0x1 << 5;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_v(u32 r)
{
	return (r >> 5) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_rdcl_rdfast_enable_f(void)
{
	return 0x20;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_f(u32 v)
{
	return (v & 0x1) << 6;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_m(void)
{
	return 0x1 << 6;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_v(u32 r)
{
	return (r >> 6) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_cclk_override_enable_f(void)
{
	return 0x40;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_f(u32 v)
{
	return (v & 0x1) << 7;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_m(void)
{
	return 0x1 << 7;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_v(u32 r)
{
	return (r >> 7) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_rclk_ovr_mode_enable_f(void)
{
	return 0x80;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_s(void)
{
	return 1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_f(u32 v)
{
	return (v & 0x1) << 8;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_m(void)
{
	return 0x1 << 8;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_v(u32 r)
{
	return (r >> 8) & 0x1;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_init_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_init_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_disable_v(void)
{
	return 0x00000000;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_disable_f(void)
{
	return 0x0;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_enable_v(void)
{
	return 0x00000001;
}
static inline u32 tfbif_mccif_fifoctrl_wclk_ovr_mode_enable_f(void)
{
	return 0x100;
}
static inline u32 tfbif_mccif_fifoctrl1_v(void)
{
	return 0x00001634;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_s(void)
{
	return 16;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_f(u32 v)
{
	return (v & 0xffff) << 0;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_m(void)
{
	return 0xffff << 0;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_v(u32 r)
{
	return (r >> 0) & 0xffff;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_init_v(void)
{
	return 0x00000080;
}
static inline u32 tfbif_mccif_fifoctrl1_srd2mc_reorder_depth_limit_init_f(void)
{
	return 0x80;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_s(void)
{
	return 16;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_f(u32 v)
{
	return (v & 0xffff) << 16;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_m(void)
{
	return 0xffff << 16;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_v(u32 r)
{
	return (r >> 16) & 0xffff;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_init_v(void)
{
	return 0x00000040;
}
static inline u32 tfbif_mccif_fifoctrl1_swr2mc_reorder_depth_limit_init_f(void)
{
	return 0x400000;
}

#endif /* __hw_tfbif_vic03_h__ */
