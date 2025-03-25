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
/// @file pst_cu.H
/// @brief PST chip unit definitions
///
/// HWP Owner: thi@us.ibm.com
/// HWP Team: NEST
/// HWP Level: 1
/// HWP Consumed by: FSP/HB
///

#ifndef PST_CU_H
#define PST_CU_H

// includes
#include <stdint.h>

extern "C"
{

    /// PST chip unit type enumeration
    typedef enum
    {
        ///< | T | S |
        NO_CU                    =  0,           ///< | x | x |PST chip
        PERV_CHIPUNIT            =  1,           ///< | x | x |Pervasive
        EQ_CHIPUNIT              =  2,           ///< | x |   |EQ chiplet, qme, clkadj
        C_CHIPUNIT               =  3,           ///< | x |   |Core, L2, mma
        L3_CHIPUNIT              =  4,           ///< | x |   |L3Cache Only
        TBUSL_CHIPUNIT           =  5,           ///< | x | x |Tbus logical
        TBUS_CHIPUNIT            =  6,           ///< |   | x |Tbus, Spinal only
        PAU_CHIPUNIT             =  7,           ///< |   | x |(8) Common queue + address xlate for pci/ocapi, with cache 4 per north/south
        INT_CHIPUNIT             =  8,           ///< |   | x |(2) in center
        NX_CHIPUNIT              =  9,           ///< |   | x |(2) 1 per north/south
        MC_CHIPUNIT              = 10,           ///< |   | x |(4)
        MI_CHIPUNIT              = 11,           ///< |   | x |
        MCC_CHIPUNIT             = 12,           ///< |   | x |
        OMIC_CHIPUNIT            = 13,           ///< |   | x |
        OMI_CHIPUNIT             = 14,           ///< |   | x |
        IOHS_CHIPUNIT            = 15,           ///< |   | x |
        PAX_CHIPUNIT             = 16,           ///< |   | x |(8) iohs 0..7
        PAXO_CHIPUNIT            = 17,           ///< |   | x |(4) PAX with OCAPI support iohs 8..11
        SMPLINK_CHIPUNIT         = 18,           ///< |   | x |(24) 2 per PAX/PAXO
        PEC2P_CHIPUNIT           = 19,           ///< |   | x |(2) Each supports 2 16x phbs
        PEC6P_CHIPUNIT           = 20,           ///< |   | x |(4) Each supports 6 2x,4x,8x phbs
        PHB248X_CHIPUNIT         = 21,           ///< |   | x |(24) 2x,4x,8x phbs
        PHB16X_CHIPUNIT          = 22,           ///< |   | x |(6) 16x phbs
        PST_NONE                 = 0xFF,         ///< | x | x |None/Invalid
    } pstChipUnits_t;

    /// PST chip unit pairing struct
    struct pst_chipUnitPairing_t
    {
        /// @brief Default constructor
        pst_chipUnitPairing_t()
            : chipUnitType(PST_NONE), chipUnitNum(0) {}
        /// @brief Construct from type/instance number
        pst_chipUnitPairing_t (pstChipUnits_t type, uint32_t num)
            : chipUnitType(type), chipUnitNum(num) {}

        pstChipUnits_t chipUnitType;  ///< chip unit type
        uint8_t chipUnitNum;          ///< chip unit instance number
    };

} // extern "C"

#endif /* PST_CU_H */
