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
/// @file ps_cu_utils.H
/// @brief PS chip unit utility definitions
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: CRONUS
///

#ifndef PS_CU_UTILS_H
#define PS_CU_UTILS_H

// includes
//HB and SBE doesn't support string
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))
    #include <string>
#endif
#include <ps_cu.H>

extern "C"
{
// HB and SBE doesn't support string or use these functions
#if (!defined(__SBE__) && !defined(__HOSTBOOT_MODULE))

    /// @brief Convert chip unit enumeration to string
    /// @param[in]  i_PSCU Enumeration of chip unit type
    /// @param[out] o_chipUnitType String description of chip unit type
    /// @retval uint32_t Return non-zero for error
    uint32_t ps_convertCUEnum_to_String(const pstChipUnits_t i_PSCU,
                                        std::string& o_chipUnitType);

    /// @brief Convert string description of chip unit type to enumeration
    /// @param[in]  i_chipUnitType String description of chip unit type
    /// @param[out] o_PSCU Enumeration of chip unit type
    /// @retval uint32_t Return non-zero for error
    uint32_t ps_convertCUString_to_enum(const std::string& i_chipUnitType,
                                        pstChipUnits_t& o_PSCU);

#endif

    /// @brief Debug utility that prints out address fields
    /// @param[in] i_addr         Address value
    /// @param[in] i_chipUnitType Chip unit type
    /// @param[in] i_chipEcLevel  Chip EC level
    /// @retval None
    void ps_displayAddrFields(uint64_t i_addr,
                              pstChipUnits_t i_chipUnitType,
                              uint32_t i_chipEcLevel);

    /// @brief Validate the chip unit number to be within range
    ///        of a chip unit type.
    /// @param[in] i_chipUnitNum   Value of chip unit number (instance)
    /// @param[in] i_chipUnitType  Chip unit type
    /// @retval Non-zero if error
    uint8_t ps_validateChipUnitNum(const uint8_t i_chipUnitNum,
                                   const pstChipUnits_t i_chipUnitType);

    /// @brief Return the number of chip unit instances associated with
    ///        the provided chip unit type
    /// @param[in] i_chipUnitType  Chip unit type
    /// @param[in] o_numChipUnits  Count of valid chip unit instances
    /// @retval Non-zero if error
    uint8_t ps_getNumChipUnits(const pstChipUnits_t i_chipUnitType,
                               uint8_t& o_numChipUnits);

} // extern "C"

#endif /* PS_CU_UTILS_H */
