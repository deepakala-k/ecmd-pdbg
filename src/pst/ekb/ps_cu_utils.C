/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* Host Firmware for POWER Systems Project                                */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2018,2024                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
///
/// @file ps_cu_utils.C
/// @brief PS chip unit utility definitions
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: CRONUS
///

// Includes
#include <ps_cu_utils.H>
#ifndef __SBE__
    #include <stdio.h>
#endif
#include <pst_scom_addr.H>

#define PS_CU_UTILS_C

extern "C"
{

// HB and SBE doesn't support string or use these functions
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))

    //################################################################################
    uint32_t ps_convertCUEnum_to_String(const pstChipUnits_t i_PSCU,
                                        std::string& o_chipUnitType)
    {
        uint8_t l_index;

        // Look for input chip unit value
        for (l_index = 0;
             l_index < (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t));
             l_index++)
        {
            if (i_PSCU == ps_ChipUnitDescriptionTable[l_index].enumVal)
            {
                // Found a match
                o_chipUnitType = ps_ChipUnitDescriptionTable[l_index].strVal;
                return 0;
            }
        }

        return 1;
    }

    //################################################################################
    uint32_t ps_convertCUString_to_enum(const std::string& i_chipUnitType,
                                        pstChipUnits_t& o_PSCU)
    {
        uint8_t l_index;

        // Look for input chip unit string
        for (l_index = 0;
             l_index < (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t));
             l_index++)
        {
            if (i_chipUnitType.compare(ps_ChipUnitDescriptionTable[l_index].strVal) == 0)
            {
                // Found a match
                o_PSCU = ps_ChipUnitDescriptionTable[l_index].enumVal;
                return 0;
            }
        }

        return 1;
    }

    //################################################################################
    void ps_displayAddrFields(uint64_t i_addr,
                              pstChipUnits_t i_chipUnitType,
                              uint32_t i_chipEcLevel)
    {
        pst_scom_addr l_scom(i_addr, PS);
        printf("\n     Chip EC: 0x%.2X\n", i_chipEcLevel);
        printf("        Addr: 0x%08lx_%08llx\n", (i_addr >> 32), (i_addr & 0xFFFFFFFFULL));
        printf("   ChipletId: 0x%02X\n", l_scom.getChipletId());
        printf("    Endpoint: 0x%02X\n", l_scom.getEndpoint());

        // Print out EQ chiplet SCOM layout depending on endpoint
        //if ( (i_chipUnitType == PS_C_CHIPUNIT) ||
        //     (i_chipUnitType == PS_EQ_CHIPUNIT) ||
        //     ((i_chipUnitType == PS_NO_CU) &&
        //      (l_scom.getChipletId() >= EQ0_CHIPLET_ID) &&
        //      (l_scom.getChipletId() <= EQ7_CHIPLET_ID)) )
        //{
        //    // QME endpoint, show QME specific fields
        //    if ( l_scom.getEndpoint() == QME_ENDPOINT )
        //    {
        //        printf("   RegionSel: 0x%.1X\n", l_scom.getRegionSelect());
        //        printf("    QME/core: 0x%.1X\n", l_scom.getQMEPerCore());
        //        printf("   QME SatEn: 0x%.1X\n", l_scom.getQMESatEn());
        //        printf("  QME SatSel: 0x%.1X\n", l_scom.getQMESatSel());
        //        printf("     QME Reg: 0x%.2X\n", l_scom.getQMEReg());
        //    }
        //    // PSCOM or PCB slave, RingId/SatId are limited
        //    else if (( l_scom.getEndpoint() == PSCOM_ENDPOINT ) ||
        //             ( l_scom.getEndpoint() == PSCOM_2_ENDPOINT ) ||
        //             ( l_scom.getEndpoint() == PCBSLV_ENDPOINT) )
        //    {
        //        printf("EQ RegionSel: 0x%.1X\n", l_scom.getRegionSelect());
        //        printf("   EQ RingId: 0x%.1X\n", l_scom.getEQRingId());
        //        printf("    EQ SatId: 0x%.1X\n", l_scom.getEQSatId());
        //        printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
        //    }
        //    else
        //    {
        //        printf("      RingId: 0x%.1X\n", l_scom.getRingId());
        //        printf("       SatId: 0x%.1X\n", l_scom.getSatId());
        //        printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
        //    }
        //}
        //else
        //{
        printf("      RingId: 0x%.1X\n", l_scom.getRingId());
        printf("       SatId: 0x%.1X\n", l_scom.getSatId());
        printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
        //}

        // Additional display for indirect SCOM
        //if ( l_scom.isIndirect() )
        //{
        //    // Display  values of the OBUS Super Wrapper (upper 32-bit)
        //    if ( l_scom.isIoHsTarget() )
        //    {
        //        printf("\nOBUS Super Wrapper:\n");
        //        printf("    Reg addr: 0x%.3X\n", l_scom.getIoRegAddr());
        //        printf("TX/RX select: 0x%.1X\n", l_scom.getIoTxRxBit());
        //        printf("  Group Addr: 0x%.2X\n", l_scom.getIoGroupAddr());
        //        printf("        Lane: 0x%.2X\n", l_scom.getIoLane());
        //    }
        //
        //    // Display  values of IOP
        //    else if ( l_scom.isPecTarget() )
        //    {
        //        printf("\nIOP Indirect:\n");
        //        printf("    Indirect CR register (12:31): 0x%.5X\n", l_scom.getIopIndCRreg());
        //        printf("    Top (53): %d\n", l_scom.getIopTop());
        //        printf("    PMA (15): %d\n", l_scom.getPMA());
        //    }
        //}

        return;
    }

