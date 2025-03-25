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
/// @file pt_scominfo.C
/// @brief PT chip unit SCOM address platform translation code
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: Cronus, HB, HWSV
///

// includes
#include <pt_scominfo.H>
#include <pst_scom_addr.H>
#include <pt_cu_utils.H>

#define PT_SCOMINFO_C

extern "C"
{

    //################################################################################
    /// @brief Calculate the region select (core ID) value for given core
    ///        instance
    /// @param[in] i_coreInstance   Core instance number (0-7)
    /// @retval uint8_t Region select value
    uint8_t pst_calcRegionSelect(uint8_t i_coreInstanceNum)
    {
        uint8_t l_regionSel = 0;

        if (i_coreInstanceNum % NUM_CORES_PER_EQ == 0)
        {
            l_regionSel = MULTI_HOT_SELECT_C0;
        }
        else if (i_coreInstanceNum % NUM_CORES_PER_EQ == 1)
        {
            l_regionSel = MULTI_HOT_SELECT_C1;
        }
        else if (i_coreInstanceNum % NUM_CORES_PER_EQ == 2)
        {
            l_regionSel = MULTI_HOT_SELECT_C2;
        }
        else
        {
            l_regionSel = MULTI_HOT_SELECT_C3;
        }

        return l_regionSel;
    }


    //################################################################################
    // See header file for function description
    uint64_t pt_scominfo_createChipUnitScomAddr(
        const pstChipUnits_t i_ptCU,
        const uint8_t i_ecLevel,
        const uint8_t i_chipUnitNum,
        const uint64_t i_scomAddr,
        const pstTranslationMode_t i_mode)
    {
        uint8_t l_rc = 0;
        pst_scom_addr l_scom(i_scomAddr, PT);
        uint8_t l_chipletId = 0;

        do
        {
            // Make sure i_chipUnitNum is within range
            l_rc = pt_validateChipUnitNum(i_chipUnitNum, i_ptCU);

            if (l_rc)
            {
                break;
            }

            // If chip unit type is a chip, return input address
            if (i_ptCU == NO_CU)
            {
                l_scom.setAddr(i_scomAddr);
                break;
            }

            // Set the chiplet ID
            l_rc = l_scom.getChipletId(i_chipUnitNum, i_ptCU, l_chipletId);

            if (l_rc)
            {
                break;
            }

            l_scom.setChipletId(l_chipletId);

            // Set other address fields (ringId, satId, etc...)
            // for Chip unit types that are needed.
            switch (i_ptCU)
            {
                case TBUSL_CHIPUNIT:
                    l_scom.setTbuslGroup(i_chipUnitNum);
                    break;


                case C_CHIPUNIT:
                    // Set the core's region select (core ID)
                    l_scom.setRegionSelect(pst_calcRegionSelect(i_chipUnitNum));
                    break;

                case L3_CHIPUNIT:
                    // Set the core's region select (core ID)
                    l_scom.setRegionSelect(pst_calcRegionSelect(i_chipUnitNum));
                    break;

                default:
                    break;
            }

        }
        while (0);

        if (l_rc)
        {
            l_scom.setAddr(PST_FAILED_TRANSLATION);
        }

        return l_scom.getAddr();
    }

    //################################################################################
    // See header file for function description
    uint32_t pt_scominfo_isChipUnitScom(const pstChipUnits_t i_ptCU,
                                        const uint8_t i_ecLevel,
                                        const uint64_t i_scomAddr,
                                        bool& o_chipUnitRelated,
                                        std::vector<pst_chipUnitPairing_t>& o_chipUnitPairing,
                                        const pstTranslationMode_t i_mode)
    {
        uint32_t l_rc = 0;
        pst_scom_addr l_addr(i_scomAddr, PT);
        o_chipUnitRelated = false;
        o_chipUnitPairing.clear();


        // force ENGD_BUILD_MODE to align to EQ scan rings where appropriate
        bool l_engd_build_force_to_eq =
            (i_mode == ENGD_BUILD_MODE) &&
            (l_addr.isEQPerSliceRegister() || // QME (per-slice), PSCOM (perv ring, DCADJ/SKEWADJ sats)
             l_addr.isEQPerL3Register());     // PSCOM (pscom ring, or perv ring all sats)

        bool l_engd_build_force_to_chip =
            (i_mode == ENGD_BUILD_MODE) &&
            (l_addr.getEndpoint() == PCBSLV_ENDPOINT);

        // Quad registers which can be addressed by EQ target type
        if ((l_addr.isEqTarget() ||
             l_engd_build_force_to_eq) &&
            !l_engd_build_force_to_chip)
        {
            o_chipUnitRelated = true;
            // PU_EQ_CHIPUNIT
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(EQ_CHIPUNIT,
                                        l_addr.getEqTargetInstance()));
        }

        // Core, L2 registers which can be addressed by core target type
        // prevent matching on registers associated with EQ scan rings, in ENGD build mode
        if (l_addr.isCoreTarget() &&
            !l_engd_build_force_to_eq)
        {
            o_chipUnitRelated = true;
            // C_CHIPUNIT
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(C_CHIPUNIT,
                                        l_addr.getCoreTargetInstance()));
        }

        // L3,NCU registers which can be addressed by L3 target type
        // prevent matching on registers associated with EQ scan rings, in ENGD build mode
        if (l_addr.isL3Target() &&
            !l_engd_build_force_to_eq)
        {
            o_chipUnitRelated = true;
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(L3_CHIPUNIT,
                                        l_addr.getCoreTargetInstance()));
        }

        // TBUSL registers
        // all are associated with TBUS chiplet scan rings, flat to chip, in ENGD build mode
        if (l_addr.isTbuslTarget() &&
            (i_mode != ENGD_BUILD_MODE))
        {
            o_chipUnitRelated = true;
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(TBUSL_CHIPUNIT,
                                        l_addr.getTbusTargetInstance()));
        }

        //This must be done last!!!
        if (l_addr.isPervTarget() &&
            (i_mode != ENGD_BUILD_MODE))
        {
            l_addr.pervChipUnitScom(i_ecLevel, o_chipUnitRelated, o_chipUnitPairing, i_mode);
        }

        return l_rc;
    }

    //################################################################################
    uint32_t pt_scominfo_fixChipUnitScomAddrOrTarget(const pstChipUnits_t i_ptCU,
            const uint8_t i_ecLevel,
            const uint32_t i_targetChipUnitNum,
            const uint64_t i_scomaddr,
            uint64_t& o_modifiedScomAddr,
            pstChipUnits_t& o_ptCU,
            uint32_t& o_modifiedChipUnitNum,
            const pstTranslationMode_t i_mode)
    {
        uint32_t l_rc = 0;

        o_modifiedScomAddr = i_scomaddr;
        o_ptCU = i_ptCU;
        o_modifiedChipUnitNum = i_targetChipUnitNum;

        return l_rc;
    }

} // extern "C"

#undef PT_SCOMINFO_C
