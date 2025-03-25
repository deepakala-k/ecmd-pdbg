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
/// @file pst_scom_addr.C
/// @brief PST chip unit SCOM address platform translation code
///
/// HWP HW Maintainer: Thi Tran <thi@us.ibm.com>
/// HWP FW Maintainer:
/// HWP Consumed by: Cronus, HB
///

// includes
#include "pst_scom_addr.H"
#include "pt_cu.H"
#include "ps_cu.H"

#define PST_SCOM_ADDR_C

extern "C"
{
    // #####################################
    bool pst_scom_addr::isTbuslTarget()
    {
        bool l_tbuslTarget = false;

        // Tap chip
        // There's no TBUS, only one TBUSL
        if (iv_chip_type == pstChipTypes_t::PT)
        {
            // TBUSL if chiplet id == 0x03
            if (getChipletId() == (uint8_t)ptChipletId_t::TBUS0_CHIPLET_ID)
            {
                l_tbuslTarget = isIndirect();
            }
        }
        // Spinal chip
        // 4 TBUS, each has 2 TBUSLs
        else
        {
            // TBUSL if 0x28 <= chiplet id <= 0x2B
            if (getChipletId() >= (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID &&
                getChipletId() <= (uint8_t)psChipletId_t::TBUS3_CHIPLET_ID )
            {
                if ( (getEndpoint() == CHIPLET_CTRL_ENDPOINT) || // 0x0
                     (getEndpoint() == PSCOM_ENDPOINT) ||        // 0x1
                     (getEndpoint() == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                     (getEndpoint() == FIR_ENDPOINT) ||          // 0x4
                     (getEndpoint() == THERMAL_ENDPOINT) ||      // 0x5
                     (getEndpoint() == PCBSLV_ENDPOINT) )        // 0xF
                {
                    if (isIndirect())
                    {
                        l_tbuslTarget = isIndirect();
                    }
                    else if ( (getRingId() == TBUS_RING_SF0) ||
                              (getRingId() == TBUS_RING_SF1) )
                    {
                        l_tbuslTarget = true;
                    }
                }
            }
        }

        return l_tbuslTarget;
    }

    // #####################################
    bool pst_scom_addr::isTbusTarget()
    {
        // Note: there's no TBUS chiplet in Tap
        bool l_tbusTarget = false;

        // Spinal
        if (iv_chip_type == pstChipTypes_t::PS)
        {
            // SPINAL::TBUS chiplet ids (0x28-0x2B)
            if (getChipletId() >= (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID &&
                getChipletId() <= (uint8_t)psChipletId_t::TBUS3_CHIPLET_ID )
            {
                if ( (getEndpoint() == CHIPLET_CTRL_ENDPOINT) || // 0x0
                     (getEndpoint() == PSCOM_ENDPOINT) ||        // 0x1
                     (getEndpoint() == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                     (getEndpoint() == FIR_ENDPOINT) ||          // 0x4
                     (getEndpoint() == THERMAL_ENDPOINT) ||      // 0x5
                     (getEndpoint() == PCBSLV_ENDPOINT) )        // 0xF

                {
                    if ( (!isIndirect()) &&
                         (getRingId() != TBUS_RING_SF0) &&
                         (getRingId() != TBUS_RING_SF1) )
                    {
                        l_tbusTarget = true;
                    }
                }
            }
        }

        return l_tbusTarget;
    }


    // #####################################
    bool pst_scom_addr::isPaxTarget()
    {
        bool l_paxTarget = false;

        if (iv_chip_type == pstChipTypes_t::PS)
        {
            if ( (getChipletId() >= (uint8_t)psChipletId_t::PX00_CHIPLET_ID) &&
                 (getChipletId() <= (uint8_t)psChipletId_t::PX07_CHIPLET_ID) )
            {
                if ( (getEndpoint() == CHIPLET_CTRL_ENDPOINT) || // 0x0
                     (getEndpoint() == PSCOM_ENDPOINT) ||        // 0x1
                     (getEndpoint() == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                     (getEndpoint() == FIR_ENDPOINT) ||          // 0x4
                     (getEndpoint() == THERMAL_ENDPOINT) ||      // 0x5
                     (getEndpoint() == PCBSLV_ENDPOINT) )        // 0xF
                {
                    l_paxTarget = true;
                }
            }

            else if ( getChipletId() == (uint8_t)psChipletId_t::N0_CHIPLET_ID ||
                      getChipletId() == (uint8_t)psChipletId_t::N1_CHIPLET_ID )
            {
                if ( (getEndpoint() == PSCOM_ENDPOINT) && // 0x1
                     ( getRingId() == ps_n0_ring_id_t::N01_RING_ADLQ0 ||
                       getRingId() == ps_n0_ring_id_t::N01_RING_ADLQ1 ))
                {
                    l_paxTarget = true;
                }
            }

        }

        return l_paxTarget;
    }

    // #####################################
    bool pst_scom_addr::isPaxoTarget()
    {
        bool l_paxoTarget = false;

        if (iv_chip_type == pstChipTypes_t::PS)
        {
            if ( (getChipletId() >= (uint8_t)psChipletId_t::PX08_CHIPLET_ID) &&
                 (getChipletId() <= (uint8_t)psChipletId_t::PX11_CHIPLET_ID) )
            {
                if ( (getEndpoint() == CHIPLET_CTRL_ENDPOINT) || // 0x0
                     (getEndpoint() == PSCOM_ENDPOINT) ||        // 0x1
                     (getEndpoint() == CLOCK_CTRL_ENDPOINT) ||   // 0x3
                     (getEndpoint() == FIR_ENDPOINT) ||          // 0x4
                     (getEndpoint() == THERMAL_ENDPOINT) ||      // 0x5
                     (getEndpoint() == PCBSLV_ENDPOINT) )        // 0xF
                {
                    l_paxoTarget = true;
                }
            }
        }

        return l_paxoTarget;
    }

    // #####################################
    bool pst_scom_addr::isIohsTarget()
    {
        bool l_iohsTarget = false;

        if (iv_chip_type == pstChipTypes_t::PS)
        {
            if (isPaxoTarget() || isPaxTarget())
            {
                if (getRingId() == IOHS_RING_ID)
                {
                    l_iohsTarget = true;
                }
            }
        }

        return l_iohsTarget;
    }

    // #####################################
    bool pst_scom_addr::isPervTarget()
    {
        bool l_pervTarget = false;
        uint8_t l_index = 0;
        uint8_t l_table_size = 0;

        if (iv_chip_type == pstChipTypes_t::PT)
        {
            l_table_size = sizeof(TapPervTargetChipletIdTable) / sizeof(uint8_t);
        }
        else
        {
            l_table_size = sizeof(SpinalPervTargetChipletIdTable) / sizeof(uint8_t);
        }

        // Check chiplet ID by looping through PERV chiplet ID table
        for (l_index = 0; l_index < l_table_size; l_index++)
        {
            uint8_t l_test_chiplet;

            if (iv_chip_type == pstChipTypes_t::PT)
            {
                l_test_chiplet = TapPervTargetChipletIdTable[l_index];
            }
            else
            {
                l_test_chiplet = SpinalPervTargetChipletIdTable[l_index];
            }

            // See if Chiplet ID is a perv chiplet ID from table
            if (getChipletId() == l_test_chiplet)
            {
                if (getEndpoint() == PSCOM_ENDPOINT) // 0x1
                {
                    // EQ specific PSCOM endpoint logic is unique,
                    // don't match here but handle specifically in isEqTarget()
                    // ensure ring being accessed is EQ scoped
                    if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
                         (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) &&
                         iv_chip_type == PT)
                    {
                        // no matching
                    }

                    // non-EQ chiplet, just match for ring ID = 0 / 1
                    else
                    {
                        if (   (getRingId() == PSCOM_RING_ID) ||  // 0x0
                               (getRingId() == PERV_RING_ID) )    // 0x1
                        {
                            l_pervTarget = true;
                        }
                    }
                }
                else if (getEndpoint() == CLOCK_CTRL_ENDPOINT)  // 0x3
                {
                    l_pervTarget = true;
                }
                // Check if Endpoint is a PERV endpoint
                else if ( (getEndpoint() == CHIPLET_CTRL_ENDPOINT) ||     // 0x0
                          (getEndpoint() == FIR_ENDPOINT)          ||     // 0x4
                          (getEndpoint() == THERMAL_ENDPOINT)      ||     // 0x5
                          (getEndpoint() == CHIPLET_2_CTRL_ENDPOINT) ||   // 0x9
                          (getEndpoint() == PCBSLV_ENDPOINT) )            // 0xF
                {
                    if ( getRingId() == PSCOM_RING_ID)                    // 0x0
                    {
                        l_pervTarget = true;
                    }
                }

                break;
            }
        }

        return l_pervTarget;
    }

    // #####################################
    bool pst_scom_addr::isEqTarget()
    {
        bool l_eqTarget = false;

        // Must have EQ chiplet ID
        if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
             (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) )
        {
            // If endpoint is QME (0xE):
            // QME per core (bit 20) must be 0
            // region select (bits 16:19) must be 0
            if ( (getEndpoint() == QME_ENDPOINT) &&
                 (!getQMEPerCore()) &&
                 (getRegionSelect() == EQ_REGION_SEL) )
            {
                l_eqTarget = true;
            }
            // EQ SCOM associated registers in PSCOM endpoint
            else if (getEndpoint() == PSCOM_ENDPOINT && // 0x1
                     ((getEQRingId() == QME_RING_ID) || // 0x2
                      (getEQRingId() == AN_RING_ID) ||  // 0x4
                      (getEQRingId() == RNG_RING_ID) || // 0x5
                      ((getEQRingId() == PERV_RING_ID) && // 0x1
                       (getEQSatId() == L3TRACE_COMMON_SAT_ID)))) // 0x0
            {
                l_eqTarget = true;
            }
            // associate perv target resources with EQ
            else if (isPervTarget())
            {
                l_eqTarget = true;
            }
        }

        return l_eqTarget;
    }

    // #####################################
    bool pst_scom_addr::isEQPerSliceRegister()
    {
        bool l_eqPerSlice = false;

        // Must have EQ chiplet ID
        if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
             (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) )
        {
            // Region select must be...
            if ( (getRegionSelect() == MULTI_HOT_SELECT_C0) ||  // 0x8
                 (getRegionSelect() == MULTI_HOT_SELECT_C1) ||  // 0x4
                 (getRegionSelect() == MULTI_HOT_SELECT_C2) ||  // 0x2
                 (getRegionSelect() == MULTI_HOT_SELECT_C3) ||  // 0x1
                 (getRegionSelect() == EQ_REGION_SEL) )         // 0x0
            {
                // allow access to QME-per-core regs from either C/L3 targets
                // If QME endpoint (0xE), QME per core (bit 20) must be 1
                if ( (getEndpoint() == QME_ENDPOINT) && getQMEPerCore() )
                {
                    l_eqPerSlice = true;
                }
                // PSCOM end point, Perv Ring ID, CLKADJ/SKEWADJ satellites
                else if ( (getEndpoint() == PSCOM_ENDPOINT) &&  // 0x1
                          (getEQRingId() == PERV_RING_ID) &&    // 0x1
                          ((getEQSatId() == CLKADJ_SAT_ID) ||   // 0x6
                           (getEQSatId() == SKEWADJ_SAT_ID)) )  // 0x7
                {
                    l_eqPerSlice = true;
                }
            }
        }

        return l_eqPerSlice;
    }

    // #####################################
    bool pst_scom_addr::isEQPerL3Register()
    {
        bool l_eqPerL3 = false;

        // Must have EQ chiplet ID
        if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
             (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) )
        {
            // Region select must be...
            if ( (getRegionSelect() == MULTI_HOT_SELECT_C0) ||  // 0x8
                 (getRegionSelect() == MULTI_HOT_SELECT_C1) ||  // 0x4
                 (getRegionSelect() == MULTI_HOT_SELECT_C2) ||  // 0x2
                 (getRegionSelect() == MULTI_HOT_SELECT_C3) ||  // 0x1
                 (getRegionSelect() == EQ_REGION_SEL) )         // 0x0
            {
                // PSCOM end point:
                //   1) PSCOM ring OR
                //   2) Perv Ring ID, all satellites except 0 (common L3 trace control macro)
                if ((getEndpoint() == PSCOM_ENDPOINT) &&  // 0x1
                    ((getEQRingId() == PSCOM_RING_ID) ||  // 0x0
                     ((getEQRingId() == PERV_RING_ID) &&  // 0x1
                      (getEQSatId() != L3TRACE_COMMON_SAT_ID)))) // 0x0
                {
                    l_eqPerL3 = true;
                }
            }
        }

        return l_eqPerL3;

    }

    // #####################################
    bool pst_scom_addr::isCoreTarget()
    {
        bool l_coreTarget = false;

        // Must have EQ chiplet ID
        if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
             (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) )
        {
            // Region select must be...
            if ( (getRegionSelect() == MULTI_HOT_SELECT_C0) ||  // 0x8
                 (getRegionSelect() == MULTI_HOT_SELECT_C1) ||  // 0x4
                 (getRegionSelect() == MULTI_HOT_SELECT_C2) ||  // 0x2
                 (getRegionSelect() == MULTI_HOT_SELECT_C3) ||  // 0x1
                 (getRegionSelect() == EQ_REGION_SEL) )         // 0x0
            {
                // include per slice registers in QME/clock controls in EQ scan scope
                if (isEQPerSliceRegister())
                {
                    l_coreTarget = true;
                }
                // core registers on second PSCOM endpoint (0x2), all are in core scan scope
                else if (getEndpoint() == PSCOM_2_ENDPOINT)
                {
                    l_coreTarget = true;
                }
            }
        }

        return l_coreTarget;
    }

    // #####################################
    bool pst_scom_addr::isL3Target()
    {
        bool l_l3Target = false;

        // Must have EQ chiplet ID
        if ( (getChipletId() >= (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) &&
             (getChipletId() <= (uint8_t)ptChipletId_t::EQ1_CHIPLET_ID) )
        {
            // Region select must be...
            if ( (getRegionSelect() == MULTI_HOT_SELECT_C0) ||  // 0x8
                 (getRegionSelect() == MULTI_HOT_SELECT_C1) ||  // 0x4
                 (getRegionSelect() == MULTI_HOT_SELECT_C2) ||  // 0x2
                 (getRegionSelect() == MULTI_HOT_SELECT_C3) ||  // 0x1
                 (getRegionSelect() == EQ_REGION_SEL) )         // 0x0
            {
                // include per slice registers in QME/clock controls and per L3 registers in EQ scan scope
                if (isEQPerSliceRegister() ||
                    isEQPerL3Register())
                {
                    l_l3Target = true;
                }
                // L3 registers on first PSCOM endpoint, all are in L3 scan scope
                else if ((getEndpoint() == PSCOM_ENDPOINT) &&  // 0x1
                         (getEQRingId() == L3_RING_ID))        // 0x2
                {
                    l_l3Target = true;
                }
            }
        }

        return l_l3Target;
    }

    // ########################################
    uint8_t pst_scom_addr::getEqTargetInstance()
    {
        uint8_t l_instance = 0;
        l_instance = (getChipletId() - (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID);
        return l_instance;
    }

    // ########################################
    uint8_t pst_scom_addr::getTbuslTargetInstance()
    {
        //NOTE: There are 2 groups per tbusl right now.
        //If it turns out to be better to have a tbusl target
        //per each group we can adjust later.
        uint8_t l_instance = 0;

        if (isIndirect())
        {
            // Tap
            if (iv_chip_type == pstChipTypes_t::PT)
            {
                l_instance = 0;
            }
            else // Spinal
            {
                l_instance = (getChipletId() - (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID) * NUM_TBUSL_PER_CPLT;
            }

            l_instance += (getIoGroupAddr() / NUM_GRPS_PER_TBUSL);
        }
        else if (iv_chip_type == pstChipTypes_t::PS)
        {
            l_instance = (getChipletId() - (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID) * NUM_TBUSL_PER_CPLT;
            l_instance += (getRingId() - TBUS_RING_SF0);
        }

        return l_instance;
    }

    // ########################################
    void pst_scom_addr::setTbuslGroup(uint8_t i_chipUnitNum)
    {
        uint8_t l_grp = getIoGroupAddr() % NUM_GRPS_PER_TBUSL;
        uint8_t l_cplt_tbusl = i_chipUnitNum % NUM_TBUSL_PER_CPLT;
        setIoGroupAddr((l_cplt_tbusl * NUM_GRPS_PER_TBUSL) + l_grp);
    }


    // ########################################
    uint8_t pst_scom_addr::getTbusTargetInstance()
    {
        uint8_t l_instance = 0;

        // Tap
        if (iv_chip_type == pstChipTypes_t::PT)
        {
            l_instance = 0; // No TBUS in Tap chip
        }
        else // Spinal
        {
            l_instance = (getChipletId() - (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID);
        }

        return l_instance;
    }

    // #####################################
    uint8_t pst_scom_addr::getCoreTargetInstance()
    {
        uint8_t l_instance = 0;

        // First core instance of the quad
        l_instance = (getChipletId() - (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID) * NUM_CORES_PER_EQ;

        // Get core instance based on region select
        if (getRegionSelect() == MULTI_HOT_SELECT_C3)
        {
            l_instance += 3;
        }
        else if (getRegionSelect() == MULTI_HOT_SELECT_C2)
        {
            l_instance += 2;
        }
        else if (getRegionSelect() == MULTI_HOT_SELECT_C1)
        {
            l_instance += 1;
        }

        return l_instance;
    }

    // #####################################
    void pst_scom_addr::pervChipUnitScom(const uint8_t i_ecLevel,
                                         bool& o_chipUnitRelated,
                                         std::vector<pst_chipUnitPairing_t>& o_chipUnitPairing,
                                         const pstTranslationMode_t i_mode)
    {
        // if running in engineering data build flow context, do not
        // emit associations for registers which would have only
        // a single association of type PERV
        if (!((o_chipUnitPairing.size() == 0) &&
              (i_mode == ENGD_BUILD_MODE)))
        {
            o_chipUnitRelated = true;
            // PU_PERV_CHIPUNIT
            o_chipUnitPairing.push_back(pst_chipUnitPairing_t(PERV_CHIPUNIT,
                                        getPervTargetInstance()));
        }
    }

    // #####################################
    uint8_t pst_scom_addr::getPervTargetInstance()
    {
        return getChipletId();
    }

    // #####################################
    uint8_t pst_scom_addr::getChipletId(const uint8_t i_chipUnitNum,
                                        const pstChipUnits_t i_chipUnitType,
                                        uint8_t& o_chipletId)
    {
        uint8_t l_rc = 0;

        do
        {
            if (iv_chip_type == pstChipTypes_t::PT)
            {
                switch (i_chipUnitType)
                {
                    case PERV_CHIPUNIT:
                        o_chipletId = i_chipUnitNum;
                        break;

                    case EQ_CHIPUNIT:
                        o_chipletId = (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case C_CHIPUNIT:
                        o_chipletId = (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID + (i_chipUnitNum / NUM_CORES_PER_EQ);
                        break;

                    case L3_CHIPUNIT:
                        o_chipletId = (uint8_t)ptChipletId_t::EQ0_CHIPLET_ID + (i_chipUnitNum / NUM_CORES_PER_EQ);
                        break;

                    case TBUSL_CHIPUNIT:
                        o_chipletId = (uint8_t)ptChipletId_t::TBUS0_CHIPLET_ID + (i_chipUnitNum / NUM_TBUSL_PER_CPLT);
                        break;

                    default:

                        l_rc = 1;
                        break;
                };
            }

            if (iv_chip_type == pstChipTypes_t::PS)
            {
                uint8_t l_chipletId = getChipletId();

                switch (i_chipUnitType)
                {
                    case PERV_CHIPUNIT:
                        o_chipletId = i_chipUnitNum;
                        break;

                    case TBUSL_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID + (i_chipUnitNum / NUM_TBUSL_PER_CPLT);
                        break;

                    case TBUS_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::TBUS0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case PAU_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::N0_CHIPLET_ID + (i_chipUnitNum / NUM_PAU_PER_CPLT);
                        break;

                    case INT_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::N2_CHIPLET_ID;
                        break;

                    case NX_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::N0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case OMIC_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::MC0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case MC_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::MC0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case MI_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::N2_CHIPLET_ID;
                        break;

                    case MCC_CHIPUNIT:
                        if ((uint8_t)psChipletId_t::MC0_CHIPLET_ID <= l_chipletId &&
                            l_chipletId <= (uint8_t)psChipletId_t::MC3_CHIPLET_ID)
                        {
                            o_chipletId = (uint8_t)psChipletId_t::MC0_CHIPLET_ID + (i_chipUnitNum / NUM_MCC_PER_CPLT);
                        }
                        else
                        {
                            o_chipletId = l_chipletId;
                        }

                        break;

                    case OMI_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::MC0_CHIPLET_ID + (i_chipUnitNum / NUM_OMI_PER_CPLT);
                        break;

                    case IOHS_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PX00_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case PAX_CHIPUNIT:
                        if ( (getChipletId() >= (uint8_t)psChipletId_t::PX00_CHIPLET_ID) &&
                             (getChipletId() <= (uint8_t)psChipletId_t::PX07_CHIPLET_ID) )
                        {
                            o_chipletId = (uint8_t)psChipletId_t::PX00_CHIPLET_ID + i_chipUnitNum;
                        }
                        else
                        {
                            //ADL
                            //ChipletId: 0x04 RingId: 0x4 SatId: 0x0 ECAPQ0_ADL0  paxo0001 OVW
                            //ChipletId: 0x04 RingId: 0x4 SatId: 0x1 ECAPQ0_ADL1  paxo0001 OVW
                            //ChipletId: 0x05 RingId: 0x4 SatId: 0x0 ECAPQ1_ADL0  paxo0203 OVW
                            //ChipletId: 0x05 RingId: 0x4 SatId: 0x1 ECAPQ1_ADL1  paxo0203 OVW
                            //ChipletId: 0x04 RingId: 0x6 SatId: 0x0 ECAPQ2_ADL0  paxo0405 OVW
                            //ChipletId: 0x04 RingId: 0x6 SatId: 0x1 ECAPQ2_ADL1  paxo0405 OVW
                            //ChipletId: 0x05 RingId: 0x6 SatId: 0x0 ECAPQ3_ADL0  paxo0607 OVW
                            //ChipletId: 0x05 RingId: 0x6 SatId: 0x1 ECAPQ3_ADL1  paxo0607 OVW
                            o_chipletId = (uint8_t)psChipletId_t::N0_CHIPLET_ID + ( (i_chipUnitNum / 2) % 2);
                        }

                        break;

                    case PAXO_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PX08_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case PEC2P_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PCI4_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case PEC6P_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PCI0_CHIPLET_ID + i_chipUnitNum;
                        break;

                    case PHB248X_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PCI0_CHIPLET_ID + (i_chipUnitNum / NUM_PHB_PER_PEC6P_CPLT);
                        break;

                    case PHB16X_CHIPUNIT:
                        o_chipletId = (uint8_t)psChipletId_t::PCI4_CHIPLET_ID + (i_chipUnitNum / NUM_PHB_PER_PEC2P_CPLT);
                        break;

                    default:
                        l_rc = 1;
                        break;
                };
            }
        }
        while (0);

        return (l_rc);
    }


}