#endif // __HOSTBOOT_MODULE && __SBE__

    //################################################################################
    uint8_t ps_validateChipUnitNum(const uint8_t i_chipUnitNum,
                                   const pstChipUnits_t i_chipUnitType)
    {
        uint8_t l_rc = 0;
        uint8_t l_index = 0;

        for (l_index = 0;
             l_index < (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t));
             l_index++)
        {
            // Looking for input chip unit type in table
            if (i_chipUnitType == ps_ChipUnitDescriptionTable[l_index].enumVal)
            {
                // Found a match, check input i_chipUnitNum to be <= max chip unit num
                // for this unit type
                if (i_chipUnitNum > ps_ChipUnitDescriptionTable[l_index].maxChipUnitNum)
                {
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))
                    printf("ERROR: Chip Unit num entered (%d) is out of range for Chip Unit type %d\n",
                           i_chipUnitNum, i_chipUnitType);
#endif
                    l_rc = 1;
                }

                // Additional check for PERV targets, where there are gaps between instances
                else if (i_chipUnitType == PERV_CHIPUNIT)
                {
                    if ( ((i_chipUnitNum > 0x01) && (i_chipUnitNum < 0x04)) ||
                         ((i_chipUnitNum > 0x06) && (i_chipUnitNum < 0x08)) ||
                         ((i_chipUnitNum > 0x0B) && (i_chipUnitNum < 0x10)) ||
                         ((i_chipUnitNum > 0x1B) && (i_chipUnitNum < 0x20)) ||
                         ((i_chipUnitNum > 0x25) && (i_chipUnitNum < 0x28)) ||
                         ((i_chipUnitNum > 0x2B)) )
                    {
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))
                        printf("ERROR: Pervasive Chip Unit number is invalid: 0x%.8X\n", i_chipUnitNum);
#endif
                        l_rc = 1;
                    }
                }

                // Found matched chip unit type, break out, error or not
                break;
            }
        }

        // Can't find i_chipUnitType in table
        if (l_index >= (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t)) )
        {
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))
            printf("ERROR: Invalid chip unit type: %d\n", i_chipUnitType);
#endif
            l_rc = 1;
        }

        return (l_rc);
    }

    //################################################################################
    uint8_t ps_getNumChipUnits(const pstChipUnits_t i_chipUnitType,
                               uint8_t& o_numChipUnits)
    {
        uint8_t l_rc = 0;
        uint8_t l_index = 0;
        o_numChipUnits = 0;

        for (l_index = 0;
             l_index < (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t));
             l_index++)
        {
            // Looking for input chip unit type in table
            if (i_chipUnitType == ps_ChipUnitDescriptionTable[l_index].enumVal)
            {
                if (i_chipUnitType == PERV_CHIPUNIT)
                {
                    o_numChipUnits = 1;
                }
                else
                {
                    o_numChipUnits = 1 + ps_ChipUnitDescriptionTable[l_index].maxChipUnitNum;
                }

                // Found matched chip unit type, break out, error or not
                break;
            }
        }

        // Can't find i_chipUnitType in table
        if (l_index >= (sizeof(ps_ChipUnitDescriptionTable) / sizeof(ps_chipUnitDescription_t)) )
        {
            l_rc = 1;
        }

        return (l_rc);
    }

} // extern "C"

#undef PS_CU_UTILS_C
