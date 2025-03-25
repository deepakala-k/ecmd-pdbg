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
/// @file pt_scominfo.H
/// @brief PT chip unit SCOM address platform translation code
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: Cronus, HB, HWSV
///

#ifndef PT_SCOMINFO_H
#define PT_SCOMINFO_H

// includes
#include <stdint.h>
#include <vector>
#include "pt_cu.H"
#include "pst_scominfo.H"
#include "pst_scom_addr.H"

extern "C"
{
    /// @brief Creates the actual SCOM address based on the chip unit type, instance, and the input SCOM address (relative to chip unit instance 0)
    /// @param[in] i_ptCU        Enumeration of the chip unit type
    /// @param[in] i_ecLevel      Chip EC level represented in HEX digit value.  Example: i_ecLevel = 0x12 --> EC level 1.2
    /// @param[in] i_chipUnitNum  Instance number of the chip unit
    /// @param[in] i_scomAddr     The input SCOM address associated with the chip unit type
    /// @param[in] i_mode         Translation mode, specifying different addr translation methods.
    /// @retval uint64_t Actual SCOM address for the chip unit instance passed in
    uint64_t pt_scominfo_createChipUnitScomAddr(const pstChipUnits_t i_ptCU,
            const uint8_t i_ecLevel,
            const uint8_t i_chipUnitNum,
            const uint64_t i_scomAddr,
            const pstTranslationMode_t i_mode = DEFAULT_MODE);

    /// @brief Determine if the provided SCOM address correlates to any chip units (if so creates a list of chipUnitPairing structures which correspond)
    /// @param[in] i_ptCU              Enumeration of the chip unit type
    /// @param[in] i_ecLevel            Chip EC level represented in HEX digit value.  Example: i_ecLevel = 0x12 --> EC level 1.2
    /// @param[in] i_scomAddr SCOM address to be tested
    /// @param[out] o_chipUnitRelated   Returns true if SCOM address is associated with any chip units
    /// @param[out] o_chipUnitPairing   Collection of chipUnitPairing enums
    /// @param[in] i_mode               Translation mode, specifying different addr translation methods.
    /// @retval uint32_t Return non-zero for error
    uint32_t pt_scominfo_isChipUnitScom(const pstChipUnits_t i_ptCU,
                                        const uint8_t i_ecLevel,
                                        const uint64_t i_scomAddr,
                                        bool& o_chipUnitRelated,
                                        std::vector<pst_chipUnitPairing_t>& o_chipUnitPairing,
                                        const pstTranslationMode_t i_mode = DEFAULT_MODE);

    /// @brief Alter the unit/unitnum of a target for spys where the clocks-on vs clocks-off targets are different.
    /// @param[in] i_ptCU                Target used for the spy request
    /// @param[in] i_ecLevel              Chip EC level represented in HEX digit value.  Example: i_ecLevel = 0x12 --> EC level 1.2
    /// @param[in] i_targetChipUnitNum    The instance number of the target used for the spy request
    /// @param[in] i_scomaddr             The scom from the clocks-on portion of the spy
    /// @param[out] o_modifiedScomAddr    The translated scom address (none may be needed)
    /// @param[out] o_ptCU               The translated target type
    /// @param[out] o_modifiedChipUnitNum The translated target instance number
    /// @param[in] i_mode                 Translation mode, specifying different addr translation methods.
    /// @retval uint32_t Return non-zero for error
    uint32_t pt_scominfo_fixChipUnitScomAddrOrTarget(const pstChipUnits_t i_ptCU,
            const uint8_t i_ecLevel,
            const uint32_t i_targetChipUnitNum,
            const uint64_t i_scomaddr,
            uint64_t& o_modifiedScomAddr,
            pstChipUnits_t& o_ptCU,
            uint32_t& o_modifiedChipUnitNum,
            const pstTranslationMode_t i_mode = DEFAULT_MODE);

} // extern "C"

#endif /* PT_SCOMINFO_H */
