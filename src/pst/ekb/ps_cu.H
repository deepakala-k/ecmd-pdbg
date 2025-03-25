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
/// @file ps_cu.H
/// @brief PS chip unit definitions
///
/// HWP Owner: thi@us.ibm.com
/// HWP Team: NEST
/// HWP Level: 1
/// HWP Consumed by: HB
///

#ifndef PS_CU_H
#define PS_CU_H

// includes
#include <stdint.h>
#include <pst_cu.H>

extern "C"
{

    struct ps_chipUnitDescription_t
    {
        const char*          strVal;          // Chip unit string
        const pstChipUnits_t enumVal;         // Chip unit enum value
        const uint8_t        maxChipUnitNum;  // Max Chip unit num value
    };


    // Max chip unit positions
    const uint8_t MAX_PS_CHIPUNIT_NUM      =  0;  // PS_NO_CU

    // Total Spinal pervasive chip unit number
    // TODO: Need to revisit this, for now based on
    //       https://ibm.ent.box.com/notes/880374816574?s=7j76zf4d1ss89ifywtxt7s717ee0r70d
    // and   https://ibm.ent.box.com/file/871932308581?s=pt9slhzztv397wozbrt644gejzze00sk
    //
    // Spinal pervasive chiplets (0x00, 0x01) ph.perv                              2
    // Spinal nest chiplets (0x04-0x06), ph.int, ph.nx, ph.pau                     3
    // Spinal memory chiplets (0x08-0x0B), ph.m[ci], ph.mcc, ph.omic, ph.omi       4
    // Spinal pax chiplets (0x10-0x1B), ph.pax, ph.paxo                           12
    // Spinal pci chiplets (0x20-0x25), ph.pec2p, ph.pec6p, ph.phb248x, ph.phb16x  6
    // Spinal TBUS chiplets (0x28-0x2B), ph.tbusc, ph.tbusl                        4
    const uint8_t MAX_PH_PERV_CHIPUNIT_NUM     = 0x2B;
    const uint8_t MAX_PH_TBUSL_CHIPUNIT_NUM    = 7;
    const uint8_t MAX_PH_TBUS_CHIPUNIT_NUM     = 3;
    const uint8_t MAX_PH_PAU_CHIPUNIT_NUM      = 7;
    const uint8_t MAX_PH_INT_CHIPUNIT_NUM      = 1;
    const uint8_t MAX_PH_NX_CHIPUNIT_NUM       = 1;
    const uint8_t MAX_PH_MC_CHIPUNIT_NUM       = 3;
    const uint8_t MAX_PH_MI_CHIPUNIT_NUM       = 7;
    const uint8_t MAX_PH_MCC_CHIPUNIT_NUM      = 15;
    const uint8_t MAX_PH_OMIC_CHIPUNIT_NUM     = 3;
    const uint8_t MAX_PH_OMI_CHIPUNIT_NUM      = 31;
    const uint8_t MAX_PH_IOHS_CHIPUNIT_NUM     = 11;
    const uint8_t MAX_PH_PAX_CHIPUNIT_NUM      = 7;
    const uint8_t MAX_PH_PAXO_CHIPUNIT_NUM     = 3;
    const uint8_t MAX_PH_SMPLINK_CHIPUNIT_NUM  = 23;
    const uint8_t MAX_PH_PEC6P_CHIPUNIT_NUM    = 3;
    const uint8_t MAX_PH_PEC2P_CHIPUNIT_NUM    = 1;
    const uint8_t MAX_PH_PHB248X_CHIPUNIT_NUM  = 23;
    const uint8_t MAX_PH_PHB16X_CHIPUNIT_NUM   = 5;


    // Chip unit string/enum/max targes table
    const ps_chipUnitDescription_t ps_ChipUnitDescriptionTable[] =
    {
        { "ps"    , NO_CU,               MAX_PS_CHIPUNIT_NUM          },
        { "perv"    , PERV_CHIPUNIT,       MAX_PH_PERV_CHIPUNIT_NUM       },  // Special case, with gaps
        { "tbusl"   , TBUSL_CHIPUNIT,      MAX_PH_TBUSL_CHIPUNIT_NUM      },
        { "tbusc"   , TBUS_CHIPUNIT,       MAX_PH_TBUS_CHIPUNIT_NUM      },
        { "pau"     , PAU_CHIPUNIT,        MAX_PH_PAU_CHIPUNIT_NUM        },
        { "int"     , INT_CHIPUNIT,        MAX_PH_INT_CHIPUNIT_NUM        },
        { "nx"      , NX_CHIPUNIT,         MAX_PH_NX_CHIPUNIT_NUM         },
        { "mc"      , MC_CHIPUNIT,         MAX_PH_MC_CHIPUNIT_NUM         },
        { "mi"      , MI_CHIPUNIT,         MAX_PH_MI_CHIPUNIT_NUM         },
        { "mcc"     , MCC_CHIPUNIT,        MAX_PH_MCC_CHIPUNIT_NUM        },
        { "omic"    , OMIC_CHIPUNIT,       MAX_PH_OMIC_CHIPUNIT_NUM       },
        { "omi"     , OMI_CHIPUNIT,        MAX_PH_OMI_CHIPUNIT_NUM        },
        { "iohs"    , IOHS_CHIPUNIT,       MAX_PH_IOHS_CHIPUNIT_NUM       },
        { "pax"     , PAX_CHIPUNIT,        MAX_PH_PAX_CHIPUNIT_NUM        },
        { "paxo"    , PAXO_CHIPUNIT,       MAX_PH_PAXO_CHIPUNIT_NUM       },
        { "smplink" , SMPLINK_CHIPUNIT,    MAX_PH_SMPLINK_CHIPUNIT_NUM    },
        { "pec2p"   , PEC2P_CHIPUNIT,      MAX_PH_PEC2P_CHIPUNIT_NUM      },
        { "pec6p"   , PEC6P_CHIPUNIT,      MAX_PH_PEC6P_CHIPUNIT_NUM      },
        { "phb248x" , PHB248X_CHIPUNIT,    MAX_PH_PHB248X_CHIPUNIT_NUM    },
        { "phb16x"  , PHB16X_CHIPUNIT,     MAX_PH_PHB16X_CHIPUNIT_NUM     },
    };

} // extern "C"

#endif /* PS_CU_H */
