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
/// @file pt_cu.H
/// @brief PT chip unit definitions
///
/// HWP Owner: thi@us.ibm.com
/// HWP Team: NEST
/// HWP Level: 1
/// HWP Consumed by: FSP/HB
///

#ifndef PT_CU_H
#define PT_CU_H

// includes
#include <stdint.h>
#include <pst_cu.H>

extern "C"
{

// DEBUG_PRINT flag can be enabled in pt_scom/scan_xlate.mk
// to enable debug print for odyssey's clock, scom, scan code.
#if DEBUG_PRINT
#define dbg_print printf
#else
#define dbg_print(...) /**/
#endif

    struct pt_chipUnitDescription_t
    {
        const char*          strVal;          // Chip unit string
        const pstChipUnits_t enumVal;         // Chip unit enum value
        const uint8_t        maxChipUnitNum;  // Max Chip unit num value
    };


    // Max chip unit positions
    const uint8_t MAX_PT_CHIPUNIT_NUM      =  0; // PT_NO_CU

    // TODO: Need to revisit this, for now based on
    //       https://ibm.ent.box.com/notes/880374816574?s=7j76zf4d1ss89ifywtxt7s717ee0r70d
    // and   https://ibm.ent.box.com/file/871932308581?s=pt9slhzztv397wozbrt644gejzze00sk
    //
    // Pervasive Chiplets(0x00-0x01), pc.perv     1  //  No support for pc.perv–c0 (FSI) given lack of commonality to rest of chipletdesigns
    // Nest chiplet (0x02)                        1
    // Tap TBUSL (0x03), pc.tbusl                 1
    // Tap EQ chiplets (0x20-0x21), pc.eq         2
    const uint8_t MAX_PC_PERV_CHIPUNIT_NUM   =  0x21; // Special case, with gaps
    const uint8_t MAX_PC_EQ_CHIPUNIT_NUM     =  1; // EQ00, EQ01, QME
    const uint8_t MAX_PC_C_CHIPUNIT_NUM      =  7; // Each EQ contains 4 cores/l2/mma
    const uint8_t MAX_PC_L3_CHIPUNIT_NUM     =  7; // Each EQ contains 4 L3s
    const uint8_t MAX_PC_TBUSL_CHIPUNIT_NUM  =  0; // Only one TBUSL, convenience for tbus proc commonality

    // Chip unit string/enum/max targes table
    const pt_chipUnitDescription_t pt_ChipUnitDescriptionTable[] =
    {
        { "pt"    , NO_CU,           MAX_PT_CHIPUNIT_NUM       },
        { "perv"    , PERV_CHIPUNIT,   MAX_PC_PERV_CHIPUNIT_NUM    },  // Special case, with gaps
        { "eq"      , EQ_CHIPUNIT,     MAX_PC_EQ_CHIPUNIT_NUM      },
        { "c"       , C_CHIPUNIT,      MAX_PC_C_CHIPUNIT_NUM       },
        { "l3"      , L3_CHIPUNIT,     MAX_PC_L3_CHIPUNIT_NUM      },
        { "tbusl"   , TBUSL_CHIPUNIT,  MAX_PC_TBUSL_CHIPUNIT_NUM   },
    };

} // extern "C"

#endif /* PT_CU_H */
