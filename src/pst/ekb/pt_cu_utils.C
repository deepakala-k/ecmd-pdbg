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
/// @file pt_cu_utils.C
/// @brief PT chip unit utility definitions
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: CRONUS
///

// Includes
#include <pt_cu_utils.H>
#include <pst_scominfo.H>
#ifndef __SBE__
    #include <stdio.h>
#endif

#define PT_CU_UTILS_C

extern "C"
{

// HB and SBE doesn't support string or use these functions
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))

    //################################################################################
    uint32_t pt_convertCUEnum_to_String(const pstChipUnits_t i_PTCU,
                                        std::string& o_chipUnitType)
    {
        uint8_t l_index;

        // Look for input chip unit value
        for (l_index = 0;
             l_index < (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t));
             l_index++)
        {
            if (i_PTCU == pt_ChipUnitDescriptionTable[l_index].enumVal)
            {
                // Found a match
                o_chipUnitType = pt_ChipUnitDescriptionTable[l_index].strVal;
                return 0;
            }
        }

        return 1;
    }

    //################################################################################
    uint32_t pt_convertCUString_to_enum(const std::string& i_chipUnitType,
                                        pstChipUnits_t& o_PTCU)
    {
        uint8_t l_index;

        // Look for input chip unit string
        for (l_index = 0;
             l_index < (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t));
             l_index++)
        {
            if (i_chipUnitType.compare(pt_ChipUnitDescriptionTable[l_index].strVal) == 0)
            {
                // Found a match
                o_PTCU = pt_ChipUnitDescriptionTable[l_index].enumVal;
                return 0;
            }
        }

        return 1;
    }

    //################################################################################
    void pt_displayAddrFields(uint64_t i_addr,
                              pstChipUnits_t i_chipUnitType,
                              uint32_t i_chipEcLevel)
    {
        pst_scom_addr l_scom(i_addr, PT);

        printf("\n     Chip EC: 0x%.2X\n", i_chipEcLevel);
        printf("        Addr: 0x%08lx_%08llx\n", (i_addr >> 32), (i_addr & 0xFFFFFFFFULL));
        printf("   ChipletId: 0x%02X\n", l_scom.getChipletId());
        printf("    Endpoint: 0x%02X\n", l_scom.getEndpoint());

        // Print out EQ chiplet SCOM layout depending on endpoint
        if ( (i_chipUnitType == C_CHIPUNIT) ||
             (i_chipUnitType == EQ_CHIPUNIT) ||
             (i_chipUnitType == L3_CHIPUNIT) ||
             ((i_chipUnitType == NO_CU) &&
              (l_scom.getChipletId() >= (int)ptChipletId_t::EQ0_CHIPLET_ID) &&
              (l_scom.getChipletId() <= (int)ptChipletId_t::EQ1_CHIPLET_ID)) )
        {
            // QME endpoint, show QME specific fields
            if ( l_scom.getEndpoint() == QME_ENDPOINT )
            {
                printf("   RegionSel: 0x%.1X\n", l_scom.getRegionSelect());
                printf("    QME/core: 0x%.1X\n", l_scom.getQMEPerCore());
                printf("   QME SatEn: 0x%.1X\n", l_scom.getQMESatEn());
                printf("  QME SatSel: 0x%.1X\n", l_scom.getQMESatSel());
                printf("     QME Reg: 0x%.2X\n", l_scom.getQMEReg());
            }
            // PSCOM or PCB slave, RingId/SatId are limited
            else if (( l_scom.getEndpoint() == PSCOM_ENDPOINT ) ||
                     ( l_scom.getEndpoint() == PSCOM_2_ENDPOINT ) ||
                     ( l_scom.getEndpoint() == PCBSLV_ENDPOINT) )
            {
                printf("EQ RegionSel: 0x%.1X\n", l_scom.getRegionSelect());
                printf("   EQ RingId: 0x%.1X\n", l_scom.getEQRingId());
                printf("    EQ SatId: 0x%.1X\n", l_scom.getEQSatId());
                printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
            }
            else
            {
                printf("      RingId: 0x%.1X\n", l_scom.getRingId());
                printf("       SatId: 0x%.1X\n", l_scom.getSatId());
                printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
            }
        }
        else
        {
            printf("      RingId: 0x%.1X\n", l_scom.getRingId());
            printf("       SatId: 0x%.1X\n", l_scom.getSatId());
            printf("      SatReg: 0x%.2X\n", l_scom.getSatOffset());
        }

        // Additional display for indirect SCOM
        if ( l_scom.isIndirect() )
        {
            // Display  values of the TBUS link
            if ( l_scom.isTbuslTarget() )
            {
// TODO - Need to decode indirect address for TBUS link I/O logic
#if 0
                printf("\nOBUS Super Wrapper:\n");
                printf("    Reg addr: 0x%.3X\n", l_scom.getIoRegAddr());
                printf("TX/RX select: 0x%.1X\n", l_scom.getIoTxRxBit());
                printf("  Group Addr: 0x%.2X\n", l_scom.getIoGroupAddr());
                printf("        Lane: 0x%.2X\n", l_scom.getIoLane());
#endif
            }
        }

        return;
    }

#endif //__HOSTBOOT_MODULE && __SBE__

    //################################################################################
    uint8_t pt_validateChipUnitNum(const uint8_t i_chipUnitNum,
                                   const pstChipUnits_t i_chipUnitType)
    {
        uint8_t l_rc = 0;
        uint8_t l_index;

        for (l_index = 0;
             l_index < (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t));
             l_index++)
        {
            // Looking for input chip unit type in table
            if (i_chipUnitType == pt_ChipUnitDescriptionTable[l_index].enumVal)
            {
                // Found a match, check input i_chipUnitNum to be <= max chip unit num
                // for this unit type
                if (i_chipUnitNum > pt_ChipUnitDescriptionTable[l_index].maxChipUnitNum)
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
                    if ( ((i_chipUnitNum > 0x03) && (i_chipUnitNum < 0x20)) ||
                         ((i_chipUnitNum > 0x21)) )
                    {
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))
                        printf("ERROR: Pervasive Chip Unit number is invalid: 0x%.8X\n", i_chipUnitNum);
#endif
                        l_rc = 1;
                    }
                }

                break;
            }
        }

        // Can't find i_chipUnitType in table
        if ( l_index >= (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t)) )
        {
            l_rc = 1;
        }

        return (l_rc);
    }

    //################################################################################
    uint8_t pt_getNumChipUnits(const pstChipUnits_t i_chipUnitType,
                               uint8_t& o_numChipUnits)
    {
        uint8_t l_rc = 0;
        uint8_t l_index;

        for (l_index = 0;
             l_index < (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t));
             l_index++)
        {
            // Looking for input chip unit type in table
            if (i_chipUnitType == pt_ChipUnitDescriptionTable[l_index].enumVal)
            {
                if (i_chipUnitType == PERV_CHIPUNIT)
                {
                    o_numChipUnits = 1;
                }
                else
                {
                    o_numChipUnits = 1 + pt_ChipUnitDescriptionTable[l_index].maxChipUnitNum;
                }

                break;
            }
        }

        // Can't find i_chipUnitType in table
        if ( l_index >= (sizeof(pt_ChipUnitDescriptionTable) / sizeof(pt_chipUnitDescription_t)) )
        {
            l_rc = 1;
        }

        return (l_rc);
    }

} // extern "C"

#undef PT_CU_UTILS_C
