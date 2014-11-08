/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#include "../odm_precomp.h"

#if (RTL8812A_SUPPORT == 1)

void
odm_ConfigRFReg_8812A(
	IN 	PDM_ODM_T 				pDM_Odm,
	IN 	uint32_t 					Addr,
	IN 	uint32_t 					Data,
	IN  ODM_RF_RADIO_PATH_E     RF_PATH,
	IN	uint32_t				    RegAddr
	)
{
	if(Addr == 0xfe || Addr == 0xffe)
	{
		#ifdef CONFIG_LONG_DELAY_ISSUE
		msleep(50);
		#else
		mdelay(50);
		#endif
	}
	else
	{
		ODM_SetRFReg(pDM_Odm, RF_PATH, RegAddr, bRFRegOffsetMask, Data);
		// Add 1us delay between BB/RF register setting.
		udelay(1);
	}
}


void
odm_ConfigMAC_8812A(
 	IN 	PDM_ODM_T 	pDM_Odm,
 	IN 	uint32_t 		Addr,
 	IN 	u1Byte 		Data
 	)
{
	ODM_Write1Byte(pDM_Odm, Addr, Data);
    ODM_RT_TRACE(pDM_Odm,ODM_COMP_INIT, ODM_DBG_TRACE, ("===> ODM_ConfigMACWithHeaderFile: [MAC_REG] %08X %08X\n", Addr, Data));
}

void
odm_ConfigBB_AGC_8812A(
    IN 	PDM_ODM_T 	pDM_Odm,
    IN 	uint32_t 		Addr,
    IN 	uint32_t 		Bitmask,
    IN 	uint32_t 		Data
    )
{
	ODM_SetBBReg(pDM_Odm, Addr, Bitmask, Data);
	// Add 1us delay between BB/RF register setting.
	udelay(1);

    ODM_RT_TRACE(pDM_Odm,ODM_COMP_INIT, ODM_DBG_TRACE, ("===> ODM_ConfigBBWithHeaderFile: [AGC_TAB] %08X %08X\n", Addr, Data));
}

void
odm_ConfigBB_PHY_REG_PG_8812A(
	IN 	PDM_ODM_T 	pDM_Odm,
    IN 	uint32_t 		Addr,
    IN 	uint32_t 		Bitmask,
    IN 	uint32_t 		Data
    )
{
	if (Addr == 0xfe || Addr == 0xffe) {
		#ifdef CONFIG_LONG_DELAY_ISSUE
		msleep(50);
		#else
		mdelay(50);
		#endif
	}
	else
	{
		storePwrIndexDiffRateOffset(pDM_Odm->Adapter, Addr, Bitmask, Data);
	}
	ODM_RT_TRACE(pDM_Odm,ODM_COMP_INIT, ODM_DBG_LOUD, ("===> ODM_ConfigBBWithHeaderFile: [PHY_REG] %08X %08X %08X\n", Addr, Bitmask, Data));
}

void
odm_ConfigBB_PHY_8812A(
	IN 	PDM_ODM_T 	pDM_Odm,
    IN 	uint32_t 		Addr,
    IN 	uint32_t 		Bitmask,
    IN 	uint32_t 		Data
    )
{
	if (Addr == 0xfe) {
		#ifdef CONFIG_LONG_DELAY_ISSUE
		msleep(50);
		#else
		mdelay(50);
		#endif
	}
	else if (Addr == 0xfd) {
		mdelay(5);
	}
	else if (Addr == 0xfc) {
		mdelay(1);
	}
	else if (Addr == 0xfb) {
		udelay(50);
	}
	else if (Addr == 0xfa) {
		udelay(5);
	}
	else if (Addr == 0xf9) {
		udelay(1);
	}
	else
	{
		ODM_SetBBReg(pDM_Odm, Addr, Bitmask, Data);
		// Add 1us delay between BB/RF register setting.
		udelay(1);
	}

	ODM_RT_TRACE(pDM_Odm,ODM_COMP_INIT, ODM_DBG_TRACE, ("===> ODM_ConfigBBWithHeaderFile: [PHY_REG] %08X %08X\n", Addr, Data));
}

void
odm_ConfigBB_TXPWR_LMT_8812A(
	IN 	PDM_ODM_T 	pDM_Odm,
	IN	pu1Byte		Regulation,
	IN	pu1Byte		Band,
	IN	pu1Byte		Bandwidth,
	IN	pu1Byte		RateSection,
	IN	pu1Byte		RfPath,
	IN	pu1Byte 	Channel,
	IN	pu1Byte		PowerLimit
    )
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_CE))
	PHY_SetPowerLimitTableValue(pDM_Odm, Regulation, Band,
		Bandwidth, RateSection, RfPath, Channel, PowerLimit);
#endif
}

#endif

